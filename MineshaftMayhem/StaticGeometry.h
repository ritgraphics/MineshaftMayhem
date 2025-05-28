#pragma once

#include <SimpleMath.h>

XM_ALIGNED_STRUCT(16) VertexPositionColor
{
    DirectX::SimpleMath::Vector3                 Position;
    DirectX::SimpleMath::Vector4                 Color;

    static std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout()
    {
        return {
            {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
            {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(VertexPositionColor, Color),
             D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
        };
    }
};

XM_ALIGNED_STRUCT(16) VertexPositionTexture
{
    DirectX::SimpleMath::Vector3                 Position;
    DirectX::SimpleMath::Vector2                 TexCoord;

    static std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout()
    {
        return {{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(VertexPositionTexture, TexCoord),
                 D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};
    }
};

XM_ALIGNED_STRUCT(16) Vertex
{
    DirectX::SimpleMath::Vector3                 Position;
    DirectX::SimpleMath::Vector4                 Color;
    DirectX::SimpleMath::Vector2                 TexCoord;

    static std::vector<D3D12_INPUT_ELEMENT_DESC> InputLayout()
    {
        return {{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, offsetof(Vertex, Color),
                 D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0},
                {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, offsetof(Vertex, TexCoord),
                 D3D12_INPUT_CLASSIFICATION_PER_VERTEX_DATA, 0}};
    }
};

template <typename VertexType>
struct StaticGeometry
{
    explicit StaticGeometry(
        ID3D12Device* device, const VertexType* vertices, size_t nVertices, const uint16_t* indices, size_t nIndices)
    {
        IndexCount = nIndices;
        const size_t vertexBufferSize = sizeof(VertexType) * nVertices;
        const auto   heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        const auto   resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(vertexBufferSize);
        winrt::check_hresult(device->CreateCommittedResource(&heapProps, D3D12_HEAP_FLAG_NONE, &resourceDesc,
                                                             D3D12_RESOURCE_STATE_COMMON, nullptr,
                                                             IID_PPV_ARGS(&VertexBuffer)));
        UINT8*              vertexDataBegin{};
        const CD3DX12_RANGE readRange(0, 0);
        winrt::check_hresult(VertexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&vertexDataBegin)));
        memcpy(vertexDataBegin, vertices, vertexBufferSize);
        VertexBuffer->Unmap(0, nullptr);

        VertexBufferView.BufferLocation = VertexBuffer->GetGPUVirtualAddress();
        VertexBufferView.StrideInBytes = sizeof(VertexType);
        VertexBufferView.SizeInBytes = vertexBufferSize;

        const size_t indexBufferSize = sizeof(uint16_t) * nIndices;
        const auto   indexHeapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
        const auto   indexResourceDesc = CD3DX12_RESOURCE_DESC::Buffer(indexBufferSize);
        winrt::check_hresult(device->CreateCommittedResource(&indexHeapProps, D3D12_HEAP_FLAG_NONE, &indexResourceDesc,
                                                             D3D12_RESOURCE_STATE_COMMON, nullptr,
                                                             IID_PPV_ARGS(&IndexBuffer)));
        UINT8* indexDataBegin{};
        winrt::check_hresult(IndexBuffer->Map(0, &readRange, reinterpret_cast<void**>(&indexDataBegin)));
        memcpy(indexDataBegin, indices, indexBufferSize);
        IndexBuffer->Unmap(0, nullptr);
        IndexBufferView.BufferLocation = IndexBuffer->GetGPUVirtualAddress();
        IndexBufferView.Format = DXGI_FORMAT_R16_UINT;
        IndexBufferView.SizeInBytes = indexBufferSize;
    }

    explicit StaticGeometry(ID3D12Device*                 device,
                            const std::vector<VertexType> vertices,
                            const std::vector<uint16_t>   indices)
        : StaticGeometry(device, vertices.data(), vertices.size(), indices.data(), indices.size())
    {
    }

    void Draw(ID3D12GraphicsCommandList* commandList, uint32_t nIndices)
    {
        // Set the primitive topology
        commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        commandList->IASetVertexBuffers(0, 1, &VertexBufferView);

        commandList->IASetIndexBuffer(&IndexBufferView);

        commandList->DrawIndexedInstanced(IndexCount, nIndices, 0, 0, 0);
    }

    size_t                         IndexCount;
    D3D12_VERTEX_BUFFER_VIEW       VertexBufferView;
    D3D12_INDEX_BUFFER_VIEW        IndexBufferView;
    winrt::com_ptr<ID3D12Resource> VertexBuffer;
    winrt::com_ptr<ID3D12Resource> IndexBuffer;
};
