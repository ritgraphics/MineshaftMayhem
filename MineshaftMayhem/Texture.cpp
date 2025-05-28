#include "pch.h"
#include "Texture.h"

#include "DDSTextureLoader12.h"

#include "D3D12Context.h"

Texture::Texture(const std::vector<uint8_t>& data) : m_data(data)
{
}

UINT Texture::GetWidth() const
{
    return m_resource->GetDesc().Width;
}

UINT Texture::GetHeight() const
{
    return m_resource->GetDesc().Height;
}

void Texture::Upload(D3D12Context& context)
{
    ID3D12Device*                       device = context.GetDevice();
    ID3D12CommandQueue*                 commandQueue = context.GetCommandQueue();
    ID3D12GraphicsCommandList*          commandList = context.GetCommandList();

    std::vector<D3D12_SUBRESOURCE_DATA> subresources;
    winrt::check_hresult(
        DirectX::LoadDDSTextureFromMemory(device, m_data.data(), m_data.size(), m_resource.put(), subresources));

    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(m_resource.get(), 0, subresources.size());

    auto         uploadHeapProperties = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD);
    auto         resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(uploadBufferSize);
    HRESULT      hr =
        device->CreateCommittedResource(&uploadHeapProperties, D3D12_HEAP_FLAG_NONE, &resourceDesc,
                                        D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&m_uploadHeap));

    commandList->Reset(context.GetCommandAllocator(), nullptr);
    auto barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_resource.get(), D3D12_RESOURCE_STATE_COMMON,
                                                        D3D12_RESOURCE_STATE_COPY_DEST);
    commandList->ResourceBarrier(1, &barrier);
    UpdateSubresources(commandList, m_resource.get(), m_uploadHeap.get(), 0, 0, subresources.size(),
                       subresources.data());

    barrier = CD3DX12_RESOURCE_BARRIER::Transition(m_resource.get(), D3D12_RESOURCE_STATE_COPY_DEST,
                                                   D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);
    commandList->ResourceBarrier(1, &barrier);
    winrt::check_hresult(commandList->Close());

    ID3D12CommandList* ppCommandLists[] = {commandList};
    commandQueue->ExecuteCommandLists(1, ppCommandLists);

    context.WaitForGpuCompletion();
}

void Texture::AddToDescriptorHeap(ID3D12Device* device, ID3D12DescriptorHeap* descriptorHeap, size_t index)
{
    m_srvDescriptorHeap = descriptorHeap;

    CD3DX12_CPU_DESCRIPTOR_HANDLE hDescriptor(
        descriptorHeap->GetCPUDescriptorHandleForHeapStart(), index,
        device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV));
    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    srvDesc.Format = m_resource->GetDesc().Format;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = m_resource->GetDesc().MipLevels;
    srvDesc.Texture2D.ResourceMinLODClamp = 0.0f;
    device->CreateShaderResourceView(m_resource.get(), &srvDesc, hDescriptor);
}

void Texture::Bind(ID3D12GraphicsCommandList* commandList)
{
    CD3DX12_GPU_DESCRIPTOR_HANDLE hDescriptor(m_srvDescriptorHeap->GetGPUDescriptorHandleForHeapStart());
    commandList->SetGraphicsRootDescriptorTable(0, hDescriptor);
}