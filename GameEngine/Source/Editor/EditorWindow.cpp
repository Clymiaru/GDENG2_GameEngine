#include "pch.h"
#include "EditorWindow.h"

#include "Windows.h"

#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/Vertex.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

namespace Editor
{
	__declspec(align(16))
	struct Constant
	{
		float Angle;
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

	void EditorWindow::OnStart()
	{
		Window::OnStart();
		std::cout << "Editor Window Start\n";

		Vertex rainbowRectangle[] =
		{
			{
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 1.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f}
			},
		
			{
				Engine::Vector3Float{-0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f}
			},
		
			{
				Engine::Vector3Float{0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f}
			},
		
			{
				Engine::Vector3Float{0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
			},
		
			{
				Engine::Vector3Float{0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, -0.30f - 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
			},
		
			{
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{0.0f, 0.5f, 1.0f, 1.0f},
			}
		};
		
		constexpr UINT rainbowRectangleListSize = ARRAYSIZE(rainbowRectangle);
		
		void* shaderByteCode      = nullptr;
		size_t shaderByteCodeSize = 0;
		Engine::RenderSystem::GetInstance().CompileVertexShader(L"VertexShader.hlsl",
		                                                        "vsmain",
		                                                        &shaderByteCode,
		                                                        &shaderByteCodeSize);
		
		m_VertexShader = Engine::CreateUniquePtr<Engine::VertexShader>(shaderByteCode, shaderByteCodeSize);
		
		Engine::RenderSystem::GetInstance().RegisterObject(rainbowRectangle,
		                                                   sizeof(Vertex),
		                                                   rainbowRectangleListSize,
		                                                   shaderByteCode,
		                                                   shaderByteCodeSize);
		
		Engine::RenderSystem::GetInstance().ReleaseCompiledShader();
		
		Engine::RenderSystem::GetInstance().CompilePixelShader(L"PixelShader.hlsl",
		                                                       "psmain",
		                                                       &shaderByteCode,
		                                                       &shaderByteCodeSize);
		
		m_PixelShader = Engine::CreateUniquePtr<Engine::PixelShader>(shaderByteCode, shaderByteCodeSize);
		Engine::RenderSystem::GetInstance().ReleaseCompiledShader();
		
		Constant constant = {};
		constant.Angle    = 0;
		m_ConstantBuffer  = Engine::CreateUniquePtr<Engine::ConstantBuffer>();
		m_ConstantBuffer->Load(&constant, sizeof(Constant));
	}

	auto EditorWindow::OnUpdate() -> void
	{
		Window::OnUpdate();
		Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});
		
		const RECT rc = GetClientWindowRect();
	
		Engine::RenderSystem::GetInstance().SetViewportSize({
			static_cast<UINT>(rc.right - rc.left),
			static_cast<UINT>(rc.bottom - rc.top)
		});
		
		unsigned long newTime = 0;
		if (m_OldTime)
			newTime = GetTickCount() - m_OldTime;
		m_DeltaTime = static_cast<float>(newTime) / 1000.0f;
		m_OldTime   = GetTickCount();
		
		m_Angle += 1.57f * m_DeltaTime;
		Constant constant = {};
		constant.Angle    = m_Angle;
		
		auto device = Engine::RenderSystem::GetInstance().GetDevice();
		m_ConstantBuffer->Update(Engine::RenderSystem::GetInstance().GetDeviceContext(), &constant);
		
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			m_VertexShader, m_ConstantBuffer);
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetConstantBuffer(
			m_PixelShader, m_ConstantBuffer);
		
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetVertexShader(m_VertexShader);
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetPixelShader(m_PixelShader);
		
		Engine::RenderSystem::Draw();
	}

	auto EditorWindow::OnTerminate() -> void
	{
		Window::OnTerminate();
		m_ConstantBuffer->Release();
	}
}
