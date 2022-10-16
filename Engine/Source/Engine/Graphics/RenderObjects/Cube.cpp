#include "pch.h"
#include "Cube.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/RenderSystem.h"

namespace Engine
{
	struct Vertex
	{
		Vector3 Position;

		Color Color;
	};

	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		DirectX::XMMATRIX Model;

		float Time;
	};

	Cube::Cube(const Vector3& position,
	           const Vector3& size,
	           const std::wstring& shaderName) :
		Primitive{},
		m_Position{position},
		m_Scale{size},
		m_TransformMatrix{DirectX::XMMatrixIdentity()},
		m_Constant{nullptr}
	{
		auto [vertices, vertexCount] = Cube::CreateVertices();
		auto [layout, layoutSize]    = Cube::CreateVertexLayout();
		auto [indices, indexCount]   = Cube::CreateIndices();

		InitializeImpl({vertices, vertexCount},
					   {layout, layoutSize},
					   {indices, indexCount},
					   shaderName);

		Cube::InitializeBuffers();
	}

	Cube::~Cube()
	{
		TerminateImpl();
		m_ConstantBuffer->Release();
		delete m_Constant;
	}

	void Cube::Update(float deltaTime)
	{
		using namespace DirectX;

		m_Constant->Time = deltaTime;

		m_TransformMatrix = XMMatrixIdentity();
		m_TransformMatrix *= XMMatrixScaling(m_Scale.X(),
											 m_Scale.Y(),
											 1.0f);
		m_TransformMatrix *= XMMatrixTranslation(m_Position.X(),
												 m_Position.Y(),
												 m_Position.Z());
		m_Constant->Model = XMMatrixTranspose(m_TransformMatrix);

		// To be transferred to camera later
		m_Constant->View = XMMatrixIdentity();
		m_Constant->View = XMMatrixTranspose(m_Constant->View);

		m_Constant->Projection = XMMatrixIdentity();
		m_Constant->Projection *= XMMatrixOrthographicLH(1280.0f, 720.0f, -4.0f, 4.0f);
		m_Constant->Projection = XMMatrixTranspose(m_Constant->Projection);
	}

	void Cube::Render() const
	{
		RenderSystem::SetShader<VertexShader>(*m_VertexShader);
		RenderSystem::SetShader<PixelShader>(*m_PixelShader);

		RenderSystem::GetDeviceContext().UpdateConstantBuffer(*m_ConstantBuffer, m_Constant);

		RenderSystem::SetConstantBuffer<VertexShader>(*m_ConstantBuffer);
		RenderSystem::SetConstantBuffer<PixelShader>(*m_ConstantBuffer);

		RenderSystem::Draw(*m_VertexBuffer, *m_IndexBuffer);
	}

	void Cube::InitializeBuffers()
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
											  sizeof(Vertex),
											  m_VertexData->VertexListCount,
											  m_VertexShader->GetByteCodeData(),
											  static_cast<Uint>(m_VertexShader->GetByteCodeSizeData()),
											  m_VertexLayoutData->VertexLayout,
											  m_VertexLayoutData->VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
											m_IndexData->IndexListCount);

		m_Constant       = new Constant({});
		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(m_Constant, sizeof(Constant));
	}

	std::pair<Vertex*, size_t> Cube::CreateVertices()
	{
		Vertex* vertices = new Vertex[8]
		{
			{
				Vector3{-0.5f, -0.5f, -0.5f},
				Color{0.8f,0,0}
			},

			{
				Vector3{-0.5f, 0.5f, -0.5f},
				Color{0.8f,0.8f,0}
			},

			{
				Vector3{0.5f, 0.5f, -0.5f},
				Color{0.8f,0.8f,0}
			},

			{
				Vector3{0.5f, -0.5f, -0.5f},
				{0.8f,0,0},
			},

			{
				Vector3{0.5f, -0.5f, 0.5f},
				Color{0,0.8f,0}
			},

			{
				Vector3{0.5f, 0.5f, 0.5f},
				Color{0,0.8f,0.8f}
			},

			{
				Vector3{-0.5f, 0.5f, 0.5f},
				Color{0,0.8f,0.8f}
			},

			{
				Vector3{-0.5f, -0.5f, 0.5f},
				Color{0,0.8f,0},
			}
		};

		size_t vertexSize = sizeof(*vertices);

		return {vertices, vertexSize};
	}

	std::pair<D3D11_INPUT_ELEMENT_DESC*, size_t> Cube::CreateVertexLayout()
	{
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		return {layout, layoutSize};
	}

	std::pair<Uint*, size_t> Cube::CreateIndices()
	{
		Uint* indices = new Uint[36]
		{
			//FRONT SIDE
			0,
			1,
			2,
			2,
			3,
			0,

			//BACK SIDE
			4,
			5,
			6,
			6,
			7,
			4,

			//TOP SIDE
			1,
			6,
			5,
			5,
			2,
			1,

			//BOTTOM SIDE
			7,
			0,
			3,
			3,
			4,
			7,

			//RIGHT SIDE
			3,
			2,
			5,
			5,
			4,
			3,

			//LEFT SIDE	
			7,
			6,
			1,
			1,
			0,
			7
		};
		size_t indexSize = sizeof(indices);
		return {indices, indexSize};
	}
}
