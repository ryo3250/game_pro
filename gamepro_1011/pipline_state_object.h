#pragma once
#include "device.h"
#include "shader.h"
#include "root_signature.h"

class pipline_state_object final
{
public:
	pipline_state_object() = default;

	~pipline_state_object();


	[[nodiscard]] bool create(const device& device, const shader& shader, const root_signature rootSignature) noexcept;

	[[nodiscard]] ID3D12PipelineState* get() const noexcept;

private:
	ID3D12PipelineState* pipelineState_ = {};
};

