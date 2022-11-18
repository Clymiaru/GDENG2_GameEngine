#pragma once
#include <d3d11.h>
#include "Engine/Core/Debug.h"

#include "SwapChain.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/ConstantBuffer.h"

#include "Shader/PixelShader.h"
#include "Shader/VertexShader.h"

#include "Texture/RenderTexture.h"
#include "Texture/Texture.h"

namespace Engine
{
	class UISystem;
	// Responsible of creating resources for DirectX
	class RenderDevice final
	{
	public:
		explicit RenderDevice(ID3D11Device* device);

		~RenderDevice();

		SwapChain* CreateSwapChain(Window& window) const;

		template <typename RenderResource, typename... Args>
		RenderResource* Create(Args ... args);

		UniquePtr<VertexBuffer> CreateVertexBuffer(RenderData& renderData,
		                                           VertexShader& vertexShader) const;
		
		UniquePtr<IndexBuffer> CreateIndexBuffer(RenderData& renderData) const;
		
		UniquePtr<ConstantBuffer> CreateConstantBuffer(const void* bufferData,
		                                               const size_t bufferSize) const;

		UniquePtr<VertexShader> CreateVertexShader(ID3DBlob* vertexShaderBlob) const;
		UniquePtr<PixelShader> CreatePixelShader(ID3DBlob* pixelShaderBlob) const;

		RenderDevice(const RenderDevice&)                = delete;
		RenderDevice& operator=(const RenderDevice&)     = delete;
		RenderDevice(RenderDevice&&) noexcept            = delete;
		RenderDevice& operator=(RenderDevice&&) noexcept = delete;

	private:
		ID3D11Device* m_Device;
		IDXGIDevice* m_DxgiDevice;
		IDXGIAdapter* m_DxgiAdapter;
		IDXGIFactory* m_DxgiFactory;

		// Hack: UISystem needs Device
		friend class UISystem;
	};

	template <typename RenderResource, typename ... Args>
	RenderResource* RenderDevice::Create(Args ... args)
	{
		Debug::Log("Attempting to create an unimplemented render resource!");
		return nullptr;
	}

	// CreateTexture
	template <>
	inline Texture* RenderDevice::Create<Texture>(const Texture::Specification& specs)
	{
		return new Texture(*m_Device, specs);
	}

	// CreateRenderTexture
	template <>
	inline RenderTexture* RenderDevice::Create<RenderTexture>(const uint32_t width,
	                                                          const uint32_t height)
	{
		return new RenderTexture(*m_Device, width, height);
	}

	// CreateRenderTexture - ExistingTexture
	template <>
	inline RenderTexture* RenderDevice::Create<RenderTexture>(ID3D11Texture2D* existingTexture,
	                                                          bool isSwapChainTexture)
	{
		return new RenderTexture(*m_Device, existingTexture, isSwapChainTexture);
	}
}
