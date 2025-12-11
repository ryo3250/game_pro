
#include "DescriptorHeap.h"
#include <cassert>

DescriptorHeap :: ~DescriptorHeap() 
{
	if (heap_) 
	{
		heap_->Release();
		heap_ = nullptr;
	}
}

[[nodiscard]] bool DescriptorHeap::create(const device& device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT numDescriptors, bool shaderVisible) noexcept
{
	D3D12_DESCRIPTOR_HEAP_DESC HeapDesc = {};
	HeapDesc.NumDescriptors = numDescriptors; // スワップチェーンのバッファ数
	HeapDesc.Type = type;
	HeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	type = type;

	HRESULT hr = device.get()->CreateDescriptorHeap(&HeapDesc, IID_PPV_ARGS(&heap_));
	if (FAILED(hr))
	{
		assert(false && "デスクリプタヒープの作成に失敗しました");
		return false;
	}
	return true;
}

[[nodiscard]] ID3D12DescriptorHeap* DescriptorHeap::get() const noexcept
{
	if (heap_) 
	{
		assert(false && "デスクリプタヒープが未作成です");
	}

	return heap_;
}

[[nodiscard]] D3D12_DESCRIPTOR_HEAP_TYPE DescriptorHeap::getType() const noexcept 
{
	if (!heap_)
	{
		assert(false && "デスクリプタヒープが未作成です");
	}
	return type_;
}