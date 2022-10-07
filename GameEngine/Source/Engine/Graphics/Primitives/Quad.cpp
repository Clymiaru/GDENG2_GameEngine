#include "pch.h"
#include "Quad.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		DirectX::XMMATRIX Model;

		float Time;
	};

	Quad::Quad(const Vector2Float& position,
	           const Vector2Float& size,
	           const Color32& color):
		ARenderObject{},
		m_Position{position},
		m_Size{size},
		m_Color{color}
	{
		m_VertexData = InitializeVertexData();
		m_VertexLayoutData = InitializeVertexLayout();
		m_IndexData = InitializeIndexData();
		InitializeShaderData();
		SetBuffers();
	}

	Quad::~Quad()
	{
		m_ConstantBuffer->Release();
		delete constant;
	}

	auto Quad::Update(float deltaTime) -> void
	{
		using namespace DirectX;
		constant->Time = deltaTime;

		constant->Model = XMMatrixIdentity();
		constant->Model *= XMMatrixScaling(m_Size.X,
		                                   m_Size.Y,
		                                   1.0f);
		constant->Model *= XMMatrixTranslation(m_Position.X,
		                                       m_Position.Y,
		                                       0.0f);
		constant->Model = XMMatrixTranspose(constant->Model);

		constant->View       = XMMatrixIdentity();
		constant->View       = XMMatrixTranspose(constant->View);
		constant->Projection = XMMatrixIdentity();

		constant->Projection *= XMMatrixOrthographicLH(
			1280.0f,
			720.0f,
			-4.0f, 4.0f);

		constant->Projection = XMMatrixTranspose(constant->Projection);
		m_ConstantBuffer->Update(RenderSystem::GetInstance().GetDeviceContext(), constant);

		RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			*m_VertexShader, m_ConstantBuffer);
		RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			*m_PixelShader, m_ConstantBuffer);

		RenderSystem::GetInstance().GetDeviceContext().SetVertexShader(L"SinTimeAnimShader.hlsl");
		RenderSystem::GetInstance().GetDeviceContext().SetPixelShader(L"SinTimeAnimShader.hlsl");
	}

	auto Quad::SetBuffers() -> void
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>();
		m_VertexBuffer->Load(m_VertexData.VertexList,
		                     sizeof(Vertex),
		                     m_VertexData.VertexListCount,
		                     m_VertexShader->GetByteCodeData(),
		                     m_VertexShader->GetByteCodeSizeData(),
		                     m_VertexLayoutData.VertexLayout,
		                     m_VertexLayoutData.VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>();
		m_IndexBuffer->Load(m_IndexData.IndexList,
		                    m_IndexData.IndexListCount);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>();
		constant         = new Constant({});
		m_ConstantBuffer->Load(constant, sizeof(Constant));
	}

	auto Quad::InitializeVertexData() -> VertexData
	{
		auto* vertices = new Vertex[4]
		{
			{
				Vector3Float{-0.5f, -0.5f, 0.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{-0.5f, 0.5f, 0.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{0.5f, 0.5f, 0.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha}
			},

			{
				Vector3Float{0.5f, -0.5f, 0.0f},
				Color32{m_Color.Red, m_Color.Green, m_Color.Blue, m_Color.Alpha},
			},
		};
		constexpr size_t vertexSize = sizeof vertices;
		return {std::move(vertices), vertexSize};
	}

	auto Quad::InitializeVertexLayout() -> VertexLayoutData
	{
		auto* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		constexpr size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).
		return {std::move(layout), layoutSize};
	}

	auto Quad::InitializeIndexData() -> IndexData
	{
		auto* indices = new Uint[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};
		constexpr size_t indexSize = sizeof indices;
		return {std::move(indices), indexSize};
	}

	auto Quad::InitializeShaderData() -> void
	{
		m_VertexShader = &ShaderLibrary::GetInstance().GetVertexShader(L"SinTimeAnimShader.hlsl");
		m_PixelShader  = &ShaderLibrary::GetInstance().GetPixelShader(L"SinTimeAnimShader.hlsl");
	}
}
