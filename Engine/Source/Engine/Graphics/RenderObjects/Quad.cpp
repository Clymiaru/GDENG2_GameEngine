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

	constexpr std::tuple<Vertex*, size_t> GetQuadVertices(Color32 color)
	{
		Vertex* vertices = new Vertex[4]
		{
			{
				Vector3Float{-0.5f, -0.5f, 0.0f},
				Color32{color.Red, color.Green, color.Blue, color.Alpha}
			},

			{
				Vector3Float{-0.5f, 0.5f, 0.0f},
				Color32{color.Red, color.Green, color.Blue, color.Alpha}
			},

			{
				Vector3Float{0.5f, 0.5f, 0.0f},
				Color32{color.Red, color.Green, color.Blue, color.Alpha}
			},

			{
				Vector3Float{0.5f, -0.5f, 0.0f},
				Color32{color.Red, color.Green, color.Blue, color.Alpha},
			},
		};
		size_t vertexSize = sizeof vertices;

		return {vertices, vertexSize};
	}

	constexpr std::tuple<D3D11_INPUT_ELEMENT_DESC*, size_t> GetQuadVertexLayout()
	{
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		return {layout, layoutSize};
	}

	constexpr std::tuple<Uint*, size_t> GetQuadIndices()
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
		size_t indexSize = sizeof indices;

		return {indices, indexSize};
	}

	Quad::Quad(const Vector3Float& position,
	           const Vector2Float& size,
	           const Color32& color,
	           const std::wstring& shaderName) :
		RenderObject{},
		m_Position{position},
		m_Size{size},
		m_Color{color},
		m_ConstantBuffer{nullptr},
		m_TransformMatrix{DirectX::XMMatrixIdentity()},
		m_Constant{nullptr}
	{
		auto [vertices, vertexCount] = GetQuadVertices(m_Color);
		auto [layout, layoutSize]    = GetQuadVertexLayout();
		auto [indices, indexCount]   = GetQuadIndices();

		InitializeImpl({vertices, vertexCount},
		               {layout, layoutSize},
		               {indices, indexCount},
		               shaderName);

		InitializeBuffers();
	}

	Quad::~Quad()
	{
		TerminateImpl();
		m_ConstantBuffer->Release();
		delete m_Constant;
	}

	void Quad::Update(const float deltaTime)
	{
		UpdateConstantBuffer(deltaTime);
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

	void Quad::InitializeBuffers()
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>();
		bool result    = m_VertexBuffer->Load(m_VertexData->VertexList,
		                                      sizeof(Vertex),
		                                      m_VertexData->VertexListCount,
		                                      m_VertexShader->GetByteCodeData(),
		                                      static_cast<Uint>(m_VertexShader->GetByteCodeSizeData()),
		                                      m_VertexLayoutData->VertexLayout,
		                                      m_VertexLayoutData->VertexLayoutCount);
		ENGINE_ASSERT(result, "Vertex Buffer can't be loaded!")

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>();
		result        = m_IndexBuffer->Load(m_IndexData->IndexList,
		                                    m_IndexData->IndexListCount);
		ENGINE_ASSERT(result, "Index Buffer can't be loaded!")

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>();
		m_Constant       = new Constant({});
		result           = m_ConstantBuffer->Load(m_Constant, sizeof(Constant));
		ENGINE_ASSERT(result, "Constant Buffer can't be loaded!")
	}

	void Quad::UpdateConstantBuffer(float time)
	{
		using namespace DirectX;

		m_Constant->Time = time;

		m_TransformMatrix = XMMatrixIdentity();
		m_TransformMatrix *= XMMatrixScaling(m_Size.X,
											 m_Size.Y,
											 1.0f);
		m_TransformMatrix *= XMMatrixTranslation(m_Position.X,
												 m_Position.Y,
												 m_Position.Z);
		m_Constant->Model = XMMatrixTranspose(m_TransformMatrix);

		// To be transferred to camera later
		m_Constant->View = XMMatrixIdentity();
		m_Constant->View = XMMatrixTranspose(m_Constant->View);

		m_Constant->Projection = XMMatrixIdentity();
		m_Constant->Projection *= XMMatrixOrthographicLH(1280.0f, 720.0f, -4.0f, 4.0f);
		m_Constant->Projection = XMMatrixTranspose(m_Constant->Projection);
	}
}
