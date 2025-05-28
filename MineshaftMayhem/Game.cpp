#include "pch.h"
#include "Game.h"

#include "resource.h"

#include <stdexcept>

#include "D3D12Context.h"
#include "File.h"
#include "Level.h"
#include "Texture.h"
#include "Camera.hpp"
#include "GeometryBuilder.h"

using namespace DirectX::SimpleMath;

namespace
{
    LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
    {
        Game* game = reinterpret_cast<Game*>(GetWindowLongPtrW(hWnd, GWLP_USERDATA));
        switch (message)
        {
        case WM_CREATE: {
            CREATESTRUCT* lpCreateStruct = reinterpret_cast<CREATESTRUCT*>(lParam);
            if (lpCreateStruct != nullptr)
            {
                game = static_cast<Game*>(lpCreateStruct->lpCreateParams);
                SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(game));
            }
            return 0;
        }
        case WM_ACTIVATEAPP: {
            DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
            DirectX::Mouse::ProcessMessage(message, wParam, lParam);
            return 0;
        }

        case WM_MOUSEACTIVATE:
            // When you click to activate the window, we want Mouse to ignore that event.
            return MA_ACTIVATEANDEAT;

        case WM_ACTIVATE:
        case WM_INPUT:
        case WM_MOUSEMOVE:
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_RBUTTONDOWN:
        case WM_RBUTTONUP:
        case WM_MBUTTONDOWN:
        case WM_MBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_XBUTTONDOWN:
        case WM_XBUTTONUP:
        case WM_MOUSEHOVER:
            DirectX::Mouse::ProcessMessage(message, wParam, lParam);
            return 0;

        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
            DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
            break;

        case WM_SYSKEYDOWN:
            DirectX::Keyboard::ProcessMessage(message, wParam, lParam);
            break;

        case WM_SIZE: {
            if (game)
                game->Resize();
            break;
        }

        case WM_CLOSE:
        case WM_DESTROY:
            game->Quit();
            PostQuitMessage(0);
            return 0;
        }

        return DefWindowProc(hWnd, message, wParam, lParam);
    }

    ATOM RegisterWindowClass(HINSTANCE hInstance, WCHAR* szWindowClass)
    {
        WNDCLASSEXW wcex{};
        wcex.cbSize = sizeof(WNDCLASSEX);
        wcex.style = CS_HREDRAW | CS_VREDRAW;
        wcex.lpfnWndProc = WndProc;
        wcex.cbClsExtra = 0;
        wcex.cbWndExtra = 0;
        wcex.hInstance = hInstance;
        wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MINESHAFTMAYHEM));
        wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
        wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_MINESHAFTMAYHEM);
        wcex.lpszClassName = szWindowClass;
        wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

        return RegisterClassExW(&wcex);
    }

} // namespace

Game::Game(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow) : m_hInstance(hInstance), m_hWnd(nullptr)
{
    if (LoadStringW(m_hInstance, IDS_APP_TITLE, m_szTitle, MAX_LOADSTRING) == 0)
    {
        throw std::runtime_error("Failed to load title string resource.");
    }
    if (LoadStringW(m_hInstance, IDC_MINESHAFTMAYHEM, m_szWindowClass, MAX_LOADSTRING) == 0)
    {
        throw std::runtime_error("Failed to load window class string resource.");
    }

    ATOM classAtom = RegisterWindowClass(m_hInstance, m_szWindowClass);
    if (classAtom == INVALID_ATOM)
    {
        throw std::runtime_error("Failed to register window class.");
    }

    // Create application window
    m_hWnd = CreateWindowW(m_szWindowClass, m_szTitle, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr,
                           nullptr, hInstance, this);
    if (m_hWnd == nullptr)
    {
        throw std::runtime_error("Failed to create window.");
    }

    ShowWindow(m_hWnd, nCmdShow);
    UpdateWindow(m_hWnd);

    m_context = std::make_unique<D3D12Context>(m_hWnd);

    m_geometryBuilder = std::make_unique<GeometryBuilder>(m_context->GetDevice());
    m_transforms.resize(10000);

    try
    {
        File       file(L"level1.xml");

        const auto bytes = file.ReadAll();
        m_level = std::make_unique<Level>(bytes.data(), bytes.size());

        File texture(L"stackedTileSheet.dds");
        m_texture = std::make_unique<Texture>(texture.ReadAll());

        D3D12_DESCRIPTOR_HEAP_DESC srvDescriptorHeapDesc = {};
        srvDescriptorHeapDesc.NumDescriptors = 2;
        srvDescriptorHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
        srvDescriptorHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
        winrt::check_hresult(
            m_context->GetDevice()->CreateDescriptorHeap(&srvDescriptorHeapDesc, IID_PPV_ARGS(&m_srvDescriptorHeap)));

        m_texture->Upload(*m_context);
        m_texture->AddToDescriptorHeap(m_context->GetDevice(), m_srvDescriptorHeap.get(), 0);

        File       rs(L"RootSignature1.cso");
        const auto rootSignature = rs.ReadAll();
        winrt::check_hresult(m_context->GetDevice()->CreateRootSignature(0, rootSignature.data(), rootSignature.size(),
                                                                         IID_PPV_ARGS(&m_rootSignature)));
    }
    catch (const std::exception& e)
    {
        OutputDebugStringA(e.what());
    }

    CreatePipelineState();

    CreateBuffers();

    RECT rect{};
    GetClientRect(m_hWnd, &rect);
    const auto      width = rect.right - rect.left;
    const auto      height = rect.bottom - rect.top;
    const float     aspect = static_cast<float>(width) / static_cast<float>(height);
    constexpr float fov = DirectX::XMConvertToRadians(75.0f);
    constexpr float nearPlane = 0.01f;
    constexpr float farPlane = 1000.0f;

    m_camera = std::make_unique<Camera>(Vector3::Zero, Vector3::Forward, Vector3::Up, fov, aspect, nearPlane, farPlane,
                                        width, height);

    m_keyboard = std::make_unique<DirectX::Keyboard>();
    m_mouse = std::make_unique<DirectX::Mouse>();
    m_mouse->SetWindow(m_hWnd);

    m_projection = Matrix::CreateOrthographicOffCenter(0.0f, width, height, 0.0f, -100.0f, 100.0f);
}

