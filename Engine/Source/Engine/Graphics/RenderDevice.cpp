#include "pch.h"
#include "RenderDevice.h"

namespace Engine
{
	RenderDevice::RenderDevice(ID3D11Device* device) :
		m_Device{device},
		m_DxgiDevice{nullptr},
		m_DxgiAdapter{nullptr},
		m_DxgiFactory{nullptr}

	{
		m_Device->QueryInterface(__uuidof(IDXGIDevice),
		                         reinterpret_cast<void**>(&m_DxgiDevice));

		m_DxgiDevice->GetParent(__uuidof(IDXGIAdapter),
		                        reinterpret_cast<void**>(&m_DxgiAdapter));

		m_DxgiAdapter->GetParent(__uuidof(IDXGIFactory),
		                         reinterpret_cast<void**>(&m_DxgiFactory));
	}

	RenderDevice::~RenderDevice()
	{
		m_DxgiAdapter->Release();
		m_DxgiDevice->Release();
		m_DxgiFactory->Release();
		m_Device->Release();
	}

	SwapChain* RenderDevice::CreateSwapChain(Window& window) const
	{
		return new SwapChain(window, m_Device, m_DxgiFactory);
	}

	UniquePtr<VertexBuffer> RenderDevice::CreateVertexBuffer(RenderData& renderData,
	                                                         VertexShader& vertexShader) const
	{
		return CreateUniquePtr<VertexBuffer>(*m_Device, renderData, vertexShader);
	}

	UniquePtr<IndexBuffer> RenderDevice::CreateIndexBuffer(RenderData& renderData) const
	{
		return CreateUniquePtr<IndexBuffer>(*m_Device, renderData);
	}

	UniquePtr<ConstantBuffer> RenderDevice::CreateConstantBuffer(const void* bufferData,
	                                                             const size_t bufferSize) const
	{
		return CreateUniquePtr<ConstantBuffer>(*m_Device, bufferData, bufferSize);
	}

	UniquePtr<VertexShader> RenderDevice::CreateVertexShader(ID3DBlob* vertexShaderBlob) const
	{
		return CreateUniquePtr<VertexShader>(*m_Device, vertexShaderBlob);
	}

	UniquePtr<PixelShader> RenderDevice::CreatePixelShader(ID3DBlob* pixelShaderBlob) const
	{
		return CreateUniquePtr<PixelShader>(*m_Device, pixelShaderBlob);
	}
	
	UniquePtr<Texture> RenderDevice::CreateTexture(const Texture::Specification& specs) const
	{
		return CreateUniquePtr<Texture>(*m_Device, specs);
	}

	UniquePtr<Framebuffer> RenderDevice::CreateFramebuffer(const FramebufferProfile& profile) const
	{
		return CreateUniquePtr<Framebuffer>(*m_Device, profile);
	}
}
