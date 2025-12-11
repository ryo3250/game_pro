#include "device.h"
#include <cassert>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "deguid.lib")

device::~device() 
{
	if (device_) 
	{
		device_->Release();
		device_ = nullptr;
	}
}

[[nodiscard]] bool create(const dx12& dxgi) noexcept
{
	const auto hr = D3D12CreateDevice(dxgi.displayAdapter(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device_));
}

