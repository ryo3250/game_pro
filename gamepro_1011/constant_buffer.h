#pragma once

#include "device.h"
#include "DescriptorHeap.h"

class constant_buffer final
{
public:

	constant_buffer() = default;

	~constant_buffer();

	[[nodiscard]] bool cerate(const device& device, const DescriptorHeap& heap, UINT bufferSize, UINT descriptorIndex) noexcept;

	[[nodiscard]] ID3D12Resource* constantBuffer() const noexcept;

	[[nodiscard]] D3D12_GPU_DESCRIPTOR_HANDLE getGpuDescriptorHandle() const noexcept;

private:
	ID3D12Resource* constanBuffer_{};
	D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle_{};

};

