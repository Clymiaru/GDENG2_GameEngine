#include "pch.h"
#include "Plane.h"

namespace Engine
{
	struct Vertex
	{
		Engine::Vector3 Position;

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
}


Engine::Plane::Plane(const Vector3& position,
                     const Vector3& size,
                     const std::wstring& shaderName) :
	AEntity{"Plane"},
	m_Constant{nullptr},
	m_Primitive{new Primitive()}
{
	Position(position);
	Scale(size);

	Vertex* vertices = new Vertex[4]
	{
		{
			Vector3{-0.5f,0,-0.5f},
			Color{0.0f, 0, 0.8f}
		},

		{
			Vector3{-0.5f,0,0.5f},
			Color{0.0f, 0.8f, 0.8f}
		},

		{
			Vector3{0.5f,0.0f,0.5f},
			Color{0.0f, 0.8f, 0.8f}
		},

		{
			Vector3{0.5f,0.0f,-0.5f},
			{0.0f, 0, 0.8f},
		},
	};

	size_t vertexSize = sizeof(*vertices);

	D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, sizeof(float) * 3, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

	Uint* indices = new Uint[6]
	{
		0, 3, 2 ,2, 1, 0
	};
	//size_t indexSize = ARRAYSIZE(indices);

	m_Primitive->Initialize({vertices, vertexSize},
							{layout, layoutSize},
							{indices, 6},
							shaderName);

	m_Constant = new Constant{};

	m_Primitive->InitializeBuffers(sizeof(Vertex),
								   m_Constant,
								   sizeof(Constant));
}

Engine::Plane::~Plane()
{
	m_Primitive->Terminate();
	delete m_Constant;
}

void Engine::Plane::Update(float deltaTime)
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

void Engine::Plane::Draw()
{
	m_Primitive->Draw(m_Constant);
}
