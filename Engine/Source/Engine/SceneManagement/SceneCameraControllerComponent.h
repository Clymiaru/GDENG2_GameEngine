#pragma once
#include "Engine/ECS/Component/AComponent.h"

namespace Engine
{
	class SceneCamera;
	class SceneCameraControllerComponent final : public AComponent
	{
	public:
		SceneCameraControllerComponent(SceneCamera* sceneCameraRef);
		~SceneCameraControllerComponent() override;
	};
}

