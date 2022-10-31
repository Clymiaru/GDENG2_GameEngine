#pragma once
#include "Engine/ECS/Component/AComponent.h"

namespace Engine
{
	class EditorSceneCamera;
	class EditorSceneCameraControllerComponent final : public AComponent
	{
	public:
		EditorSceneCameraControllerComponent(EditorSceneCamera* sceneCameraRef);
		~EditorSceneCameraControllerComponent() override;
	};
}