Game::~Game() = default;

void Game::Quit()
{
    m_running = false;
}

void Game::Resize()
{
    if (m_context)
    {
        m_context->ResizeSwapChain();

        RECT rect{};
        GetClientRect(m_hWnd, &rect);
        const auto      width = rect.right - rect.left;
        const auto      height = rect.bottom - rect.top;
        const float     aspect = static_cast<float>(width) / static_cast<float>(height);
        constexpr float fov = DirectX::XMConvertToRadians(75.0f);
        constexpr float nearPlane = 0.01f;
        constexpr float farPlane = 1000.0f;
        m_camera->setProjection(fov, aspect, nearPlane, farPlane, width, height);
        m_projection = Matrix::CreateOrthographicOffCenter(0.0f, width, height, 0.0f, -100.0f, 100.0f);
    }
}

void Game::UpdateUniforms(float deltaTime)
{
    using namespace DirectX::SimpleMath;

    constexpr float xStep = 32.0f / 128.0f;
    for (uint32_t i = 0; i < 8; i++)
    {
        auto          position = Vector3(i * (38.0f), 0.0, 0.0f);
        auto          rotationX = 0.0f;
        auto          rotationY = 0.0f;
        auto          scaleFactor = 3.0f;
        const Vector3 xAxis = Vector3::Right;
        const Vector3 yAxis = Vector3::Up;
        Matrix        xRot = Matrix::CreateFromAxisAngle(xAxis, rotationX);
        Matrix        yRot = Matrix::CreateFromAxisAngle(yAxis, rotationY);
        Matrix        translation = Matrix::CreateTranslation(position);
        Matrix        rotation = Matrix::CreateRotationZ(m_cubeRotationY);
        Matrix        scale = Matrix::CreateScale(32, 32, 1.0f);
        Matrix        model = scale * Matrix::CreateTranslation(-16.0f, -16.0f, 0.0f) * rotation *
                       Matrix::CreateTranslation(16.0f, 16.0f, 0.0f) * translation;
        const auto                     width = static_cast<float>(m_texture->GetWidth());
        const auto                     height = static_cast<float>(m_texture->GetHeight());
        float                          transformWidth = width;
        float                          transformHeight = height;
        DirectX::SimpleMath::Rectangle sourceRect = {(long)(32 * i) % 64, (i % 32) * 128, 32, 32};
        if (!sourceRect.IsEmpty())
        {
            transformWidth = sourceRect.width;
            transformHeight = sourceRect.height;
        }

        const float                    x = sourceRect.x / width;
        const float                    y = sourceRect.y / height;
        const float                    w = sourceRect.width / width;
        const float                    h = sourceRect.height / height;

        DirectX::SimpleMath::Rectangle base = {0, 0, (long)m_texture->GetWidth(), (long)m_texture->GetHeight()};
        DirectX::SimpleMath::Rectangle inter = Rectangle::Union(base, sourceRect);

        float                          u1 = 0.0f;
        float                          v1 = 0.0f;
        float                          u2 = 1.0f;
        float                          v2 = 1.0f;

        if (!sourceRect.IsEmpty())
        {
            // Calculate UV coordinates
            u1 = sourceRect.x / width;                                      // Start U
            v1 = sourceRect.y / height;                                     // Start V
            u2 = ((float)sourceRect.x + (float)sourceRect.width) / width;   // End U
            v2 = ((float)sourceRect.y + (float)sourceRect.height) / height; // End V
        }

        const auto uv0 = Vector2(u1, v2);
        const auto uv1 = Vector2(u2, v2);
        const auto uv2 = Vector2(u1, v1);
        const auto uv3 = Vector2(u2, v1);

        m_transforms[i].Model = model;
        m_transforms[i].TexCoords[0] = uv0;
        m_transforms[i].TexCoords[1] = uv1;
        m_transforms[i].TexCoords[2] = uv2;
        m_transforms[i].TexCoords[3] = uv3;
    }

    memcpy(m_instBufferBegin, m_transforms.data(), sizeof(ModelTransform) * m_transforms.size());

    m_constBufferData.ViewProjection = m_projection; // m_camera->viewProjection();
    memcpy(m_constBufferDataBegin, &m_constBufferData, sizeof(m_constBufferData));

    m_cubeRotationY += deltaTime;
}

