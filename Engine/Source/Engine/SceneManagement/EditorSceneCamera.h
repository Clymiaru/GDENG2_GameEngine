#pragma once

#include "Engine/Core/Core.h"
#include "Engine/ECS/Entity/Camera.h"

namespace Engine
{
	class EditorSceneCameraControllerComponent;

	class EditorSceneCamera final : public Camera
	{
	public:
		explicit EditorSceneCamera(StringView name);

		~EditorSceneCamera() override;

		void UpdateController();

	protected:
		EditorSceneCameraControllerComponent* m_CameraController;
	};
}
