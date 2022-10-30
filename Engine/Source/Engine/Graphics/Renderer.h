#pragma once
#include "DeviceContext.h"
#include "SwapChain.h"

namespace Engine
{
	class Renderer final
	{
	public:
		Renderer(Window& window);

		~Renderer();

		// void End();

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

		HRESULT CreateBuffer(D3D11_BUFFER_DESC* desc,
		                     D3D11_SUBRESOURCE_DATA* resource,
		                     ID3D11Buffer** buffer);

		HRESULT CreateLayout(const D3D11_INPUT_ELEMENT_DESC* desc,
		                     uint32_t elementCount,
		                     const void* shaderByteCode,
		                     uint32_t shaderByteCodeSize,
		                     ID3D11InputLayout** layout);

		HRESULT CreateVertexShader(const void* shaderByteCode,
		                           size_t bytecodeLength,
		                           ID3D11VertexShader** vertexShader) const;

		HRESULT CreatePixelShader(const void* shaderByteCode,
								   size_t bytecodeLength,
								   ID3D11PixelShader** pixelShader) const;

		void ShowFrame() const;

		Renderer(const Renderer&) = delete;
	
		Renderer& operator=(const Renderer& v) = delete;
	
		Renderer(Renderer&&) noexcept = delete;
	
		Renderer& operator=(Renderer&&) noexcept = delete;

	private:
		void CreateDeviceAndContext();
		
		UniquePtr<SwapChain> m_SwapChain;

		UniquePtr<DeviceContext> m_DeviceContext;

		IDXGIDevice* m_DxgiDevice = nullptr;

		IDXGIAdapter* m_DxgiAdapter = nullptr;

		IDXGIFactory* m_DxgiFactory = nullptr;

		D3D_FEATURE_LEVEL m_FeatureLevel;

		ID3D11Device* m_Device = nullptr;
	};
}
