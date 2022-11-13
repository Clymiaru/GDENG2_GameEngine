#include "pch.h"
#include "PostProcessQuad.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"

#include "Engine/Math/Math.h"

#include "PostProcessEffect.h"

namespace Engine
{
	struct PostProcessQuadVertex
	{
		Vector3Float Position;

		Vector2Float TextureCoordinates;
	};

	PostProcessQuad::PostProcessQuad():
		m_RenderData{nullptr},
		m_VertexShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_TextureSampler{nullptr}
	{
		PostProcessQuadVertex* vertices = new PostProcessQuadVertex[4]
		{
			{Vector3Float{-1.0f, -1.0f, 0.0f}, Vector2Float{0.0f, 1.0f}},
			{Vector3Float{-1.0f, 1.0f, 0.0f}, Vector2Float{0.0f, 0.0f}},
			{Vector3Float{1.0f, 1.0f, 0.0f}, Vector2Float{1.0f, 0.0f}},
			{Vector3Float{1.0f, -1.0f, 0.0f}, Vector2Float{1.0f, 1.0f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[3]
		{
			{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TexCoord", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		auto* indices = new uint32_t[6]
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
		m_RenderData->VertexSize               = sizeof(PostProcessQuadVertex);
		m_RenderData->VertexLayout             = layout;
		m_RenderData->VertexLayoutElementCount = 2U;
		m_RenderData->Indices                  = indices;
		m_RenderData->IndexCount               = sizeof(indices);
		m_RenderData->Topology                 = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

		ShaderLibrary::Register<VertexShader>("Assets/Shaders/PostProcess/VSQuad_FX.hlsl");

		m_VertexShader = ShaderLibrary::GetShaderRef<VertexShader>("VSQuad_FX");

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(*m_RenderData,
		                                               *m_VertexShader);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(*m_RenderData);

		D3D11_SAMPLER_DESC postProcessFrameTextureSampler = {};
		postProcessFrameTextureSampler.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		postProcessFrameTextureSampler.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
		postProcessFrameTextureSampler.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
		postProcessFrameTextureSampler.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

		Renderer::GetDevice().CreateSamplerState(&postProcessFrameTextureSampler,
		                                         &m_TextureSampler);
	}

	PostProcessQuad::~PostProcessQuad()
	{
		delete m_RenderData;
		delete m_TextureSampler;
	}

	void PostProcessQuad::Draw(ID3D11ShaderResourceView& renderTargetFrame,
	                           const PostProcessEffect& postProcessEffect) const
	{
		Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
		Renderer::GetDeviceContext().SetRenderData<PixelShader>(postProcessEffect.GetEffectShader());

		postProcessEffect.UploadEffectData();

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
