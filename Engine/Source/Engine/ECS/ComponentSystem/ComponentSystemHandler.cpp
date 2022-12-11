#include "pch.h"
#include "ComponentSystemHandler.h"

namespace Engine
{
	ComponentSystemHandler::ComponentSystemHandler() :
		m_CameraSystem{new CameraSystem()},
		m_RenderSystem{new RenderSystem()},
		m_InputSystem{new InputSystem()} { }

	ComponentSystemHandler::~ComponentSystemHandler()
	{
		delete m_CameraSystem;
		delete m_RenderSystem;
	}

	CameraSystem& ComponentSystemHandler::GetCameraSystem() const
	{
		return *m_CameraSystem;
	}

	InputSystem& ComponentSystemHandler::GetInputSystem() const
	{
		return *m_InputSystem;
	}

	void ComponentSystemHandler::ProcessInputs(const InputData& inputData)
	{
		m_InputSystem->ProcessInput(inputData);	
	}

	void ComponentSystemHandler::UpdateCameras()
	{
		m_CameraSystem->GameCameraUpdate();
		m_CameraSystem->EditorCameraUpdate();
	}

	void ComponentSystemHandler::Render(CameraComponent& camera)
	{
		m_RenderSystem->Render(camera);
	}

	void ComponentSystemHandler::Render(EditorCameraComponent& camera)
	{
		m_RenderSystem->Render(camera);
	}
}
