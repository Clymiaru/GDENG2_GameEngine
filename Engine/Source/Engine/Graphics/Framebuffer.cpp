#include "pch.h"
#include "Framebuffer.h"
#include "Renderer.h"

namespace Engine
{
	Framebuffer::Framebuffer(const FramebufferProfile& profile,
	                         ID3D11Device& device) :
		m_Profile{profile},
		m_RenderTarget{nullptr},
		m_DepthStencilView{nullptr}
	{
		m_RenderTarget = profile.ExistingTexture == nullptr ?
			                 CreateUniquePtr<RenderTexture>(profile.Width, profile.Height) :
			                 CreateUniquePtr<RenderTexture>(profile.ExistingTexture, profile.SwapChainTarget);

		ID3D11Texture2D* depthStencilTexture = nullptr;
		D3D11_TEXTURE2D_DESC depthStencilTextureDesc;
		depthStencilTextureDesc.Width              = profile.Width;
		depthStencilTextureDesc.Height             = profile.Height;
		depthStencilTextureDesc.Format             = DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilTextureDesc.Usage              = D3D11_USAGE_DEFAULT;
		depthStencilTextureDesc.BindFlags          = D3D11_BIND_DEPTH_STENCIL;
		depthStencilTextureDesc.MipLevels          = 1;
		depthStencilTextureDesc.SampleDesc.Count   = 1;
		depthStencilTextureDesc.SampleDesc.Quality = 0;
		depthStencilTextureDesc.MiscFlags          = 0;
		depthStencilTextureDesc.ArraySize          = 1;
		depthStencilTextureDesc.CPUAccessFlags     = 0;

		HRESULT result = device.CreateTexture2D(&depthStencilTextureDesc, nullptr, &depthStencilTexture);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View Texture cannot be created!");

		result = device.CreateDepthStencilView(depthStencilTexture, nullptr, &m_DepthStencilView);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View cannot be created!");

		depthStencilTexture->Release();
	}

	Framebuffer::~Framebuffer()
	{
		if (m_DepthStencilView != nullptr)
			m_DepthStencilView->Release();
	}
}
