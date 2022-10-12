#include "pch.h"
#include "Quad.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Utils/Debug.h"

namespace Engine
{
	struct Vertex
	{
		Vector3Float Position;

		Color32 Color{};
	};

	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		DirectX::XMMATRIX Model;

		float Time;
	};

	Quad::Quad(const Vector3Float& position,
	           const Vector2Float& size,
	           const Color32& color):
		RenderObject{},
		m_Position{position},
		m_Size{size},
		m_Color{color},
		m_TransformMatrix{DirectX::XMMatrixIdentity()},
		m_Constant{nullptr}
	{
		m_VertexData       = InitializeVertexData();
		m_VertexLayoutData = InitializeVertexLayout();
		m_IndexData        = InitializeIndexData();
		InitializeShaderData();
		SetBuffers();
	}

	Quad::Quad(const Vector3Float& position,
	           const Vector2Float& size,
	           const Color32& color,
	           const std::wstring& shaderName) :
		RenderObject{},
		m_Position{position},
		m_Size{size},
		m_Color{color},
		m_TransformMatrix{DirectX::XMMatrixIdentity()},
		m_Constant{nullptr}
	{
		m_VertexData       = InitializeVertexData();
		m_VertexLayoutData = InitializeVertexLayout();
		m_IndexData        = InitializeIndexData();
		m_VertexShader     = ShaderLibrary::GetInstance().GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetInstance().GetShaderRef<PixelShader>(shaderName);
		SetBuffers();
	}

	Quad::~Quad()
	{
		m_ConstantBuffer->Release();
		delete m_Constant;
	}

	void Quad::Update(const float deltaTime)
	{
		using namespace DirectX;

		m_Constant->Time = deltaTime;

		m_TransformMatrix = XMMatrixIdentity();
		m_TransformMatrix *= XMMatrixScaling(m_Size.X,
		                                     m_Size.Y,
		                                     1.0f);
		m_TransformMatrix *= XMMatrixTranslation(m_Position.X,
		                                         m_Position.Y,
		                                         m_Position.Z);
		m_Constant->Model = XMMatrixTranspose(m_TransformMatrix);

		m_Constant->View = XMMatrixIdentity();
		m_Constant->View = XMMatrixTranspose(m_Constant->View);

		m_Constant->Projection = XMMatrixIdentity();
		m_Constant->Projection *= XMMatrixOrthographicLH(
			1280.0f,
			720.0f,
			-4.0f, 4.0f);
		m_Constant->Projection = XMMatrixTranspose(m_Constant->Projection);
	}

	void Quad::Render() const
	{
		m_ConstantBuffer->Update(RenderSystem::GetDeviceContext(), m_Constant);
		RenderSystem::GetDeviceContext().SetConstantBuffer<VertexShader>(*m_ConstantBuffer);
		RenderSystem::GetDeviceContext().SetConstantBuffer<PixelShader>(*m_ConstantBuffer);
		RenderSystem::GetDeviceContext().SetShader<VertexShader>(*m_VertexShader);
		RenderSystem::GetDeviceContext().SetShader<PixelShader>(*m_PixelShader);
		RenderSystem::Draw(*m_VertexBuffer, *m_IndexBuffer);
	}

	void Quad::SetBuffers()
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>();
		bool result    = m_VertexBuffer->Load(m_VertexData.VertexList,
		                                      sizeof(Vertex),
		                                      m_VertexData.VertexListCount,
		                                      m_VertexShader->GetByteCodeData(),
		                                      static_cast<Uint>(m_VertexShader->GetByteCodeSizeData()),
		                                      m_VertexLayoutData.VertexLayout,
		                                      m_VertexLayoutData.VertexLayoutCount);
		ENGINE_ASSERT(result, "Vertex Buffer can't be loaded!")

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>();
		result        = m_IndexBuffer->Load(m_IndexData.IndexList,
		                                    m_IndexData.IndexListCount);
		ENGINE_ASSERT(result, "Index Buffer can't be loaded!")

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>();
		m_Constant       = new Constant({});
		result           = m_ConstantBuffer->Load(m_Constant, sizeof(Constant));
		ENGINE_ASSERT(result, "Constant Buffer can't be loaded!")
	}

	RenderObject::VertexData Quad::InitializeVertexData()
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

	RenderObject::VertexLayoutData Quad::InitializeVertexLayout()
	{
		auto* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		constexpr size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).
		return {std::move(layout), layoutSize};
	}

	RenderObject::IndexData Quad::InitializeIndexData()
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

	void Quad::InitializeShaderData()
	{
		m_VertexShader = ShaderLibrary::GetInstance().GetShaderRef<VertexShader>(L"SinTimeAnimShader");
		m_PixelShader  = ShaderLibrary::GetInstance().GetShaderRef<PixelShader>(L"SinTimeAnimShader");
	}
}
