#include "pch.h"
#include "Texture.h"

#include "../../Engine/Dependencies/stb/stb_image.h"

namespace Engine
{
	Texture::Texture(ID3D11Device& device,
	                 const Specification& specs) :
		m_Profile{},
		m_TextureView{nullptr},
		m_TextureSampler{nullptr}
	{
		// Load from disk into a raw RGBA buffer
		int imageWidth  = 0;
		int imageHeight = 0;

		unsigned char* imageData = stbi_load(specs.Filepath,
		                                     &imageWidth,
		                                     &imageHeight,
		                                     nullptr,
		                                     4);
		if (imageData == nullptr)
		{
			Debug::Log("Unable to load image {0}!",
			           specs.Filepath);
			// TODO: Block execution to handle null image?
		}

		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width            = imageWidth;
		desc.Height           = imageHeight;
		desc.MipLevels        = 1;
		desc.ArraySize        = 1;
		desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage            = D3D11_USAGE_DEFAULT;
		desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags   = 0;

		ID3D11Texture2D* pTexture = nullptr;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem          = imageData;
		subResource.SysMemPitch      = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		device.CreateTexture2D(&desc, &subResource, &pTexture);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		device.CreateShaderResourceView(pTexture, &srvDesc, &m_TextureView);
		pTexture->Release();

		m_Profile.Width  = imageWidth;
		m_Profile.Height = imageHeight;
		m_Profile.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

		D3D11_SAMPLER_DESC textureSamplerDesc = {};
		textureSamplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		textureSamplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_WRAP;
		textureSamplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_WRAP;
		textureSamplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_WRAP;

		device.CreateSamplerState(&textureSamplerDesc, &m_TextureSampler);

		stbi_image_free(imageData);
	}

	Texture::~Texture()
	{
		if (m_TextureView != nullptr)
			m_TextureView->Release();
	}

	const Texture::Profile& Texture::GetInfo() const
	{
		return m_Profile;
	}

	Texture::Profile Texture::GetInfo()
	{
		return m_Profile;
	}

	ID3D11ShaderResourceView& Texture::GetView() const
	{
		return *m_TextureView;
	}

	ID3D11SamplerState& Texture::GetSampler() const
	{
		return *m_TextureSampler;
	}
}
