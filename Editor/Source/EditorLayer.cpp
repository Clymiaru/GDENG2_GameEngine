#include "EditorLayer.h"
#include <Engine/Core/Debug.h>
#include <Engine/Core/Application.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/UI/UISystem.h>

#include <Engine/ECS/Entity/Camera.h>
#include <Engine/ECS/Entity/EditorCamera.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ResourceManagement/Core/ResourceSystem.h>

#include "Screen/EditorViewportScreen.h"
#include "Screen/GameViewportScreen.h"

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{"EditorLayer"} { }

	EditorLayer::~EditorLayer() = default;

	void EditorLayer::OnAttach()
	{
		using namespace Engine;
	}

	void EditorLayer::OnStart()
	{
		using namespace Engine;
		Application::GetResourceSystem().Load<Texture>("Assets/Brick1024x1024.jpg");
		
		// m_TextureResource = Application::GetResourceSystem().Get<TextureResource>("Brick1024x1024");
		
		auto* editorCamera = EntityManager::Create<EditorCamera>("EditorCamera", 512, 512);
		UISystem::Create<EditorViewportScreen>(editorCamera);

		UISystem::Create<GameViewportScreen>();

		EntityManager::Create<Camera>("GameCamera", 512, 512);

		EntityManager::Create<Cube>("Cube");
	}

	void EditorLayer::OnPollInput() { }

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
	}

	void EditorLayer::OnRender()
	{
		using namespace Engine;

		const CameraSystem& cameraSystem = Application::GetComponentSystem().GetCameraSystem();

		if (const auto gameCamera = cameraSystem.GetGameCamera();
			gameCamera != nullptr)
		{
			Application::GetRenderer().StartRender(gameCamera->GetRenderTarget());
			Application::GetComponentSystem().Render(*gameCamera);

			// gameCamera->ApplyPostProcessing();

			Application::GetRenderer().EndRender();
			
		}

		m_NumberOfEditorViewports = (int)cameraSystem.GetEditorCameraCount();
		for (int i = 0; i < m_NumberOfEditorViewports; i++)
		{
			if (const auto editorCamera = cameraSystem.GetEditorCamera(i);
				editorCamera != nullptr)
			{
				Application::GetRenderer().StartRender(editorCamera->GetRenderTarget());
				Application::GetComponentSystem().Render(*editorCamera);
				Application::GetRenderer().EndRender();
			}
		}
	}

	void EditorLayer::OnDetach()
	{
		using namespace Engine;
		Debug::Log("Editor Layer End");
	}
}
