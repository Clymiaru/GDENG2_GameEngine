#pragma once
#include "DeviceContext.h"
#include "SwapChain.h"
#include "Engine/Core/Core.h"

namespace Engine
{
	class Renderer final
	{
	public:
		static void Start(Window& window);

		static void End();

		// Takes in the Framebuffer to clear then set it as current render target
		static void StartRender(const Framebuffer& framebuffer);

		// Removes the bound framebuffer as rendertarget
		static void EndRender(const Framebuffer& framebuffer);

		static void ClearFramebuffer(const Framebuffer& framebuffer);

		static void ClearRenderTarget(ID3D11RenderTargetView* renderTargetView,
		                              const Color& clearColor);

		static void ClearDepthStencil(ID3D11DepthStencilView* depthStencilView);

		static void SetRenderTargetTo(ID3D11RenderTargetView* renderTarget,
		                            ID3D11DepthStencilView* depthStencil);

		static void ShowFrame();

		static void UpdateConstantBuffer(const ConstantBuffer& constantBuffer,
		                                 const void* updatedBufferData);

		static void Draw(const VertexShader& vertexShader,
		                 const PixelShader& pixelShader,
		                 const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer,
		                 D3D11_PRIMITIVE_TOPOLOGY topology);

		static void Draw(const VertexShader& vertexShader,
		                 const PixelShader& pixelShader,
		                 const VertexBuffer& vertexBuffer,
		                 const IndexBuffer& indexBuffer,
		                 const ConstantBuffer& constantBuffer,
		                 const void* updatedConstantBuffer,
		                 D3D11_PRIMITIVE_TOPOLOGY topology);

		static HRESULT CreateBuffer(const D3D11_BUFFER_DESC* desc,
		                            const D3D11_SUBRESOURCE_DATA* resource,
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

		static void Resize(Vector2Uint& size);


		// Raster Stage
		static void SetViewportSize(const Vector2Int& viewportSize);

		static ID3D11Device& GetDevice()
		{
			return *s_Device;
		};

		static SwapChain& GetSwapChain()
		{
			return *s_SwapChain;
		};

		static DeviceContext& GetDeviceContext()
		{
			return *s_DeviceContext;
		};

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
