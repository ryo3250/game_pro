#pragma once

#include"dx12.h"
#include<d3d12.h>

class device final
{
public:

	device() = default;

	~device();

	[[nodiscard]] bool create(const dx12& dxgi) noexcept;

	[[nodiscrad]] ID3D12Device* get() const noexcept;

private:
	ID3D12Device* device_;
};

