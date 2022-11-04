#include "SandboxLayer.h"

#include <Engine/ECS/Component/TransformComponent.h>
#include <Engine/ECS/Entity/Cube.h>
#include <Engine/ECS/Entity/Plane.h>
#include <Engine/Graphics/Renderer.h>

#include "Engine/ECS/Entity/Entity.h"
#include "../../Engine/Dependencies/ImGui/imgui.h"

// TODO: Rendering System
// TODO: Camera
// TODO: Goal: Render 3 Cubes with Camera Movement

namespace Sandbox
{
	SandboxLayer::SandboxLayer() :
		Layer{"SandboxLayer"},
		m_EntityList{Engine::List<Engine::Cube*>()},
		m_Plane{nullptr},
		m_CameraHandler{3}
	{
	}

	SandboxLayer::~SandboxLayer() = default;

	void SandboxLayer::OnAttach()
	{
		using namespace Engine;

		FramebufferProfile sceneFramebufferProfile;
		sceneFramebufferProfile.Width = Application::WindowRect().Width;
		sceneFramebufferProfile.Height = Application::WindowRect().Height;
		m_Framebuffer = CreateUniquePtr<Framebuffer>(sceneFramebufferProfile);

		
		ShaderLibrary::Register<VertexShader>("Assets/DefaultShader.hlsl",
		                                      "vsmain");

		ShaderLibrary::Register<PixelShader>("Assets/DefaultShader.hlsl",
		                                     "psmain");

		// TODO: Make cube and plane from entity and not from its own class
		Cube* cubeEntity              = new Cube("Testing Entity", Vector3Float());
		cubeEntity->Transform().Scale = Vector3Float(10.0f, 10.0f, 10.0f);
		m_EntityList.emplace_back(cubeEntity);

		m_Plane                       = new Plane("PlaneEntity", Vector3Float());
		m_Plane->Transform().Position = Vector3Float(0.0f, -5.0f, 0.0f);
		m_Plane->Transform().Scale    = Vector3Float(100.0f, 100.0f, 100.0f);

		// Initialize Scene Cameras
		m_CameraHandler.Initialize(3,
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 0, -400.0),
			                           Vector3Float(0.0f, -500.0f, -400.0f),
			                           Vector3Float(-100.0f, -400.0f, 300.0f)
		                           },
		                           List<Vector3Float>
		                           {
			                           Vector3Float(0, 90.0f, 0),
			                           Vector3Float(60.0f, 90.0f, 0),
			                           Vector3Float(60.0f, -90.0f, 0)
		                           });
	}

	void SandboxLayer::OnUpdate()
	{
		m_Frame++;
		m_Timer += (float)Engine::Application::DeltaTime();

		if (m_Timer > 60.0f)
		{
			m_Fps   = (float)m_Frame / m_Timer;
			m_Frame = 0;
			m_Timer = 0.0f;
		}

		m_CameraHandler.UpdateSceneCameraOfId(m_CurrentSceneCamera);
	}

	void SandboxLayer::OnRender()
	{
		using namespace Engine;
		Renderer::SetRenderTargetTo(&Renderer::GetSwapChain().GetBackbuffer().GetRenderTarget(),
		                            &Renderer::GetSwapChain().GetBackbuffer().GetDepthStencil());
		
		for (auto* entity : m_EntityList)
		{
			entity->Draw(m_CameraHandler.GetSceneCamera(m_CurrentSceneCamera));
		}
		m_Plane->Draw(m_CameraHandler.GetSceneCamera(m_CurrentSceneCamera));
	}

	void SandboxLayer::OnImGuiRender()
	{
		// ImGui::ShowDemoWindow(&m_IsDemoWindowOpen);
		// int entityNo = 0;
		// auto displayEntityInfo = [](Engine::Entity* toDisplay, int number) -> void
		// {
		// 	ImGui::Text("%s", toDisplay->Name().c_str());
		//
		// 	std::string positionLabel = "Position##";
		// 	positionLabel+= "Entity" + std::to_string(number);
		// 	ImGui::DragFloat3(positionLabel.c_str(), (float*)toDisplay->Transform().Position);
		//
		// 	std::string scaleLabel = "Scale##";
		// 	scaleLabel+= "Entity" + std::to_string(number);
		// 	ImGui::DragFloat3(scaleLabel.c_str(), (float*)toDisplay->Transform().Scale);
		//
		// 	std::string rotationLabel = "Rotation##";
		// 	rotationLabel+= "Entity" + std::to_string(number);
		// 	ImGui::DragFloat3(rotationLabel.c_str(), (float*)toDisplay->Transform().Rotation);
		//
		// 	ImGui::Spacing();
		// };
		//
		// ImGui::Begin("Inspector");
		//
		// for (auto* entity : m_EntityList)
		// {
		// 	displayEntityInfo(entity, entityNo);
		// 	entityNo++;
		// }
		//
		// displayEntityInfo(m_Plane, entityNo);
		//
		// ImGui::Text("FPS: %f", m_Fps);
		//
		// ImGui::Separator();
		//
		// ImGui::Text("Scene Cameras");
		//
		//
		// if (ImGui::Button("Camera 0"))
		// {
		// 	m_CurrentSceneCamera = 0;
		// }
		// ImGui::SameLine();
		//
		// if (ImGui::Button("Camera 1"))
		// {
		// 	m_CurrentSceneCamera = 1;
		// }
		// ImGui::SameLine();
		//
		// if (ImGui::Button("Camera 2"))
		// {
		// 	m_CurrentSceneCamera = 2;
		// }
		// ImGui::Separator();
		// for (auto i = 0; i < 3; i++)
		// {
		// 	std::string cameraId = "Camera" + std::to_string(i);
		//
		// 	ImGui::Text((cameraId).c_str());
		// 	
		// 	ImGui::DragFloat3((std::string("Position##") + cameraId).c_str(),
		// 		(float*)m_CameraHandler.GetSceneCamera(i).Transform().Position, 0.1f);
		//
		// 	ImGui::DragFloat3((std::string("Rotation##") + cameraId).c_str(),
		// 		(float*)m_CameraHandler.GetSceneCamera(i).Transform().Rotation, 0.1f);
		//
		// 	ImGui::Separator();
		// }
		//
		// ImGui::End();
	}

	void SandboxLayer::OnPollInput()
	{
	}

	void SandboxLayer::OnDetach()
	{
		for (auto i = 0; i < m_EntityList.size(); i++)
		{
			delete m_EntityList[i];
			m_EntityList[i] = nullptr;
		}
		delete m_Plane;

		m_EntityList.clear();

		m_CameraHandler.Terminate();
	}
}
