#include "pch.h"

#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

#include "Editor/EditorApplication.h"
#include "Editor/EditorWindow.h"

#include "Engine/Graphics/ShaderLibrary.h"

namespace Editor
{
	EditorApplication::EditorApplication(Engine::RectUint windowRect) :
		Application
		{
			Engine::ApplicationDescription
			{
				L"Engine Editor",
				windowRect
			}
		}
	{
		m_Window = Engine::CreateUniquePtr<EditorWindow>(m_Description.ApplicationName,
		                                                 m_Description.StartWindowRect);
	}

	EditorApplication::~EditorApplication() = default;

	auto EditorApplication::InitializeSystems() -> void
	{
		const auto rc = m_Window->GetClientWindowRect();
		Engine::RenderSystem::GetInstance().Initialize(m_Window->GetHandle(),
		                                               Engine::Vector2Int(rc.right - rc.left,
		                                                                  rc.bottom - rc.top));

		Engine::ShaderLibrary::GetInstance().Initialize();
	}

	auto EditorApplication::TerminateSystems() -> void
	{
		Engine::ShaderLibrary::GetInstance().Terminate();
		Engine::RenderSystem::GetInstance().Terminate();
	}
}
