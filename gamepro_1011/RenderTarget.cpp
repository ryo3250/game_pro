#include "RenderTarget.h"
#include <cassert>

RenderTarget::~RenderTarget()
{
	for (auto& rt : renderTragets_)
	{
		if (rt)
		{
			rt->Release();
			rt = nullptr;
		}
	}
	renderTragets_.clear();
}

[[nodiscard]] bool RenderTarget::createBackBuffer(const device& device, const swap_chain& swapChain, DescriptorHeap& heap) noexcept 
{
	const auto& desc = swapChain.getDesc();

	renderTragets_.resize(desc.BufferCount);
	
	auto handle = heap.get()->GetCPUDescriptorHandleForHeapStart();

	auto heapType = heap.getType();
	assert(heapType == D3D12_DESCRIPTOR_HEAP_TYPE_RTV && "ディスクリプタヒープのタイプが RTV ではありません");

	for (uint8_t i = 0; i < desc.BufferCount; ++i) 
	{
	
	}
}