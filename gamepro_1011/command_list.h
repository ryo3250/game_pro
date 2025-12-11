#pragma once

#include "CommandAllocator.h"
#include "device.h"

class command_list final
{
public:
	command_list() = default;

	~command_list();

	[[nodiscard]] bool create(const device& device,const CommandAllocator& commandAllocator) noexcept;

	void reset(const CommandAllocator& cmmandAllocator) noexcept;

	[[nodiscard]] ID3D12GraphicsCommandList* get() const noexcept;

private:
	ID3D12GraphicsCommandList* commandList_{};
};

