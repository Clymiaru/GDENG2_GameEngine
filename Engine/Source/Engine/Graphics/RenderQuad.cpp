#include "pch.h"
#include "RenderQuad.h"

#include "Engine/Math/Vector2.h"
#include "Engine/Math/Vector3.h"

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	struct PostProcessVertex
	{
		Vector3Float Position;

		Vector2Float TextureCoordinates;
	};

	RenderQuad::RenderQuad() :
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr}
	{
		PostProcessVertex* vertices = new PostProcessVertex[4]
		{
			{Vector3Float{-1.0f, -1.0f, 0.0f}, Vector2Float{0.0f, 1.0f}},
			{Vector3Float{-1.0f, 1.0f, 0.0f}, Vector2Float{0.0f, 0.0f}},
			{Vector3Float{1.0f, 1.0f, 0.0f}, Vector2Float{1.0f, 0.0f}},
			{Vector3Float{1.0f, -1.0f, 0.0f}, Vector2Float{1.0f, 1.0f}},
		};

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
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

		const VertexData vertexData = VertexData(vertices, sizeof(*vertices));

		const VertexLayoutData vertexLayoutData = VertexLayoutData(layout, 2U);

		const IndexData indexData = IndexData(indices, sizeof(indices));

		m_VertexShader = ShaderLibrary::GetShaderRef<VertexShader>("BasicQuad_VertexShader");

		m_PixelShader = ShaderLibrary::GetShaderRef<PixelShader>("BasicQuad_PixelShader");

		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(vertexData.VertexList,
		                                               sizeof(PostProcessVertex),
		                                               vertexData.VertexListCount,
		                                               m_VertexShader->ByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->ByteCodeSizeData()),
		                                               vertexLayoutData.VertexLayout,
		                                               vertexLayoutData.VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(indexData.IndexList,
		                                             indexData.IndexListCount);

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

		Renderer::GetDevice().CreateSamplerState(&samplerDesc, &m_TextureSampler);
	}

	RenderQuad::~RenderQuad()
	{
		delete m_TextureSampler;
	}

	void RenderQuad::Draw(ID3D11ShaderResourceView& renderTargetFrame)
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

		Renderer::GetDeviceContext().SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(),
		                                         0);
	}
}
