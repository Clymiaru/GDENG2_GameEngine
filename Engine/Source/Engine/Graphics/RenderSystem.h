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

		static void Initialize(HWND windowHandle,
		                       Vector2Int windowSize);

		static void Terminate();

		[[nodiscard]]
		static ID3D11Device& GetDevice();

		[[nodiscard]]
		static DeviceContext& GetDeviceContext();

		//---------- RENDER COMMANDS
		static void Clear(Color32 fillColor);

		static void Draw(const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer);

		static void ShowFrame();

		static void SetViewportSize(Vector2Uint viewportSize);

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
