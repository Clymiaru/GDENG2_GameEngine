#pragma once
#include "DeviceContext.h"
#include "SwapChain.h"

namespace Engine
{
	// Make this a static class
	class Renderer final
	{
	public:
		static void Start(Window& window);

		static void End();

		static void Clear(const Color& clearColor);

		static void ShowFrame();

		// void UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
		//                           const void* updatedBufferData);

		// void Draw(VertexShader& vertexShader,
		// 				 PixelShader& pixelShader,
		// 				 const VertexBuffer& vertexBuffer,
		// 				 const IndexBuffer& indexBuffer,
		// 				 const ConstantBuffer& constantBuffer,
		// 				 const void* updatedConstantBuffer,
		// 				 D3D11_PRIMITIVE_TOPOLOGY topology);

		static HRESULT CreateBuffer(D3D11_BUFFER_DESC* desc,
		                            D3D11_SUBRESOURCE_DATA* resource,
		                            ID3D11Buffer** buffer);

		static HRESULT CreateLayout(const D3D11_INPUT_ELEMENT_DESC* desc,
		                            uint32_t elementCount,
		                            const void* shaderByteCode,
		                            uint32_t shaderByteCodeSize,
		                            ID3D11InputLayout** layout);

		static HRESULT CreateVertexShader(const void* shaderByteCode,
		                                  size_t bytecodeLength,
		                                  ID3D11VertexShader** vertexShader);

		static HRESULT CreatePixelShader(const void* shaderByteCode,
		                                 size_t bytecodeLength,
		                                 ID3D11PixelShader** pixelShader);

		Renderer(const Renderer&) = delete;

		Renderer& operator=(const Renderer&) = delete;

		Renderer(Renderer&&) noexcept = delete;

		Renderer& operator=(Renderer&&) noexcept = delete;

	private:
		static UniquePtr<SwapChain> s_SwapChain;

		static UniquePtr<DeviceContext> s_DeviceContext;

		static IDXGIDevice* s_DxgiDevice;

		static IDXGIAdapter* s_DxgiAdapter;

		static IDXGIFactory* s_DxgiFactory;

		static D3D_FEATURE_LEVEL s_FeatureLevel;

		static ID3D11Device* s_Device;
	};
}
