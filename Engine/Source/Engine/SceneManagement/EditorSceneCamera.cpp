#include "pch.h"
#include "EditorSceneCamera.h"

#include "EditorSceneCameraControllerComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/Core/Debug.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	EditorSceneCamera::EditorSceneCamera(String name) :
		Camera{name}
	{
		m_CameraController = new EditorSceneCameraControllerComponent(*this);
	}

	EditorSceneCamera::~EditorSceneCamera()
	{
		delete m_CameraController;
	}

	void EditorSceneCamera::UpdateController()
	{
		m_CameraController->UpdateController();
	}
}
