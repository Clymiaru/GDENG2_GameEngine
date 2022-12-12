#include "EditorLayer.h"
#include <Engine/Core/Debug.h>
#include <Engine/Core/Application.h>
#include <Engine/ECS/Component/RenderComponent.h>
#include <Engine/ECS/Component/Render/StaticMeshComponent.h>
#include <Engine/Graphics/Renderer.h>
#include <Engine/ECS/ComponentSystem/ComponentSystemHandler.h>
#include <Engine/ECS/Core/EntityManager.h>
#include <Engine/UI/UISystem.h>

#include <Engine/ECS/Entity/Camera.h>
#include <Engine/ECS/Entity/EditorCamera.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/Plane.h>
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
		Application::GetResourceSystem().Load<Texture>("Assets/image0-42.png");
		Application::GetResourceSystem().Load<Texture>("Assets/SuzunaDerpComfy.png");

		auto shioriTexture = Application::GetResourceSystem().Get<TextureResource>("image0-42");

		auto* editorCamera = EntityManager::Create<EditorCamera>("EditorCamera", 512UL, 512UL);
		UISystem::Create<EditorViewportScreen>(editorCamera);

		UISystem::Create<GameViewportScreen>();

		EntityManager::Create<Camera>("GameCamera", 512UL, 512UL);

		auto cubeEntity   = EntityManager::Create<Cube>("Cube");
		auto cubeRenderer = cubeEntity->GetComponent<StaticMeshComponent>();
		cubeRenderer->SetTexture(shioriTexture);

		// auto plane = EntityManager::Create<Plane>("Plane");
		// auto planeTransform = plane->GetComponent<TransformComponent>();
		// planeTransform->Scale = Vector3Float(100.0f, 100.0f, 100.0f);
	}
	
	void EditorLayer::OnPollInput(const Engine::InputData& inputData)
	{
		using namespace Engine;
		Application::GetComponentSystem().ProcessInputs(inputData);
	}
	
	void EditorLayer::OnUpdate(const Engine::TimeData& timeData)
	{
		using namespace Engine;
		Application::GetComponentSystem().UpdateCameras();
	}

	void EditorLayer::OnRender()
	{
		using namespace Engine;

		const CameraSystem& cameraSystem = Application::GetComponentSystem().GetCameraSystem();

		if (const auto gameCamera = cameraSystem.GetGameCamera();
			gameCamera != nullptr)
		{
			const auto& framebuffer = gameCamera->GetRenderTarget();

			Application::GetRenderer().SetViewportSize(Vector2Uint(framebuffer.GetInfo().Width,
			                                                       framebuffer.GetInfo().Height));
			Application::GetRenderer().SetFramebuffer(framebuffer);
			Application::GetRenderer().ClearFramebuffer(framebuffer, gameCamera->ClearColor);

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
