#pragma once

#include "device.h"
#include "command_list.h"

class triangle_polygon
{
public:
	triangle_polygon() = default;

	~triangle_polygon();

	[[nodiscard]] bool cerate(const device& device) noexcept;

	[[nodiscard]] void draw(const command_list& commandList)noexcept;

private:

	[[nodiscard]] bool createVertexBuffer(const device& device)noexcept;

	[[nodiscard]] bool createIndexBuffer(const device& device)noexcept;

private:
	ID3D12Resource* vertexBuffer_{};
	ID3D12Resource* indexBuffer_{};

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView_ = {};
	D3D12_INDEX_BUFFER_VIEW indexBufferView_ = {};
};

