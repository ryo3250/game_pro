#pragma once
#include"DXGI.h"
#include"command_queue.h"
#include"window.h"

class swap_chain final
{
public:
	swap_chain() = default;

	~swap_chain();

	[[nodiscard]] bool create(const DXGI& dxgi, const window& window, const command_queue& commandQueue) noexcept;

	[[nodiscard]] IDXGISwapChain3* get() const noexcept;

	[[nodiscard]] const DXGI_SWAP_CHAIN_DESC1& getDesc() const noexcept;

private:
	IDXGISwapChain3* swapChain_{};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc_{};
};

