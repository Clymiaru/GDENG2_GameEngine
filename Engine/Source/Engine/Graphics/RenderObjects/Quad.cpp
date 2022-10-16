#include "pch.h"
#include "Quad.h"

#include "Engine/Core/Debug.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	struct Vertex
	{
		Vector3 Position;

		Color Color{};
	};

	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		DirectX::XMMATRIX Model;

		float Time;
	};

	Quad::Quad(const Vector3& position,
	           const Vector2& size,
	           const Color& color,
	           const std::wstring& shaderName) :
		Primitive{},
		m_Position{position},
		m_Scale{size},
		m_Color{color},
		m_TransformMatrix{DirectX::XMMatrixIdentity()},
		m_Constant{nullptr}
	{
		auto [vertices, vertexCount] = CreateVertices();
		auto [layout, layoutSize]    = CreateVertexLayout();
		auto [indices, indexCount]   = CreateIndices();

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
		// Create geometry
		// Create Vertex buffer
		// Create index buffer
		// Create Constant Buffer
		//==========

		// Clear Render Target and Depth and Stencil Views

		//===========
		// Set Shaders that will be used

		RenderSystem::SetShader<VertexShader>(*m_VertexShader);
		RenderSystem::SetShader<PixelShader>(*m_PixelShader);

		// Update and Set Constant Buffers that will be used by the shaders
		RenderSystem::GetDeviceContext().UpdateConstantBuffer(*m_ConstantBuffer, m_Constant);

		RenderSystem::SetConstantBuffer<VertexShader>(*m_ConstantBuffer);
		RenderSystem::SetConstantBuffer<PixelShader>(*m_ConstantBuffer);

		// Set Vertex and Index Buffer

		// Set Topology of the rendering

		// DrawIndexed

		RenderSystem::Draw(*m_VertexBuffer, *m_IndexBuffer);
	}

	void Quad::InitializeBuffers()
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

	void Quad::UpdateConstantBuffer(float time)
	{
		using namespace DirectX;

		m_Constant->Time = time;

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

	std::pair<Vertex*, size_t> Quad::CreateVertices()
	{
		Vertex* vertices = new Vertex[4]
		{
			{
				Vector3{-0.5f, -0.5f, 0.0f},
				Color{m_Color.Red(), m_Color.Green(), m_Color.Blue(), m_Color.Alpha()}
			},

			{
				Vector3{-0.5f, 0.5f, 0.0f},
				Color{m_Color.Red(), m_Color.Green(), m_Color.Blue(), m_Color.Alpha()}
			},

			{
				Vector3{0.5f, 0.5f, 0.0f},
				Color{m_Color.Red(), m_Color.Green(), m_Color.Blue(), m_Color.Alpha()}
			},

			{
				Vector3{0.5f, -0.5f, 0.0f},
				Color{m_Color.Red(), m_Color.Green(), m_Color.Blue(), m_Color.Alpha()},
			},
		};
		size_t vertexSize = sizeof(*vertices);

		return {vertices, vertexSize};
	}

	std::pair<D3D11_INPUT_ELEMENT_DESC*, size_t> Quad::CreateVertexLayout()
	{
		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		return {layout, layoutSize};
	}

	std::pair<Uint*, size_t> Quad::CreateIndices()
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
}
