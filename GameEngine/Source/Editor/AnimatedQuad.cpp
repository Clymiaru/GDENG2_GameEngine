#include "pch.h"
#include "AnimatedQuad.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	struct Vertex
	{
		Engine::Vector3Float Position;

		Engine::Vector3Float Position1;

		Engine::Color32 Color{};

		Engine::Color32 Color1{};
	};

	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		DirectX::XMMATRIX Model;

		float Ratio;
	};
}

Editor::AnimatedQuad::AnimatedQuad(const Engine::Vector3Float& v0_start,
                                   const Engine::Vector3Float& v0_end,
                                   const Engine::Vector3Float& v1_start,
                                   const Engine::Vector3Float& v1_end,
                                   const Engine::Vector3Float& v2_start,
                                   const Engine::Vector3Float& v2_end,
                                   const Engine::Vector3Float& v3_start,
                                   const Engine::Vector3Float& v3_end,
                                   const Engine::Color32& v0_color_start,
                                   const Engine::Color32& v0_color_end,
                                   const Engine::Color32& v1_color_start,
                                   const Engine::Color32& v1_color_end,
                                   const Engine::Color32& v2_color_start,
                                   const Engine::Color32& v2_color_end,
                                   const Engine::Color32& v3_color_start,
                                   const Engine::Color32& v3_color_end) :
	RenderObject{},
	m_TransformMatrix{DirectX::XMMatrixIdentity()},
	m_Constant{nullptr},
	m_V0Start{v0_start},
	m_V0End{v0_end},
	m_V1Start{v1_start},
	m_V1End{v1_end},
	m_V2Start{v2_start},
	m_V2End{v2_end},
	m_V3Start{v3_start},
	m_V3End{v3_end},
	m_V0ColorStart{v0_color_start},
	m_V0ColorEnd{v0_color_end},
	m_V1ColorStart{v1_color_start},
	m_V1ColorEnd{v1_color_end},
	m_V2ColorStart{v2_color_start},
	m_V2ColorEnd{v2_color_end},
	m_V3ColorStart{v3_color_start},
	m_V3ColorEnd{v3_color_end}

{
	m_VertexData       = InitializeVertexData();
	m_VertexLayoutData = InitializeVertexLayout();
	m_IndexData        = InitializeIndexData();
	InitializeShaderData();
	SetBuffers();
}

Editor::AnimatedQuad::~AnimatedQuad()
{
	m_ConstantBuffer->Release();
	delete m_Constant;
}

auto Editor::AnimatedQuad::Update(float ratio) -> void
{
	using namespace DirectX;

	m_Constant->Ratio = ratio;

	m_TransformMatrix = XMMatrixIdentity();
	//m_Constant->Model = XMMatrixTranspose(m_TransformMatrix);

	m_Constant->View = XMMatrixIdentity();
	//m_Constant->View = XMMatrixTranspose(m_Constant->View);

	m_Constant->Projection = XMMatrixIdentity();
	m_Constant->Projection *= XMMatrixOrthographicLH(
		1280.0f,
		720.0f,
		-4.0f, 4.0f);
	m_Constant->Projection = XMMatrixTranspose(m_Constant->Projection);
}

auto Editor::AnimatedQuad::Render() const -> void
{
	m_ConstantBuffer->Update(Engine::RenderSystem::GetInstance().GetDeviceContext(), m_Constant);
	Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
		*m_VertexShader, *m_ConstantBuffer);
	Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
		*m_PixelShader, *m_ConstantBuffer);
	Engine::RenderSystem::GetInstance().GetDeviceContext().SetVertexShader(L"QuadAnimShader.hlsl");
	Engine::RenderSystem::GetInstance().GetDeviceContext().SetPixelShader(L"QuadAnimShader.hlsl");
}

auto Editor::AnimatedQuad::SetBuffers() -> void
{
	m_VertexBuffer = Engine::CreateUniquePtr<Engine::VertexBuffer>();
	bool result    = m_VertexBuffer->Load(m_VertexData.VertexList,
	                                      sizeof(Engine::Vertex),
	                                      m_VertexData.VertexListCount,
	                                      m_VertexShader->GetByteCodeData(),
	                                      static_cast<Engine::Uint>(m_VertexShader->GetByteCodeSizeData()),
	                                      m_VertexLayoutData.VertexLayout,
	                                      m_VertexLayoutData.VertexLayoutCount);

	m_IndexBuffer = Engine::CreateUniquePtr<Engine::IndexBuffer>();
	result        = m_IndexBuffer->Load(m_IndexData.IndexList,
	                                    m_IndexData.IndexListCount);

	m_ConstantBuffer = Engine::CreateUniquePtr<Engine::ConstantBuffer>();
	m_Constant       = new Engine::Constant({});
	result           = m_ConstantBuffer->Load(m_Constant, sizeof(Engine::Constant));
}

auto Editor::AnimatedQuad::InitializeVertexData() -> VertexData
{
	auto* vertices = new Engine::Vertex[4]
	{
		{
			m_V0Start,
			m_V0End,
			m_V0ColorStart,
			m_V0ColorEnd
		},

		{
			m_V1Start,
			m_V1End,
			m_V1ColorStart,
			m_V1ColorEnd
		},

		{
			m_V2Start,
			m_V2End,
			m_V2ColorStart,
			m_V2ColorEnd
		},

		{
			m_V3Start,
			m_V3End,
			m_V3ColorStart,
			m_V3ColorEnd
		},
	};
	constexpr size_t vertexSize = sizeof vertices;
	return {std::move(vertices), vertexSize};
}

auto Editor::AnimatedQuad::InitializeVertexLayout() -> VertexLayoutData
{
	auto* layout = new D3D11_INPUT_ELEMENT_DESC[4]
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"POSITION", 1, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 1, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	constexpr size_t layoutSize = 4U; //INFO: Is there a way to automate this (to automate layoutSize calculation).
	return {std::move(layout), layoutSize};
}

auto Editor::AnimatedQuad::InitializeIndexData() -> IndexData
{
	auto* indices = new Engine::Uint[6]
	{
		1,
		2,
		3,
		3,
		0,
		1
	};
	constexpr size_t indexSize = sizeof indices;
	return {std::move(indices), indexSize};
}

auto Editor::AnimatedQuad::InitializeShaderData() -> void
{
	m_VertexShader = Engine::ShaderLibrary::GetInstance().GetVertexShaderRef(L"QuadAnimShader.hlsl");
	m_PixelShader  = Engine::ShaderLibrary::GetInstance().GetPixelShaderRef(L"QuadAnimShader.hlsl");
}
