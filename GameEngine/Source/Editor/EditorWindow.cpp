#include "pch.h"
#include "EditorWindow.h"

#include "Windows.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/Shader.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Graphics/VertexShader.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

#include "Engine/Graphics/Primitives/Quad.h"

namespace Editor
{
	__declspec(align(16))
	struct Constant
	{
		DirectX::XMMATRIX World;

		DirectX::XMMATRIX View;

		DirectX::XMMATRIX Projection;

		float Time;
	};

	EditorWindow::EditorWindow(const std::wstring& windowName,
	                           const Engine::Vector2Int windowSize) :
		Window()
	{
	}

	EditorWindow::~EditorWindow() = default;

	auto EditorWindow::OnCreate() -> void
	{
		Window::OnCreate();
		std::cout << "Editor Window Create\n";
	}

	auto EditorWindow::OnStart() -> void
	{
		Window::OnStart();
		std::cout << "Editor Window Start\n";

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector2Float{-300.0f, 100.0f},
		                                                        Engine::Vector2Float{400.f, 400.0f},
		                                                        Engine::Color32{0.68f, 0, 0.83f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector2Float{200.0f, 125.0f},
		                                                        Engine::Vector2Float{225.0f, 425.0f},
		                                                        Engine::Color32{0.27f, 0.51f, 0.41f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector2Float{200.0f, -225.0f},
		                                                        Engine::Vector2Float{500.0f, 225.0f},
		                                                        Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f}));

		void* shaderByteCode      = nullptr;
		size_t shaderByteCodeSize = 0;

		Engine::ShaderLibrary::GetInstance().RegisterVertexShader(L"SinTimeAnimShader.hlsl",
		                                                          "vsmain");

		Engine::ShaderLibrary::GetInstance().RegisterPixelShader(L"SinTimeAnimShader.hlsl",
		                                                         "psmain");

		auto& vs = Engine::ShaderLibrary::GetInstance().GetVertexShader(L"SinTimeAnimShader.hlsl");
		auto& ps = Engine::ShaderLibrary::GetInstance().GetPixelShader(L"SinTimeAnimShader.hlsl");

		for (auto& quad : m_Quads)
		{
			Engine::RenderSystem::GetInstance().RegisterObject(quad->GetListOfVertices(),
			                                                   quad->GetVertexSize(),
			                                                   quad->GetListOfVerticesSize(),
			                                                   vs.GetByteCodeData(),
			                                                   vs.GetByteCodeSizeData(),
			                                                   quad->GetIndexLayoutAndSize().Data,
			                                                   quad->GetIndexLayoutAndSize().Size);
		}

		Constant constant = {};
		constant.Time     = 0;
		m_ConstantBuffer  = Engine::CreateUniquePtr<Engine::ConstantBuffer>();
		m_ConstantBuffer->Load(&constant, sizeof(Constant));
	}

	auto EditorWindow::OnUpdate() -> void
	{
		Window::OnUpdate();
		Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});

		const RECT rc = GetClientWindowRect();
		Engine::RenderSystem::SetViewportSize({
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		});

		unsigned long newTime = 0;
		if (m_OldTime)
			newTime = GetTickCount() - m_OldTime;
		m_DeltaTime = static_cast<float>(newTime) / 1000.0f;
		m_OldTime   = GetTickCount();

		m_Time += m_DeltaTime;
		Constant constant = {};
		constant.Time     = m_Time;

		constant.World      = DirectX::XMMatrixIdentity();
		constant.World      = DirectX::XMMatrixTranslation(0.0f, 0.0f, 0.0f);
		constant.View       = DirectX::XMMatrixIdentity();
		constant.Projection = DirectX::XMMatrixIdentity();
		constant.Projection = DirectX::XMMatrixOrthographicLH(
			1280.0f,
			720.0f,
			-4.0f, 4.0f);

		auto device = Engine::RenderSystem::GetInstance().GetDevice();
		m_ConstantBuffer->Update(Engine::RenderSystem::GetInstance().GetDeviceContext(), &constant);

		Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			m_VertexShader, m_ConstantBuffer);
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			m_PixelShader, m_ConstantBuffer);

		Engine::RenderSystem::GetInstance().GetDeviceContext().SetVertexShader(L"SinTimeAnimShader.hlsl");
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetPixelShader(L"SinTimeAnimShader.hlsl");

		Engine::RenderSystem::Draw();
	}

	auto EditorWindow::OnTerminate() -> void
	{
		Window::OnTerminate();
		m_ConstantBuffer->Release();
	}
}
