#include "pch.h"
#include "Framebuffer.h"

#include "Renderer.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Debug.h"

namespace Engine
{
	Framebuffer::Framebuffer(const FramebufferProfile& profile) :
		m_Profile{profile}
	{
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width = profile.Width;
		desc.Height = profile.Height;
		desc.MipLevels = 1;
		desc.ArraySize = 1;
		desc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		desc.SampleDesc.Count = 1;
		desc.Usage = D3D11_USAGE_DEFAULT;
		desc.BindFlags = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags = 0;
		desc.MiscFlags = 0;

		HRESULT result = Renderer::GetDevice().CreateTexture2D(&desc, nullptr, &m_FrameTexture);
		Debug::Assert(SUCCEEDED(result), "Frame texture cannot be created!");

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc;
		rtvDesc.Format = desc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		result = Renderer::GetDevice().CreateRenderTargetView(m_FrameTexture, &rtvDesc, &m_RenderTargetView);
		Debug::Assert(SUCCEEDED(result), "Render Target View cannot be created!");

		ID3D11Texture2D* depthStencilTexture = nullptr;
		D3D11_TEXTURE2D_DESC textureDesc     = {};
		textureDesc.Width                    = profile.Width;
		textureDesc.Height                   = profile.Height;
		textureDesc.Format                   = DXGI_FORMAT_D24_UNORM_S8_UINT;
		textureDesc.Usage                    = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags                = D3D11_BIND_DEPTH_STENCIL;
		textureDesc.MipLevels                = 1;
		textureDesc.SampleDesc.Count         = 1;
		textureDesc.SampleDesc.Quality       = 0;
		textureDesc.MiscFlags                = 0;
		textureDesc.ArraySize                = 1;
		textureDesc.CPUAccessFlags           = 0;
		
		result = Renderer::GetDevice().CreateTexture2D(&textureDesc, nullptr, &depthStencilTexture);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View Texture cannot be created!");

		result = Renderer::GetDevice().CreateDepthStencilView(depthStencilTexture, nullptr, &m_DepthStencilView);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View cannot be created!");
		
		depthStencilTexture->Release();
			
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format = desc.Format;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;
		
		result = Renderer::GetDevice().CreateShaderResourceView(m_FrameTexture, &srvDesc, &m_ShaderResourceView);
		Debug::Assert(SUCCEEDED(result), "Shader Resource View cannot be created!");

	}

	Framebuffer::~Framebuffer()
	{
		if (m_ShaderResourceView != nullptr)
			m_ShaderResourceView->Release();
		
		if (m_RenderTargetView != nullptr)
			m_RenderTargetView->Release();

		if (m_DepthStencilView != nullptr)
			m_DepthStencilView->Release();

		if (m_FrameTexture != nullptr)
			m_FrameTexture->Release();
	}

	ID3D11ShaderResourceView& Framebuffer::GetShaderResourceView() const
	{
		return *m_ShaderResourceView;
	}

	ID3D11RenderTargetView& Framebuffer::GetRenderTargetView() const
	{
		return *m_RenderTargetView;
	}

	ID3D11DepthStencilView& Framebuffer::GetDepthStencilView() const
	{
		return *m_DepthStencilView;
	}

	void Framebuffer::ClearRenderTarget(const Color& clearColor) const
	{
		Renderer::ClearRenderTarget(m_RenderTargetView, clearColor);
	}

	void Framebuffer::ClearDepthStencil() const
	{
		Renderer::ClearDepthStencil(m_DepthStencilView);
	}
}
