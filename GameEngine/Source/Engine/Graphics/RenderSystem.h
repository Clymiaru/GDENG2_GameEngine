#pragma once
#include <d3d11.h>

#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class DeviceContext;
	
	class RenderObject;
	
	class SwapChain;
	
	class VertexBuffer;

	class IndexBuffer;

	class RenderSystem final
	{
	public:
		RenderSystem(const RenderSystem&) = delete;

		static auto Initialize(HWND windowHandle,
		                       Vector2Int windowSize) -> void;

		static auto Terminate() -> void;

		[[nodiscard]]
		static auto GetDevice() -> ID3D11Device&;

		[[nodiscard]]
		static auto GetDeviceContext() -> DeviceContext&;

		//---------- RENDER COMMANDS
		static auto Clear(Color32 fillColor) -> void;

		static auto Draw(const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer) -> void;

		static auto ShowFrame() -> void;

		static auto SetViewportSize(Vector2Uint viewportSize) -> void;

	private:
		RenderSystem();

		~RenderSystem();

		static RenderSystem m_Instance;

		UniquePtr<SwapChain> m_SwapChain;

		UniquePtr<DeviceContext> m_DeviceContext;

		ID3D11Device* m_Device;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		IDXGIDevice* m_DxgiDevice;

		IDXGIAdapter* m_DxgiAdapter;

		IDXGIFactory* m_DxgiFactory;
	};
}
