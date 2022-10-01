#include "pch.h"

#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

#include "Editor/EditorApplication.h"
#include "Editor/EditorWindow.h"

namespace Editor
{
	EditorApplication::EditorApplication(Engine::Vector2Uint startWindowSize) :
		Application
		{
			Engine::ApplicationDescription
			{
				L"Engine Editor",
				startWindowSize
			}
		}
	{
		m_Windows.push_back(Engine::CreateUniquePtr<EditorWindow>(m_Description.ApplicationName,
		                                                          m_Description.StartWindowSize));
	}

	EditorApplication::~EditorApplication() = default;

	auto EditorApplication::InitializeSystems() -> void
	{
		for (const auto& window : m_Windows)
		{
			RECT rc = window->GetClientWindowRect();
			Engine::RenderSystem::GetInstance().Initialize(window->GetHandle(),
			                                               Engine::Vector2Int(rc.right - rc.left,
			                                                                  rc.bottom - rc.top));
		}
	}

	auto EditorApplication::TerminateSystems() -> void
	{
		Engine::RenderSystem::GetInstance().Terminate();
	}
}
