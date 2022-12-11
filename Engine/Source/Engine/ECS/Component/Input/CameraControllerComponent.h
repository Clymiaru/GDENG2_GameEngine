#pragma once
#include "Engine/Core/Time.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Core/AComponent.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	class CameraControllerComponent : public AComponent
	{
	public:
		explicit CameraControllerComponent(const EntityID& ownerID,
		                                   SharedPtr<TransformComponent> transform);

		void ProcessInput(const InputData& input);

		void Update(const TimeData& time);

		MAKE_COMPONENT(CameraController)

	private:
		bool m_IsFocused;
		SharedPtr<TransformComponent> m_Transform;
		InputData m_InputData;
	};
}
