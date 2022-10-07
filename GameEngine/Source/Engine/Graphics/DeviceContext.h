#pragma once
#include <d3d11.h>

#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class SwapChain;

	class VertexBuffer;

	class IndexBuffer;

	class ConstantBuffer;

	class VertexShader;

	class PixelShader;

	class DeviceContext final
	{
	public:
		explicit DeviceContext(ID3D11DeviceContext* deviceContext);

		~DeviceContext();

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto Clear(const SwapChain& swapChain,
		           Color32 color) const -> void;

		auto SetViewportSize(Vector2Uint size) const -> void;

		// Buffers
		auto SetVertexBuffer(const VertexBuffer& vertexBuffer) const -> void;

		auto SetIndexBuffer(const IndexBuffer& indexBuffer) const -> void;

		auto SetConstantBuffer(const VertexShader& vertexShader,
		                       const ConstantBuffer& constantBuffer) const -> void;

		auto SetConstantBuffer(const PixelShader& pixelShader,
		                       const ConstantBuffer& constantBuffer) const -> void;

		// Shaders
		auto SetVertexShader(const std::wstring& filename) const -> void;

		auto SetPixelShader(const std::wstring& filename) const -> void;

		// Draw
		auto DrawTriangleList(Uint indexCount,
		                      Uint startingIndex) const -> void;

	private:
		ID3D11DeviceContext* m_DeviceContext;

		friend class ConstantBuffer;
	};
}
