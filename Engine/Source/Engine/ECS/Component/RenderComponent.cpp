#include "pch.h"
#include "RenderComponent.h"

#include "TransformComponent.h"

#include "Engine/ECS/Entity/Entity.h"
#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Math/Color.h"
#include "Engine/Math/Vector3.h"

struct Vertex
{
	Engine::Vector3Float Position;

	Engine::Color Color;
};

__declspec(align(16))
struct Constant
{
	DirectX::XMMATRIX View;

	DirectX::XMMATRIX Projection;

	DirectX::XMMATRIX Model;

	float Time;
};

namespace Engine
{
	RenderComponent::RenderComponent(Entity* owner) :
		AComponent{owner},
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr},
		m_Constant{nullptr}
	{
	}

	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::Initialize()
	{
		Vertex* vertices = new Vertex[8]
		{
			{
				Vector3Float{-0.5f,-0.5f,-0.5f},
				Color{0.8f, 0, 0}
			},

			{
				Vector3Float{-0.5f,0.5f,-0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3Float{0.5f,0.5f,-0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3Float{0.5f,-0.5f,-0.5f},
				Color{0.8f, 0, 0},
			},

			{
				Vector3Float{0.5f,-0.5f,0.5f},
				Color{0, 0.8f, 0}
			},

			{
				Vector3Float{0.5f,0.5f,0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3Float{-0.5f,0.5f,0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3Float{-0.5f,-0.5f,0.5f},
				Color{0, 0.8f, 0},
			}
		};

		size_t vertexSize = sizeof(*vertices);

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		uint32_t* indices = new uint32_t[36]
		{
			//FRONT SIDE
			0,1,2,  //FIRST TRIANGLE
			2,3,0,  //SECOND TRIANGLE
			//BACK SIDE
			4,5,6,
			6,7,4,
			//TOP SIDE
			1,6,5,
			5,2,1,
			//BOTTOM SIDE
			7,0,3,
			3,4,7,
			//RIGHT SIDE
			3,2,5,
			5,4,3,
			//LEFT SIDE
			7,6,1,
			1,0,7
		};
		//size_t indexSize = ARRAYSIZE(indices);

		m_VertexData       = new VertexData{vertices, vertexSize};
		m_VertexLayoutData = new VertexLayoutData{layout, layoutSize};
		m_IndexData        = new IndexData{indices, 36};
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(L"DefaultShader");
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(L"DefaultShader");
		
		m_Constant = new Constant{};

		// Do we have to create vertex, index buffers, and constant buffers here?
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
		                                               sizeof(Vertex),
		                                               m_VertexData->VertexListCount,
		                                               m_VertexShader->GetByteCodeData(),
		                                               static_cast<uint32_t>(m_VertexShader->GetByteCodeSizeData()),
		                                               m_VertexLayoutData->VertexLayout,
		                                               m_VertexLayoutData->VertexLayoutCount);
		
		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
		                                             m_IndexData->IndexListCount);
		
		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(m_Constant, sizeof(Constant));
	}

	

	void RenderComponent::Terminate()
	{
		m_VertexBuffer.release();
		m_IndexBuffer.release();
		m_ConstantBuffer.release();
	}

	void RenderComponent::Update()
	{
		m_Constant->Time = 0;
		m_Constant->Model = m_EntityRef->Transform().LocalMatrix();
		m_Constant->Projection = Matrix4();
		m_Constant->View = Matrix4();
	}

	void RenderComponent::Draw()
	{
		Update();
		
		Renderer::UpdateConstantBuffer(*m_ConstantBuffer, m_Constant);

		Renderer::Draw(*m_VertexShader, *m_PixelShader,
		                  *m_VertexBuffer, *m_IndexBuffer,
		                  *m_ConstantBuffer, m_Constant,
		                  D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	}
}
