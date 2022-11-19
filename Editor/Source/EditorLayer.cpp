#include "EditorLayer.h"

#include <Engine/Core/Application.h>
#include <Engine/Core/Debug.h>
#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/Graphics/Renderer.h>

// #include <Engine/Core/Application.h>
// #include <Engine/ECS/Component/RenderComponent.h>
// #include <Engine/Graphics/Renderer.h>
// #include <Engine/Resource/ShaderLibrary.h>
// #include <Engine/Input/Input.h>
//
// #include <Engine/ECS/Component/TransformComponent.h>
//
// #include <Engine/Graphics/RenderQuad.h>
//
// #include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
// #include <Engine/Graphics/Primitives/Primitive.h>
// #include <Engine/UI/UISystem.h>
//
// #include <Utils/Random.h>
//
// #include "../../Engine/Dependencies/ImGui/imgui.h"
//
// #include "Screen/PlaceholderHUD.h"
// #include "Screen/EntityPropertiesPanel.h"
// #include "Screen/PostProcessingPanel.h"
// #include "Screen/WorldOutlinerPanel.h"

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
		EntityManager::Create<Cube>();
	}

	void EditorLayer::OnPollInput() { }

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
	}

	void EditorLayer::OnRender()
	{
		using namespace Engine;

		CameraSystem& cameraSystem = Application::GetComponentSystem().GetCameraSystem();

		if (CameraComponent* gameCamera = cameraSystem.GetGameCamera();
			gameCamera != nullptr)
		{
			Application::GetRenderer().StartRender(gameCamera->GetRenderTarget());
			Application::GetComponentSystem().Render(*gameCamera);
			Application::GetRenderer().EndRender();
		}
		
		for (int i = 0; i < m_NumberOfEditorViewports; i++)
		{
			if (CameraComponent* editorCamera = cameraSystem.GetEditorCamera(i);
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
