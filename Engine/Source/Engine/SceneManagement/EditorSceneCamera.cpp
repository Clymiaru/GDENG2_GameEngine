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
		m_CameraController = new EditorSceneCameraControllerComponent(this);
	}

	EditorSceneCamera::~EditorSceneCamera()
	{
		delete m_CameraController;
	}

	void EditorSceneCamera::UpdateController()
	{
		const auto keyCode = Input::Keyboard().KeyCode;
		const auto state   = Input::Keyboard().KeyState;

		float speed = 10.0f;

		float deltaTime = Application::DeltaTime() / 1000.0f;
		const auto currentPosition = Transform().Rotation;
		Vector3Float newPosition = Vector3Float();
		// if (keyCode == KeyCode::W && state == KeyState::KeyDown)
		// {
		// 	newPosition = Vector3Float(0.0f, 0.0f, speed) * deltaTime;
		// }
		// else if (keyCode == KeyCode::S && state == KeyState::KeyDown)
		// {
		// 	newPosition = Vector3Float(0.0f, 0.0f, -speed) * deltaTime;
		// }
		// else if (keyCode == KeyCode::A && state == KeyState::KeyDown)
		// {
		// 	newPosition = Vector3Float(-speed, 0.0f, 0.0f) * deltaTime;
		// }
		// else if (keyCode == KeyCode::D && state == KeyState::KeyDown)
		// {
		// 	newPosition = Vector3Float(speed, 0.0f, 0.0f) * deltaTime;
		// }

		if (keyCode == KeyCode::W && state == KeyState::KeyDown)
		{
			newPosition = Vector3Float(0.0f, 0.0f, speed) * deltaTime;
		}
		else if (keyCode == KeyCode::S && state == KeyState::KeyDown)
		{
			newPosition = Vector3Float(0.0f, 0.0f, -speed) * deltaTime;
		}
		else if (keyCode == KeyCode::A && state == KeyState::KeyDown)
		{
			newPosition = Vector3Float(-speed, 0.0f, 0.0f) * deltaTime;
		}
		else if (keyCode == KeyCode::D && state == KeyState::KeyDown)
		{
			newPosition = Vector3Float(speed, 0.0f, 0.0f) * deltaTime;
		}

		Transform().Rotation = (currentPosition + newPosition);
	}
}
