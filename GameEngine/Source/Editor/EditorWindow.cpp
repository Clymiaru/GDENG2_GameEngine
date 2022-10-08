#include "pch.h"
#include "EditorWindow.h"

#include "Windows.h"

#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

#include "Engine/Graphics/RenderObjects/Quad.h"

namespace Editor
{
	EditorWindow::EditorWindow(const std::wstring& windowName,
	                           const Engine::RectUint& windowRect) :
		Window()
	{
	}

	EditorWindow::~EditorWindow() = default;

	auto EditorWindow::OnStart() -> void
	{
		std::cout << "Editor Window Start\n";

		// Shader Resource Initialization
		Engine::ShaderLibrary::GetInstance().RegisterVertexShader(L"SinTimeAnimShader.hlsl",
		                                                          "vsmain");

		Engine::ShaderLibrary::GetInstance().RegisterPixelShader(L"SinTimeAnimShader.hlsl",
		                                                         "psmain");

		Engine::ShaderLibrary::GetInstance().RegisterVertexShader(L"QuadAnimShader.hlsl",
																  "vsmain");

		Engine::ShaderLibrary::GetInstance().RegisterPixelShader(L"QuadAnimShader.hlsl",
																 "psmain");

		// Object initialization
		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{-300.0f, 100.0f, 0.0f},
		                                                        Engine::Vector2Float{400.f, 400.0f},
		                                                        Engine::Color32{0.68f, 0, 0.83f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{200.0f, 125.0f, 0.0f},
		                                                        Engine::Vector2Float{225.0f, 425.0f},
		                                                        Engine::Color32{0.27f, 0.51f, 0.41f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{200.0f, -225.0f, 0.0f},
		                                                        Engine::Vector2Float{500.0f, 225.0f},
		                                                        Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f}));

		m_AnimQuads.push_back(Engine::CreateUniquePtr<Editor::AnimatedQuad>(
			Engine::Vector3Float{-100.0f, -100.0f, 0.0f},
			Engine::Vector3Float{-100.0f, -100.0f, 0.0f},
			Engine::Vector3Float{-100.0f, 100.0f, 0.0f},
			Engine::Vector3Float{-100.0f, 100.0f, 0.0f},
			Engine::Vector3Float{100.0f, 100.0f, 0.0f},
			Engine::Vector3Float{100.0f, 100.0f, 0.0f},
			Engine::Vector3Float{100.0f, -100.0f, 0.0f},
			Engine::Vector3Float{100.0f, -100.0f, 0.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f},
			Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f}));
		
	}

	auto EditorWindow::OnUpdate() -> void
	{
		m_Time = static_cast<float>(GetTickCount()) / 1000.0f;

		for (const auto& quad : m_AnimQuads)
		{
			quad->Update(m_Time);
		}
	}

	auto EditorWindow::OnRender() -> void
	{
		Engine::RenderSystem::GetInstance().Clear({0.5f, 0.5f, 1.0f, 1.0f});
		
		const auto [left, top, right, bottom] = GetClientWindowRect();
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetViewportSize(
			Engine::Vector2Uint{
				static_cast<Engine::Uint>(right - left),
				static_cast<Engine::Uint>(bottom - top)
			});

		for (const auto& quad : m_AnimQuads)
		{
			quad->Render();
			Engine::RenderSystem::GetInstance().Draw(quad->GetVertexBuffer(),
													 quad->GetIndexBuffer());
		}
		
		Engine::RenderSystem::GetInstance().ShowFrame();
	}

	auto EditorWindow::OnTerminate() -> void
	{
	}
}
