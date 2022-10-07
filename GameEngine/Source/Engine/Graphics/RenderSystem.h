#pragma once
#include <d3d11.h>

#include "Engine/Graphics/SwapChain.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class RenderObject;

	class VertexBuffer;

	class IndexBuffer;

	class RenderSystem final
	{
	public:
		RenderSystem(const RenderSystem&) = delete;

		static auto GetInstance() -> RenderSystem&;

		auto Initialize(HWND windowHandle,
		                Vector2Int windowSize) -> void;

		auto Terminate() const -> void;

		[[nodiscard]]
		auto GetDevice() const -> ID3D11Device&;

		[[nodiscard]]
		auto GetDeviceContext() const -> DeviceContext&;

		auto Clear(Color32 fillColor) const -> void;

		auto Draw(const VertexBuffer& vertexBuffer,
		          const IndexBuffer& indexBuffer) const -> void;

		auto ShowFrame() const -> void;

		auto SetViewportSize(Vector2Uint viewportSize) const -> void;

	private:
		RenderSystem();

		~RenderSystem();

		UniquePtr<SwapChain> m_SwapChain;

		UniquePtr<DeviceContext> m_DeviceContext;

		ID3D11Device* m_Device;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;
	};
}
