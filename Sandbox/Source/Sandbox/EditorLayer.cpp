#include "pch.h"
#include "EditorLayer.h"

#include "Engine/Application.h"
#include "Engine/Time.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

Editor::EditorLayer::EditorLayer() :
	Layer("EditorLayer"),
	m_Time{0.0f},
	m_MaxTime{0.0f},
	m_Offset{0.0f},
	m_Quads{},
	m_AnimQuads{}
{
}

Editor::EditorLayer::~EditorLayer()
{
}

void Editor::EditorLayer::OnAttach()
{
	// Shader Resource Initialization
	Engine::ShaderLibrary::Register<Engine::VertexShader>(L"DefaultShader.hlsl",
	                                                      "vsmain");

	Engine::ShaderLibrary::Register<Engine::PixelShader>(L"DefaultShader.hlsl",
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
}

void Editor::EditorLayer::OnUpdate()
{
	m_Time += Engine::Time::GetDeltaTime();
	for (const auto& quad : m_Quads)
	{
		quad->Update(m_Time);
	}
}

void Editor::EditorLayer::OnRender()
{
	Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});

	const auto [left, top, right, bottom] = Engine::Application::GetClientWindowRect();
	Engine::RenderSystem::GetDeviceContext().SetViewportSize(
		Engine::Vector2Uint{
			static_cast<Engine::Uint>(right - left),
			static_cast<Engine::Uint>(bottom - top)
		});

	for (const auto& quad : m_Quads)
	{
		quad->Render();
	}

	Engine::RenderSystem::ShowFrame();
}

void Editor::EditorLayer::OnDetach()
{
}
