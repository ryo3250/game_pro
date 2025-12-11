#pragma once

#include"device.h"
#include"swap_chain.h"
#include"DescriptorHeap.h"
#include<vector>

class RenderTarget
{
public:
	RenderTarget() = default;

	~RenderTarget();

	[[nodiscard]] bool createBackBuffer(const device& device, const swap_chain& swapChain, DescriptorHeap& heap) noexcept;

	[[nodiscard]] D3D12_CPU_DESCRIPTOR_HANDLE getDescriptorHandle(const device& device, const DescriptorHeap& heap, UINT index) const noexcept;

	[[nodiscard]] ID3D12Resource* get(uint32_t index) const noexcept;

private:
	std::vector<ID3D12Resource*> renderTragets_;
};

