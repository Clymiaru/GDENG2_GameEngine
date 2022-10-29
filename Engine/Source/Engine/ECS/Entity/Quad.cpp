#include "pch.h"
#include "Quad.h"

#include "Engine/Core/Debug.h"
#include "Engine/Graphics/Camera.h"

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
		AEntity{"Quad"},
		m_Color{color},
		m_Constant{nullptr},
		m_Primitive{new Primitive()}
	{
		Position(position);
		Scale(Vector3{size.X(), size.Y(), 1.0f});

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

		D3D11_INPUT_ELEMENT_DESC* layout = new D3D11_INPUT_ELEMENT_DESC[2]
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		size_t layoutSize = 2U; //INFO: Is there a way to automate this (to automate layoutSize calculation).

		auto* indices = new Uint[6]
		{
			0,
			1,
			2,
			2,
			3,
			0
		};
		size_t indexSize = sizeof(indices);

		m_Primitive->Initialize({vertices, vertexSize},
		                        {layout, layoutSize},
		                        {indices, 6},
		                        shaderName);

		m_Constant = new Constant{};

		m_Primitive->InitializeBuffers(sizeof(Vertex),
		                               m_Constant,
		                               sizeof(Constant));
	}

	Quad::~Quad()
	{
		m_Primitive->Terminate();
		delete m_Constant;
	}

	void Quad::Update(const float deltaTime)
	{
		using namespace DirectX;

		m_Constant->Time = deltaTime;
		
		m_Constant->Model = Transform();

		// To be transferred to camera later
		m_Constant->View = Camera::Instance().ViewProjMatrix();

		m_Constant->Projection = XMMatrixIdentity();
	}

	void Quad::Draw()
	{
		m_Primitive->Draw(m_Constant);
	}
}
