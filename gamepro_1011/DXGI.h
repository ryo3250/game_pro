#pragma once

#include<d3d12.h>
#include<dxgi1_4.h>
class DXGI final
{
public:
	DXGI() = default;

	~DXGI();

	[[nodiscard]] bool setDisplayAdapter() noexcept;

	[[nodiscard]] IDXGIFactory4* factory() const noexcept;

	[[nodiscard]] IDXGIAdapter1* sisplayAdapter() const noexcept;

private:
	IDXGIFactory4* dxgiFactory_{};
	IDXGIAdapter1* dxgiAdapter_{};
};

