#pragma once
#include "DeviceContext.h"
#include "SwapChain.h"

//Consider Builder Design
// Since VertexBuffers and the like rely on the renderer/Rendering Device,
// Renderer will handle the construction of it to include the Renderer
namespace Engine
{
	class Renderer final
	{
	public:
		Renderer();
		~Renderer();
		
		void Start(Window& window);

		void End();

		void Clear(const Color& clearColor) const;

		void UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
								  const void* updatedBufferData);
		
		// void Draw(VertexShader& vertexShader,
		// 				 PixelShader& pixelShader,
		// 				 const VertexBuffer& vertexBuffer,
		// 				 const IndexBuffer& indexBuffer,
		// 				 const ConstantBuffer& constantBuffer,
		// 				 const void* updatedConstantBuffer,
		// 				 D3D11_PRIMITIVE_TOPOLOGY topology);

		void ShowFrame() const;

	private:
		
		UniquePtr<SwapChain> m_SwapChain;
		
		UniquePtr<DeviceContext> m_DeviceContext;

		IDXGIDevice* m_DxgiDevice = nullptr;

		IDXGIAdapter* m_DxgiAdapter = nullptr;

		IDXGIFactory* m_DxgiFactory = nullptr;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		ID3D11Device* m_Device = nullptr;
	};
}
