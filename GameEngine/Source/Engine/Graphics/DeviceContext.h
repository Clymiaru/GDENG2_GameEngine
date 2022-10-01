#pragma once
#include <d3d11.h>
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class SwapChain;

	class VertexBuffer;

	class ConstantBuffer;

	class VertexShader;

	class PixelShader;

	class DeviceContext final
	{
	public:
		explicit DeviceContext(ID3D11DeviceContext* deviceContext);

		~DeviceContext() = default;

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto Clear(const ScopePtr<SwapChain>& swapChain,
		           Color32 color) const -> void;

		auto SetViewportSize(UINT width,
		                     UINT height) const -> void;

		// Buffers
		auto SetVertexBuffer(const ScopePtr<VertexBuffer>& vertexBuffer) const -> void;

		auto SetConstantBuffer(const ScopePtr<VertexShader>& vertexShader,
		                       const ScopePtr<ConstantBuffer>& constantBuffer) const -> void;

		auto SetConstantBuffer(const ScopePtr<PixelShader>& pixelShader,
		                       const ScopePtr<ConstantBuffer>& constantBuffer) const -> void;

		// Shaders
		auto SetVertexShader(const ScopePtr<VertexShader>& vertexShader) const -> void;

		auto SetPixelShader(const ScopePtr<PixelShader>& pixelShader) const -> void;

		// Draw
		auto DrawTriangleList(UINT vertexCount,
		                      UINT startVertexIndex) const -> void;

		auto DrawTriangleStrip(UINT vertexCount,
		                       UINT startVertexIndex) const -> void;

	private:
		ID3D11DeviceContext* m_DeviceContext;

		friend class ConstantBuffer;
	};
}
