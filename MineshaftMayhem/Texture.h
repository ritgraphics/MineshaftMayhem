#pragma once

class D3D12Context;
class Texture
{
public:
    explicit Texture(const std::vector<uint8_t>& data);

    void Upload(D3D12Context& context);
    void AddToDescriptorHeap(ID3D12Device* device, ID3D12DescriptorHeap* descriptorHeap, size_t index);
    void Bind(ID3D12GraphicsCommandList* commandList);
    UINT GetWidth() const;
    UINT GetHeight() const;

private:
    std::vector<uint8_t>           m_data;
    winrt::com_ptr<ID3D12Resource> m_resource;
    winrt::com_ptr<ID3D12Resource> m_uploadHeap;
    ID3D12DescriptorHeap*          m_srvDescriptorHeap;
};
