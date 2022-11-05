#include "pch.h"
#include "RenderQuad.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	struct RenderQuadVertex
	{
		Vector3Float Position;

		Vector2Float TextureCoordinates;
	};

	RenderQuad::RenderQuad() :
		m_RenderData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_TextureSampler{nullptr}
	{
		RenderQuadVertex* vertices = new RenderQuadVertex[4]
		{
			{Vector3Float{-1.0f, -1.0f, 0.0f}, Vector2Float{0.0f, 1.0f}},
			{Vector3Float{-1.0f, 1.0f, 0.0f}, Vector2Float{0.0f, 0.0f}},
			{Vector3Float{1.0f, 1.0f, 0.0f}, Vector2Float{1.0f, 0.0f}},
			{Vector3Float{1.0f, -1.0f, 0.0f}, Vector2Float{1.0f, 1.0f}},
		};

		// TODO: Revamp VertexLayout
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		uint32_t* indices = new uint32_t[6]
		{
			2,
			3,
			0,
			0,
			1,
			2
		};

		m_RenderData                           = new RenderData{};
		m_RenderData->Vertices                 = vertices;
		m_RenderData->VertexCount              = sizeof(*vertices);
		m_RenderData->VertexSize               = sizeof(RenderQuadVertex);
		m_RenderData->VertexLayout             = layout;
		m_RenderData->VertexLayoutElementCount = 2U;
		m_RenderData->Indices                  = indices;
		m_RenderData->IndexCount               = sizeof(indices);
		m_RenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/RenderTarget/RenderQuad_VS.hlsl");
		ShaderLibrary::Register<PixelShader>("Assets/Shaders/RenderTarget/RenderQuad_PS.hlsl");

		m_VertexShader = ShaderLibrary::GetShaderRef<VertexShader>("RenderQuad_VS");

		m_PixelShader = ShaderLibrary::GetShaderRef<PixelShader>("RenderQuad_PS");

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
		                                               *m_VertexShader);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);

		D3D11_SAMPLER_DESC frameTextureSampler = {};
		frameTextureSampler.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		frameTextureSampler.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
		frameTextureSampler.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
		frameTextureSampler.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

		Renderer::GetDevice().CreateSamplerState(&frameTextureSampler,
		                                         &m_TextureSampler);
	}

	RenderQuad::~RenderQuad()
	{
		delete m_RenderData;
		delete m_TextureSampler;
	}

	void RenderQuad::Draw(ID3D11ShaderResourceView& renderTargetFrame) const
	{
		Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
		Renderer::GetDeviceContext().SetRenderData<PixelShader>(*m_PixelShader);

		std::vector<ID3D11ShaderResourceView*> frameReferenceViews = {};
		frameReferenceViews.push_back(&renderTargetFrame);

		Renderer::GetDeviceContext().GetContext().PSSetShaderResources(0,
		                                                               1,
		                                                               frameReferenceViews.data());
		Renderer::GetDeviceContext().GetContext().PSSetSamplers(0,
		                                                        1,
		                                                        &m_TextureSampler);

		Renderer::GetDeviceContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
		Renderer::GetDeviceContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);

		Renderer::GetDeviceContext().SetTopology(m_RenderData->Topology);

		Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(),
		                                         0);
	}
}
