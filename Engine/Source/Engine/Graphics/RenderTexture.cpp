#include "pch.h"
#include "RenderTexture.h"

#include "Renderer.h"
#include "Engine/Core/Debug.h"

namespace Engine
{
	RenderTexture::RenderTexture(const uint32_t width,
	                             const uint32_t height) :
		m_RenderTarget{nullptr},
		m_View{nullptr}
	{
		ID3D11Texture2D* renderTargetTexture;
		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		ZeroMemory(&renderTargetTextureDesc, sizeof(renderTargetTextureDesc));
		renderTargetTextureDesc.Width            = width;
		renderTargetTextureDesc.Height           = height;
		renderTargetTextureDesc.MipLevels        = 1;
		renderTargetTextureDesc.ArraySize        = 1;
		renderTargetTextureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		renderTargetTextureDesc.SampleDesc.Count = 1;
		renderTargetTextureDesc.Usage            = D3D11_USAGE_DEFAULT;
		renderTargetTextureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTextureDesc.CPUAccessFlags   = 0;
		renderTargetTextureDesc.MiscFlags        = 0;

		HRESULT result = Renderer::GetDevice().CreateTexture2D(&renderTargetTextureDesc,
		                                                       nullptr,
		                                                       &renderTargetTexture);
		Debug::Assert(SUCCEEDED(result), "Frame texture cannot be created!");

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		renderTargetDesc.Format             = renderTargetTextureDesc.Format;
		renderTargetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetDesc.Texture2D.MipSlice = 0;

		result = Renderer::GetDevice().CreateRenderTargetView(renderTargetTexture, &renderTargetDesc, &m_RenderTarget);
		Debug::Assert(SUCCEEDED(result), "Render Target View cannot be created!");
		renderTargetTexture->Release();

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = renderTargetTextureDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		result = Renderer::GetDevice().CreateShaderResourceView(renderTargetTexture, &srvDesc, &m_View);
		Debug::Assert(SUCCEEDED(result), "Shader Resource View cannot be created!");
	}

	RenderTexture::RenderTexture(ID3D11Texture2D* existingTexture,
	                             bool isSwapChainTexture) :
		m_RenderTarget{nullptr},
		m_View{nullptr}
	{
		D3D11_TEXTURE2D_DESC existingTextureDesc;
		existingTexture->GetDesc(&existingTextureDesc);

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		renderTargetDesc.Format             = existingTextureDesc.Format;
		renderTargetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetDesc.Texture2D.MipSlice = 0;

		HRESULT result = Renderer::GetDevice().CreateRenderTargetView(existingTexture, &renderTargetDesc,
		                                                              &m_RenderTarget);
		Debug::Assert(SUCCEEDED(result), "Render Target View cannot be created!");
		existingTexture->Release();

		if (isSwapChainTexture)
			return;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = existingTextureDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		result = Renderer::GetDevice().CreateShaderResourceView(existingTexture, &srvDesc, &m_View);
		Debug::Assert(SUCCEEDED(result), "Shader Resource View cannot be created!");
	}

