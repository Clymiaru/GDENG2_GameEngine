#pragma once
#include <d3d11.h>
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class SwapChain;

	class VertexBuffer;

	class VertexShader;

	class PixelShader;

	class DeviceContext final
	{
	public:
		explicit DeviceContext(ID3D11DeviceContext* deviceContext);

		~DeviceContext() = default;

		auto Release() const -> void;

		auto ClearRenderTarget(const Scope<SwapChain>& swapChain,
		                       const Color32 color) const -> void;

		auto SetVertexBuffer(const Scope<VertexBuffer>& vertexBuffer) const -> void;

		auto SetVertexShader(const Scope<VertexShader>& vertexShader) const -> void;

		auto SetPixelShader(const Scope<PixelShader>& pixelShader) const -> void;

		auto DrawTriangleList(UINT vertexCount,
		                      UINT startVertexIndex) const -> void;

		auto DrawTriangleStrip(UINT vertexCount,
		                       UINT startVertexIndex) const -> void;

		auto SetViewportSize(UINT width,
		                     UINT height) const -> void;

	private:
		ID3D11DeviceContext* m_DeviceContext;
	};
}
