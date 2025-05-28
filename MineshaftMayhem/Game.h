#pragma once

#include <SimpleMath.h>

#include "StaticGeometry.h"

XM_ALIGNED_STRUCT(256) CameraTransforms
{
    DirectX::SimpleMath::Matrix ViewProjection;
};
XM_ALIGNED_STRUCT(256) ModelTransform
{
    DirectX::SimpleMath::Matrix  Model;
    DirectX::SimpleMath::Vector2 TexCoords[4];
};

class Game
{
    static constexpr int MAX_LOADSTRING = 200;

public:
    Game(HINSTANCE hInstance, LPWSTR lpCmdLine, int nCmdShow);

    ~Game();

    void Update(float deltaTime);

    void Resize();

    void Render(float deltaTime);

    bool IsRunning() const;

    void Quit();

private:
    using StaticSamplers = std::array<const CD3DX12_STATIC_SAMPLER_DESC, 1>;

    void                                                   Draw(float deltaTime);

    void                                                   CreateBuffers();

    void                                                   CreatePipelineState();

    void                                                   UpdateUniforms(float deltaTime);

    WCHAR                                                  m_szTitle[MAX_LOADSTRING];
    WCHAR                                                  m_szWindowClass[MAX_LOADSTRING];
    HINSTANCE                                              m_hInstance;
    HWND                                                   m_hWnd;
    bool                                                   m_running = true;
    std::unique_ptr<class Camera>                          m_camera;
    std::unique_ptr<class Level>                           m_level;
    winrt::com_ptr<ID3D12RootSignature>                    m_rootSignature;
    winrt::com_ptr<ID3D12PipelineState>                    m_pipelineState;
    std::unique_ptr<StaticGeometry<VertexPositionTexture>> m_cubeGeometry;
    winrt::com_ptr<ID3D12DescriptorHeap>                   m_srvDescriptorHeap;
    winrt::com_ptr<ID3D12DescriptorHeap>                   m_instanceBufferHeap;
    std::unique_ptr<class GeometryBuilder>                 m_geometryBuilder;
    std::unique_ptr<class Texture>                         m_texture;
    float                                                  m_time;
    winrt::com_ptr<ID3D12Resource>                         m_constBuffer;
    CameraTransforms                                       m_constBufferData{};
    UINT8*                                                 m_constBufferDataBegin{};
    std::vector<ModelTransform>                            m_transforms;
    UINT8*                                                 m_instBufferBegin{};
    winrt::com_ptr<ID3D12Resource>                         m_instanceBuffer;
    float                                                  m_rotationY = 0.0f;
    float                                                  m_rotationX = 0.0f;
    float                                                  m_prevRotationX = 0.0f;
    float                                                  m_prevRotationY = 0.0f;
    float                                                  m_cubeRotationY = 0.0f;
    DirectX::SimpleMath::Vector3                           m_prevPosition = DirectX::SimpleMath::Vector3::Zero;
    DirectX::SimpleMath::Vector3                           m_currentPosition = DirectX::SimpleMath::Vector3::Zero;
    std::unique_ptr<class D3D12Context>                    m_context;
    std::unique_ptr<DirectX::Keyboard>                     m_keyboard;
    std::unique_ptr<DirectX::Mouse>                        m_mouse;
    DirectX::SimpleMath::Matrix                            m_projection;
};
