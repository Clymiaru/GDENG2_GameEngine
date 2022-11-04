#include "pch.h"
#include "PostProcessQuad.h"

#include "Renderer.h"
#include "ShaderLibrary.h"

#include "Engine/Input/Input.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Vector3.h"

__declspec(align(16))
struct Constant
{
	Engine::Vector2Float ScreenSize;
	Engine::Vector2Float Direction;
};

namespace Engine
{
	struct PostProcessVertex
	{
		Vector3Float Position;

		Vector2Float TextureCoordinates;

		Color Color{};
	};

	PostProcessQuad::PostProcessQuad() :
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr}
	{
		PostProcessVertex* vertices = new PostProcessVertex[4]
		{
			{
				Vector3Float{-1.0f, -1.0f, 0.0f},
				Vector2Float{0.0f, 1.0f},
				Color{1.0f, 1.0f, 1.0f, 1.0f}
			},

			{
				Vector3Float{-1.0f, 1.0f, 0.0f},
				Vector2Float{0.0f, 0.0f},
				Color{1.0f, 1.0f, 1.0f, 1.0f}
			},

			{
				Vector3Float{1.0f, 1.0f, 0.0f},
				Vector2Float{1.0f, 0.0f},
				Color{1.0f, 1.0f, 1.0f, 1.0f}
			},

			{
				Vector3Float{1.0f, -1.0f, 0.0f},
				Vector2Float{1.0f, 1.0f},
				Color{1.0f, 1.0f, 1.0f, 1.0f}
			},
		};
		size_t vertexSize = sizeof(*vertices);

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[3]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12 + 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
		};
		size_t layoutSize = 3U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		auto* indices = new uint32_t[6]
		{
			2,
			3,
			0,
			0,
			1,
			2
		};
		size_t indexSize = sizeof(indices);

		m_VertexData       = new VertexData(vertices, vertexSize);
		m_VertexLayoutData = new VertexLayoutData(layout, layoutSize);
		m_IndexData        = new IndexData(indices, indexSize);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>("PostProcessSimpleChromaticAberration");
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>("PostProcessSimpleChromaticAberration");

		Constant* constant = new Constant{};
		
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
		                                               sizeof(PostProcessVertex),
		                                               m_VertexData->VertexListCount,
		                                               m_VertexShader->ByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->ByteCodeSizeData()),
		                                               m_VertexLayoutData->VertexLayout,
		                                               m_VertexLayoutData->VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
		                                             m_IndexData->IndexListCount);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constant, sizeof(Constant));

		D3D11_SAMPLER_DESC samplerDesc = {};
		samplerDesc.Filter             = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.AddressU           = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressV           = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.AddressW           = D3D11_TEXTURE_ADDRESS_CLAMP;

		Renderer::GetDevice().CreateSamplerState(&samplerDesc, &m_TextureSampler);
	}

	PostProcessQuad::~PostProcessQuad()
	{
		m_VertexBuffer.release();
		m_IndexBuffer.release();
		m_ConstantBuffer.release();
	}

	void PostProcessQuad::UpdateFrameRef(ID3D11ShaderResourceView* frame)
	{
		m_FrameReference = frame;
	}

	void PostProcessQuad::Draw() const
	{
		Constant* constant = new Constant();

		constant->ScreenSize          = Vector2Float(1280, 1080);

		auto mousePos = Input::Mouse().MousePosition;
		auto mag = mousePos.Length();
		constant->Direction = Vector2Float((float)mousePos.x / mag, (float)mousePos.y / mag);
		//m_ConstantBuffer->Update();

		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, constant);
		
		Renderer::GetDeviceContext().SetRenderData<VertexShader>(*m_VertexShader);
		Renderer::GetDeviceContext().SetRenderData<PixelShader>(*m_PixelShader);

		Renderer::GetDeviceContext().GetContext().PSSetShaderResources(0, 1, &m_FrameReference);
		Renderer::GetDeviceContext().GetContext().PSSetSamplers(0, 1, &m_TextureSampler);

		Renderer::GetDeviceContext().UploadShaderData<VertexShader>(*m_ConstantBuffer);
		Renderer::GetDeviceContext().UploadShaderData<PixelShader>(*m_ConstantBuffer);

		Renderer::GetDeviceContext().SetRenderData<VertexBuffer>(*m_VertexBuffer);
		Renderer::GetDeviceContext().SetRenderData<IndexBuffer>(*m_IndexBuffer);

		Renderer::GetDeviceContext().SetTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		Renderer::GetDeviceContext().DrawIndexed(m_IndexBuffer->ElementCount(),
		                                         0);
	}
}
