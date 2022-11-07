#include "pch.h"
#include "RenderComponent.h"
#include "TransformComponent.h"

#include "Engine/ECS/Core/Entity.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/ECS/Entity/Camera.h"

#include "Engine/stb_image.h"

__declspec(align(16))
struct RenderObjectData
{
	Engine::Matrix4 Model;

	Engine::Matrix4 ViewProjection;

	Engine::Color SolidColor;
};

namespace Engine
{
	// From: https://github.com/ocornut/imgui/wiki/Image-Loading-and-Displaying-Examples#Example-for-DirectX11-users
	bool LoadTextureFromFile(const char* filename,
	                         ID3D11ShaderResourceView** out_srv,
	                         int* out_width,
	                         int* out_height)
	{
		// Load from disk into a raw RGBA buffer
		int image_width           = 0;
		int image_height          = 0;
		unsigned char* image_data = stbi_load(filename, &image_width, &image_height, NULL, 4);
		if (image_data == NULL)
			return false;

		// Create texture
		D3D11_TEXTURE2D_DESC desc;
		ZeroMemory(&desc, sizeof(desc));
		desc.Width            = image_width;
		desc.Height           = image_height;
		desc.MipLevels        = 1;
		desc.ArraySize        = 1;
		desc.Format           = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.SampleDesc.Count = 1;
		desc.Usage            = D3D11_USAGE_DEFAULT;
		desc.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
		desc.CPUAccessFlags   = 0;

		ID3D11Texture2D* pTexture = NULL;
		D3D11_SUBRESOURCE_DATA subResource;
		subResource.pSysMem          = image_data;
		subResource.SysMemPitch      = desc.Width * 4;
		subResource.SysMemSlicePitch = 0;
		Renderer::GetDevice().CreateTexture2D(&desc, &subResource, &pTexture);

		// Create texture view
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		ZeroMemory(&srvDesc, sizeof(srvDesc));
		srvDesc.Format                    = DXGI_FORMAT_R8G8B8A8_UNORM;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MipLevels       = desc.MipLevels;
		srvDesc.Texture2D.MostDetailedMip = 0;
		Renderer::GetDevice().CreateShaderResourceView(pTexture, &srvDesc, out_srv);
		pTexture->Release();

		*out_width  = image_width;
		*out_height = image_height;
		stbi_image_free(image_data);

		return true;
	}

	RenderComponent::RenderComponent(Entity& owner,
	                                 RenderData* renderData,
	                                 SharedPtr<VertexShader> vertexShader,
	                                 SharedPtr<PixelShader> pixelShader) :
		AComponent{owner},
		m_RenderData{std::move(renderData)},
		m_VertexShader{vertexShader},
		m_PixelShader{pixelShader},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr}
	{
		if (renderData == nullptr)
		{
			Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
			           owner.Name.c_str());
			return;
		}

		RenderObjectData* constant = new RenderObjectData();

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
		                                               *m_VertexShader);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant,
		                                                   sizeof(RenderObjectData));
	}

	RenderComponent::RenderComponent(Entity& owner,
	                                 RenderData* renderData,
	                                 SharedPtr<VertexShader> vertexShader,
	                                 SharedPtr<PixelShader> pixelShader,
	                                 StringView textureFilepath) :
		AComponent{owner},
		m_RenderData{std::move(renderData)},
		m_VertexShader{vertexShader},
		m_PixelShader{pixelShader},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr},
		m_HasTexture{true}
	{
		if (renderData == nullptr)
		{
			Debug::Log("Attempting to Attach a RenderComponent to {0} with null RenderData!",
			           owner.Name.c_str());
			return;
		}

		RenderObjectData* constant = new RenderObjectData();

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
		                                               *m_VertexShader);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant,
		                                                   sizeof(RenderObjectData));

		LoadTextureFromFile(textureFilepath.data(),
		                    &m_TextureView,
		                    &m_TextureWidth,
		                    &m_TextureHeight);

		D3D11_SAMPLER_DESC frameTextureSampler = {};
		frameTextureSampler.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		frameTextureSampler.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
		frameTextureSampler.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
		frameTextureSampler.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

		Renderer::GetDevice().CreateSamplerState(&frameTextureSampler,
		                                         &m_TextureSampler);
	}

	RenderComponent::~RenderComponent() = default;

	void RenderComponent::Draw(Camera& camera) const
	{
		RenderObjectData* constant = new RenderObjectData();
		constant->Model            = m_EntityRef.Transform().LocalMatrix();
		constant->ViewProjection   = camera.ViewProjMatrix();
		constant->SolidColor       = AlbedoColor;

		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, constant);

		Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
		Renderer::GetDeviceContext().SetRenderData<PixelShader>(*m_PixelShader);

		Renderer::GetDeviceContext().UploadShaderData<VertexShader>(*m_ConstantBuffer);
		Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);

		if (m_HasTexture)
		{
			Renderer::GetDeviceContext().GetContext().PSSetShaderResources(0,
																		   1,
																		   &m_TextureView);
			Renderer::GetDeviceContext().GetContext().PSSetSamplers(0,
																	1,
																	&m_TextureSampler);
		}

		Renderer::GetDeviceContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
		Renderer::GetDeviceContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);

		Renderer::GetDeviceContext().SetTopology(m_RenderData->Topology);

		Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(), 0);
	}
}
