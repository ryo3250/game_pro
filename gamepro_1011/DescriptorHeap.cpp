
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
	rtvHeapDesc.NumDescriptors = numDescriptors; // スワップチェーンのバッファ数
		rtvHeapDesc.Type = type;
		rtvHeapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAR_FLAG_SHDER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

	ID3D12DescriptorHeap* rtvHeap;
	device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&rtvHeap));
}