#pragma once
#include <d3d11.h>

#include "SwapChain.h"

#include "Buffer/VertexBuffer.h"
#include "Buffer/IndexBuffer.h"
#include "Buffer/ConstantBuffer.h"

#include "Texture/RenderTexture.h"
#include "Texture/Texture.h"

namespace Engine
{
	// Responsible of creating resources for DirectX
	class RenderDevice final
	{
	public:
		explicit RenderDevice(ID3D11Device* device);

		~RenderDevice();

		SwapChain* CreateSwapChain(Window& window) const;

		template <typename RenderResource, typename... Args>
		RenderResource* Create(Args ... args);

		// CreateVertexShader
		// CreatePixelShader

		RenderDevice(const RenderDevice&)                = delete;
		RenderDevice& operator=(const RenderDevice&)     = delete;
		RenderDevice(RenderDevice&&) noexcept            = delete;
		RenderDevice& operator=(RenderDevice&&) noexcept = delete;

	private:
		ID3D11Device* m_Device;
		IDXGIDevice* m_DxgiDevice;
		IDXGIAdapter* m_DxgiAdapter;
		IDXGIFactory* m_DxgiFactory;
	};

	template <typename RenderResource, typename ... Args>
	RenderResource* RenderDevice::Create(Args ... args)
	{
		Debug::Log("Attempting to create an unimplemented render resource!");
		return nullptr;
	}

	// CreateSwapChain
	template <>
	inline SwapChain* RenderDevice::Create<SwapChain>(Window& window)
	{
		return new SwapChain(window, m_Device, m_DxgiFactory);
	}

	// CreateVertexBuffer
	template <>
	inline VertexBuffer* RenderDevice::Create<VertexBuffer>(const RenderData& renderDataRef,
	                                                        const Shader& shaderRef)
	{
		return new VertexBuffer(*m_Device, renderDataRef, shaderRef);
	}

	// CreateIndexBuffer
	template <>
	inline IndexBuffer* RenderDevice::Create<IndexBuffer>(const RenderData& renderDataRef)
	{
		return new IndexBuffer(*m_Device, renderDataRef);
	}

	// CreateConstantBuffer
	template <>
	inline ConstantBuffer* RenderDevice::Create<ConstantBuffer>(const void* bufferData,
	                                                            const size_t bufferSize)
	{
		return new ConstantBuffer(*m_Device, bufferData, bufferSize);
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
