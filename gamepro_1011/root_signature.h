#pragma once

#include"device.h"
class root_signature final
{
	root_signature() = default;

	~root_signature();

	[[nodiscard]] bool create(const device& device) noexcept;

	[[nodiscard]] ID3D12RootSignature* get() const noexcept;

private:
	ID3D12RootSignature* rootSignature_{};
};