void Game::Update(float deltaTime)
{
    auto kb = m_keyboard->GetState();
    if (kb.Escape)
    {
        Quit();
    }

    auto mb = m_mouse->Get().GetState();

    //// FPS camera controls
    //// NOTE: Needs mouse->SetMode(Relative);
    // m_rotationX -= mb.x * deltaTime;
    // m_rotationY -= mb.y * deltaTime;
    //// Clamp m_rotationX between 75 degrees and -75 degrees
    // m_rotationY = std::clamp(m_rotationY, -DirectX::XMConvertToRadians(75.0f), DirectX::XMConvertToRadians(75.0f));
    // m_camera->rotate(m_rotationY, m_rotationX);

    if (m_level)
    {
        m_level->Update();
    }

    UpdateUniforms(deltaTime);
}

void Game::Render(float deltaTime)
{
    if (!m_context)
        return;

    m_context->BeginFrame();

    Draw(deltaTime);

    m_context->EndFrame();
}

void Game::Draw(float deltaTime)
{
    ID3D12GraphicsCommandList* commandList = m_context->GetCommandList();

    DirectX::ScopedPixEvent    scopedEvent(commandList, 0, L"Rendering");

    // Set the root signature
    commandList->SetGraphicsRootSignature(m_rootSignature.get());

    ID3D12DescriptorHeap* heaps[] = {m_srvDescriptorHeap.get()};
    commandList->SetDescriptorHeaps(_countof(heaps), heaps);

    const auto descriptorIncrementSize =
        m_context->GetDevice()->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    CD3DX12_GPU_DESCRIPTOR_HANDLE tex(m_srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart(), 0,
                                      descriptorIncrementSize);
    commandList->SetGraphicsRootDescriptorTable(1, tex);

    CD3DX12_GPU_DESCRIPTOR_HANDLE ibuffer(m_srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart(), 1,
                                          descriptorIncrementSize);
    commandList->SetGraphicsRootDescriptorTable(3, ibuffer);

    commandList->SetGraphicsRoot32BitConstant(0, *reinterpret_cast<UINT*>(&m_time), 1);

    // Set the constant buffer view (For scene data such as camera and timing)
    commandList->SetGraphicsRootConstantBufferView(2, m_constBuffer->GetGPUVirtualAddress());

    // Set the pipeline state
    commandList->SetPipelineState(m_pipelineState.get());

    m_cubeGeometry->Draw(commandList, 8);

    m_time += deltaTime;
}

