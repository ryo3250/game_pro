#include "command_list.h"
#include <cassert>

command_list::~command_list()
{
	if (commandList_)
	{
		commandList_->Release();
		commandList_ = nullptr;
	}
}

[[nodiscard]] bool command_list::create(const device& device, const CommandAllocator& commandAllocator) noexcept 
{
	const auto hr = device.get()->CreateCommandList(0, commandAllocator.getType(), commandAllocator.get(),nullptr,IID_PPV_ARGS(&commandList_));
	if (FAILED(hr))
	{
		assert(false && "コマンドリストの作成に失敗しました");
		return false;
	}

	commandList_->Close();
	return true;
	
}

void command_list::reset(const CommandAllocator& cmmandAllocator) noexcept 
{
	if (!commandList_) 
	{
		assert(false && "コマンドリストが未作成です");
	}

	commandList_->Reset(cmmandAllocator.get(), nullptr);
}

[[nodiscard]] ID3D12GraphicsCommandList* command_list::get() const noexcept 
{
	if (!commandList_) 
	{
		assert(false && "コマンドリストが未作成です");
	}
	return commandList_;
}

