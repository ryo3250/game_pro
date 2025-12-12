#include "CommandAllocator.h"
#include <cassert>

CommandAllocator::~CommandAllocator()
{
	if (commandAllocator_)
	{
		commandAllocator_->Release();
		commandAllocator_ = nullptr;
	}
}
[[nodiscard]] bool CommandAllocator::create(const device& device, D3D12_COMMAND_LIST_TYPE type) noexcept
{
	type_ = type;

	HRESULT hr = device.get()->CreateCommandAllocator(type_, IID_PPV_ARGS(&commandAllocator_));
	if (FAILED(hr))
	{
		assert(false && "コマンドアロケーターの作成に失敗しました");
		return false;
	}
	return true;
}

void CommandAllocator::reset() noexcept 
{
	if (!commandAllocator_) 
	{
		assert(false && "コマンドアロケーターが未作成です");
	}

	commandAllocator_->Reset();
}

[[nodiscard]] ID3D12CommandAllocator* CommandAllocator::get() const noexcept
{
	if (!commandAllocator_)
	{
		assert(false && "コマンドアロケーターが未作成です");
	}
	return commandAllocator_;
}

[[nodiscard]] D3D12_COMMAND_LIST_TYPE CommandAllocator::getType() const noexcept
{
	if (!commandAllocator_)
	{
		assert(false && "コマンドアロケーターが未作成です");
	}
	return type_;
}
