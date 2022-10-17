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
		AEntity{"Cube"},
		m_Constant{nullptr},
		m_Primitive{new Primitive()}
	{
		Position(position);
		Scale(size);
		
		Vertex* vertices = new Vertex[8]
		{
			{
				Vector3{-0.5f,-0.5f,-0.5f},
				Color{0.8f, 0, 0}
			},

			{
				Vector3{-0.5f,0.5f,-0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3{0.5f,0.5f,-0.5f},
				Color{0.8f, 0.8f, 0}
			},

			{
				Vector3{0.5f,-0.5f,-0.5f},
				{0.8f, 0, 0},
			},

			{
				Vector3{0.5f,-0.5f,0.5f},
				Color{0, 0.8f, 0}
			},

			{
				Vector3{0.5f,0.5f,0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3{-0.5f,0.5f,0.5f},
				Color{0, 0.8f, 0.8f}
			},

			{
				Vector3{-0.5f,-0.5f,0.5f},
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

		Uint* indices = new Uint[36]
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

		m_Primitive->Initialize({vertices, vertexSize},
								{layout, layoutSize},
								{indices, 36},
								shaderName);

		m_Constant = new Constant{};

		m_Primitive->InitializeBuffers(sizeof(Vertex),
									   m_Constant,
									   sizeof(Constant));
	}

	Cube::~Cube()
	{
		m_Primitive->Terminate();
		delete m_Constant;
	}

	void Cube::Update(float deltaTime)
	{
		using namespace DirectX;

		m_Constant->Time = deltaTime;
		
		m_Constant->Model = Transform();

		// To be transferred to camera later
		m_Constant->View = XMMatrixIdentity();
		m_Constant->View = XMMatrixTranspose(m_Constant->View);

		m_Constant->Projection = XMMatrixIdentity();
		m_Constant->Projection *= XMMatrixOrthographicLH(1280.0f, 720.0f, -1000.0f, 1000.0f);
		m_Constant->Projection = XMMatrixTranspose(m_Constant->Projection);
	}

	void Cube::Draw()
	{
		m_Primitive->Draw(m_Constant);
	}
}
