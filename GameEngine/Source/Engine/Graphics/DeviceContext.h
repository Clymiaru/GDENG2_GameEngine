#pragma once
#include <d3d11.h>
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
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

		auto Clear(const UniquePtr<SwapChain>& swapChain,
		           Color32 color) const -> void;

		auto SetViewportSize(Vector2Uint size) const -> void;

		// Buffers
		auto SetVertexBuffer(const UniquePtr<VertexBuffer>& vertexBuffer) const -> void;

		auto SetConstantBuffer(const SharedPtr<VertexShader>& vertexShader,
		                       const UniquePtr<ConstantBuffer>& constantBuffer) const -> void;

		auto SetConstantBuffer(const SharedPtr<PixelShader>& pixelShader,
		                       const UniquePtr<ConstantBuffer>& constantBuffer) const -> void;

		// Shaders
		auto SetVertexShader(const std::wstring& filename) const -> void;

		auto SetPixelShader(const std::wstring& filename) const -> void;

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