void Game::CreatePipelineState()
{
    ID3D12Device* device = m_context->GetDevice();

    const auto    inputElementDesc = VertexPositionTexture::InputLayout();
    auto          rasterDesc = CD3DX12_RASTERIZER_DESC(D3D12_DEFAULT);
    rasterDesc.CullMode = D3D12_CULL_MODE_BACK;
    rasterDesc.FrontCounterClockwise = TRUE;

    std::vector<uint8_t> vertexShader;
    std::vector<uint8_t> pixelShader;
    try
    {
        File vs("SimpleTextureVS.cso");
        File ps("SimpleTexturePS.cso");

        vertexShader = vs.ReadAll();
        pixelShader = ps.ReadAll();
    }
    catch (const std::exception& e)
    {
        OutputDebugStringA(e.what());
    }

    D3D12_GRAPHICS_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.InputLayout = {inputElementDesc.data(), (UINT)inputElementDesc.size()};
    psoDesc.pRootSignature = m_rootSignature.get();
    psoDesc.VS = CD3DX12_SHADER_BYTECODE(vertexShader.data(), vertexShader.size());
    psoDesc.PS = CD3DX12_SHADER_BYTECODE(pixelShader.data(), pixelShader.size());
    psoDesc.RasterizerState = rasterDesc;
    psoDesc.BlendState = CD3DX12_BLEND_DESC(D3D12_DEFAULT);
    psoDesc.DepthStencilState.DepthEnable = FALSE;
    psoDesc.DepthStencilState.DepthFunc = D3D12_COMPARISON_FUNC_LESS;
    psoDesc.DepthStencilState.StencilEnable = FALSE;
    psoDesc.SampleMask = UINT_MAX;
    psoDesc.PrimitiveTopologyType = D3D12_PRIMITIVE_TOPOLOGY_TYPE_TRIANGLE;
    psoDesc.NumRenderTargets = 1;
    psoDesc.DSVFormat = DXGI_FORMAT_D32_FLOAT;
    psoDesc.RTVFormats[0] = m_context->GetBackBufferFormat();
    psoDesc.SampleDesc.Count = 1;
    winrt::check_hresult(device->CreateGraphicsPipelineState(&psoDesc, IID_PPV_ARGS(&m_pipelineState)));
    m_pipelineState->SetName(L"SimpleTexture");
}

void Game::CreateBuffers()
{
    using namespace DirectX::SimpleMath;

    ID3D12Device* device = m_context->GetDevice();

    m_cubeGeometry = m_geometryBuilder->ConstructQuad<VertexPositionTexture>(Vector2{});

    D3D12_RANGE readRange{};
    // Create the constant buffer.
    {
        constexpr UINT constantBufferSize = sizeof(CameraTransforms); // CB size is required to be 256-byte aligned.

        const auto     cbHeapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        const auto     cbHeapDesc = CD3DX12_RESOURCE_DESC::Buffer(constantBufferSize);
        winrt::check_hresult(device->CreateCommittedResource(&cbHeapProps, D3D12_HEAP_FLAG_NONE, &cbHeapDesc,
                                                             D3D12_RESOURCE_STATE_COMMON, nullptr,
                                                             IID_PPV_ARGS(&m_constBuffer)));

        //// Map and initialize the constant buffer. We don't unmap this until the
        //// app closes. Keeping things mapped for the lifetime of the resource is okay
        winrt::check_hresult(m_constBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_constBufferDataBegin)));
        memcpy(m_constBufferDataBegin, &m_constBufferData, sizeof(m_constBufferData));
    }

    {
        readRange = {};
        // Create the instance buffer
        const UINT instanceBufferSize =
            sizeof(ModelTransform) * m_transforms.size(); // CB size is required to be 256-byte aligned.

        const auto srvHeapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        const auto srvHeapDesc = CD3DX12_RESOURCE_DESC::Buffer(instanceBufferSize);
        winrt::check_hresult(device->CreateCommittedResource(&srvHeapProps, D3D12_HEAP_FLAG_NONE, &srvHeapDesc,
                                                             D3D12_RESOURCE_STATE_COMMON, nullptr,
                                                             IID_PPV_ARGS(&m_instanceBuffer)));

        //// Map and initialize the constant buffer. We don't unmap this until the
        //// app closes. Keeping things mapped for the lifetime of the resource is okay
        winrt::check_hresult(m_instanceBuffer->Map(0, &readRange, reinterpret_cast<void**>(&m_instBufferBegin)));
        // memcpy(m_instBufferBegin, m_transforms.data(), sizeof(m_constBufferData));

        CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(
            m_srvDescriptorHeap->GetCPUDescriptorHandleForHeapStart(), 1,
            device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
        D3D12_SHADER_RESOURCE_VIEW_DESC srvDescription = {};
        srvDescription.ViewDimension = D3D12_SRV_DIMENSION_BUFFER;
        srvDescription.Format = DXGI_FORMAT_UNKNOWN;
        srvDescription.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
        srvDescription.Buffer.FirstElement = 0;
        srvDescription.Buffer.NumElements = m_transforms.size();
        srvDescription.Buffer.StructureByteStride = sizeof(ModelTransform);
        srvDescription.Buffer.Flags = D3D12_BUFFER_SRV_FLAG_NONE;
        device->CreateShaderResourceView(m_instanceBuffer.get(), &srvDescription, hDescriptor);
    }
}

bool Game::IsRunning() const
{
    return m_running;
}