	RenderTexture::RenderTexture(ID3D11ShaderResourceView& existingTextureView,
	                             bool isSwapChainTexture)
	{
		ID3D11Texture2D* existingTexture = nullptr;
		ID3D11Resource* existingTextureResource;
		existingTextureView.GetResource(&existingTextureResource);

		// Check if there is a resource

		D3D11_RESOURCE_DIMENSION existingResourceDimension;
		existingTextureResource->GetType(&existingResourceDimension);

		if (existingResourceDimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
		{
			// What to do if the resource is not a texture2D
		}

		D3D11_TEXTURE2D_DESC existingTextureDesc;
		existingTexture = (ID3D11Texture2D*)existingTextureResource;
		existingTexture->GetDesc(&existingTextureDesc);

		ID3D11Texture2D* renderTargetTexture;
		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		ZeroMemory(&renderTargetTextureDesc, sizeof(renderTargetTextureDesc));
		renderTargetTextureDesc.Width            = existingTextureDesc.Width;
		renderTargetTextureDesc.Height           = existingTextureDesc.Height;
		renderTargetTextureDesc.MipLevels        = 1;
		renderTargetTextureDesc.ArraySize        = 1;
		renderTargetTextureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		renderTargetTextureDesc.SampleDesc.Count = 1;
		renderTargetTextureDesc.Usage            = D3D11_USAGE_DEFAULT;
		renderTargetTextureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTextureDesc.CPUAccessFlags   = 0;
		renderTargetTextureDesc.MiscFlags        = 0;

		HRESULT result = Renderer::GetDevice().CreateTexture2D(&renderTargetTextureDesc, nullptr, &renderTargetTexture);
		Debug::Assert(SUCCEEDED(result), "Frame texture cannot be created!");

		D3D11_RENDER_TARGET_VIEW_DESC renderTargetDesc;
		renderTargetDesc.Format             = existingTextureDesc.Format;
		renderTargetDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
		renderTargetDesc.Texture2D.MipSlice = 0;

		result = Renderer::GetDevice().CreateRenderTargetView(renderTargetTexture, &renderTargetDesc,
		                                                      &m_RenderTarget);
		Debug::Assert(SUCCEEDED(result), "Render Target View cannot be created!");
		//Don't release as this resource comes from elsewhere
		renderTargetTexture->Release();

		if (isSwapChainTexture)
			return;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = existingTextureDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = 1;
		srvDesc.Texture2D.MostDetailedMip = 0;

		result = Renderer::GetDevice().CreateShaderResourceView(existingTexture, &srvDesc, &m_View);
		Debug::Assert(SUCCEEDED(result), "Shader Resource View cannot be created!");
	}

	RenderTexture::~RenderTexture()
	{
		if (m_View != nullptr)
			m_View->Release();

		if (m_RenderTarget != nullptr)
			m_RenderTarget->Release();
	}

	ID3D11Texture2D* RenderTexture::CopyTexture()
	{
		ID3D11Texture2D* existingTexture = nullptr;
		ID3D11Resource* existingTextureResource;
		m_View->GetResource(&existingTextureResource);

		// Check if there is a resource

		D3D11_RESOURCE_DIMENSION existingResourceDimension;
		existingTextureResource->GetType(&existingResourceDimension);

		if (existingResourceDimension != D3D11_RESOURCE_DIMENSION_TEXTURE2D)
		{
			// What to do if the resource is not a texture2D
		}

		D3D11_TEXTURE2D_DESC existingTextureDesc;
		existingTexture = (ID3D11Texture2D*)existingTextureResource;
		existingTexture->GetDesc(&existingTextureDesc);

		ID3D11Texture2D* renderTargetTexture;
		D3D11_TEXTURE2D_DESC renderTargetTextureDesc;
		ZeroMemory(&renderTargetTextureDesc, sizeof(renderTargetTextureDesc));
		renderTargetTextureDesc.Width            = existingTextureDesc.Width;
		renderTargetTextureDesc.Height           = existingTextureDesc.Height;
		renderTargetTextureDesc.MipLevels        = 1;
		renderTargetTextureDesc.ArraySize        = 1;
		renderTargetTextureDesc.Format           = DXGI_FORMAT_R32G32B32A32_FLOAT;
		renderTargetTextureDesc.SampleDesc.Count = 1;
		renderTargetTextureDesc.Usage            = D3D11_USAGE_DEFAULT;
		renderTargetTextureDesc.BindFlags        = D3D11_BIND_RENDER_TARGET | D3D11_BIND_SHADER_RESOURCE;
		renderTargetTextureDesc.CPUAccessFlags   = 0;
		renderTargetTextureDesc.MiscFlags        = 0;

		HRESULT result = Renderer::GetDevice().CreateTexture2D(&renderTargetTextureDesc, nullptr, &renderTargetTexture);
		Debug::Assert(SUCCEEDED(result), "Frame texture cannot be created!");

		return renderTargetTexture;
	}
}
