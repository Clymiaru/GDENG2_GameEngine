#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

namespace Engine
{
	class DeviceContext;

	class RenderObject;

	class SwapChain;

	class VertexBuffer;

	class IndexBuffer;

	class Window;

	class RenderSystem final
	{
	public:
		RenderSystem(const RenderSystem&) = delete;

		static void Start(Window& window);

		static void End();

		[[nodiscard]]
		static ID3D11Device& GetDevice();

		[[nodiscard]]
		static DeviceContext& GetDeviceContext();

		//---------- RENDER COMMANDS
		static void Clear(Color fillColor);

		static void Draw(const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer);

		static void ShowFrame();

		static void SetViewportSize(Vector2 viewportSize);

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
