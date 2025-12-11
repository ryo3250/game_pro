#pragma once

#include"device.h"

class command_queue final
{
	command_queue() = default;

	~command_queue();

	[[nodiscard]] bool create(const device& device) noexcept;

	[[nodiscard]] ID3D12CommandQueue* get() const noexcept;

private:
	ID3D12CommandQueue* commandQueue_{};
};

