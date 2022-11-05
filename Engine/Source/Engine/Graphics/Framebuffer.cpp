#include "pch.h"
#include "Framebuffer.h"

#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	Framebuffer::Framebuffer(const FramebufferProfile& profile) :
		m_Profile{profile},
		m_RenderTarget{nullptr},
		m_DepthStencilView{nullptr}
	{
		if (profile.ExistingTexture == nullptr)
		{
			m_RenderTarget = new RenderTexture(profile.Width, profile.Height);
		}
		else
		{
			m_RenderTarget = new RenderTexture(profile.ExistingTexture, profile.SwapChainTarget);
		}

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

		HRESULT result = Renderer::GetDevice().CreateTexture2D(&textureDesc, nullptr, &depthStencilTexture);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View Texture cannot be created!");

		result = Renderer::GetDevice().CreateDepthStencilView(depthStencilTexture, nullptr, &m_DepthStencilView);
		Debug::Assert(SUCCEEDED(result), "Depth Stencil View cannot be created!");

		depthStencilTexture->Release();
	}

	Framebuffer::~Framebuffer()
	{
		if (m_DepthStencilView != nullptr)
			m_DepthStencilView->Release();

		delete m_RenderTarget;
	}

	ID3D11Texture2D* Framebuffer::CopyFrameTexture()
	{
		// GetTexture then create a copy from that
		return m_RenderTarget->CopyTexture();
	}
}
