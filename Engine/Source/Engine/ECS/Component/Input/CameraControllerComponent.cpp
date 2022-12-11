#include "pch.h"
#include "CameraControllerComponent.h"

namespace Engine
{
	CameraControllerComponent::CameraControllerComponent(const EntityID& ownerID,
	                                                     SharedPtr<TransformComponent> transform) :
		AComponent{ownerID},
		m_Transform{transform}{}

	void CameraControllerComponent::ProcessInput(const InputData& input)
	{
		m_InputData = input;
	}

	void CameraControllerComponent::Update(const TimeData& time)
	{
		if (m_IsFocused)
		{
			const KeyboardInput keyInput = m_InputData.KeyInput;

			if (keyInput.KeyState == KeyState::KeyDown)
			{
				if (keyInput.KeyCode == KeyCode::Q)
				{
					m_Transform->Position.z -= 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::E)
				{
					m_Transform->Position.z += 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::A)
				{
					m_Transform->Position.x += 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::D)
				{
					m_Transform->Position.x -= 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::W)
				{
					m_Transform->Position.y += 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::S)
				{
					m_Transform->Position.y -= 50.0f * time.DeltaTimeSec;
				}

				// Rotation
				if (keyInput.KeyCode == KeyCode::J)
				{
					m_Transform->Rotation.y += 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::L)
				{
					m_Transform->Rotation.y -= 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::K)
				{
					m_Transform->Rotation.x -= 50.0f * time.DeltaTimeSec;
				}

				if (keyInput.KeyCode == KeyCode::I)
				{
					m_Transform->Rotation.x += 50.0f * time.DeltaTimeSec;
				}
			}
		}
	}
}
