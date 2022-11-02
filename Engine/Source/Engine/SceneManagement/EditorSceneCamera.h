#pragma once

#include "Engine/Core/Core.h"
#include "Engine/ECS/Entity/Camera.h"
#include "Engine/Input/KeyboardInput.h"
#include "Engine/Input/MouseInput.h"

namespace Engine
{
	class EditorSceneCameraControllerComponent;
	class EditorSceneCamera final : public Camera
	{
	public:
		
		
		EditorSceneCamera(String name);

		~EditorSceneCamera() override;

		void UpdateController();

		

	protected:
		EditorSceneCameraControllerComponent* m_CameraController;

		
	};
}
