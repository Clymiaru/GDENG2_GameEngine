#include "pch.h"
#include "EditorSceneCameraControllerComponent.h"

#include "Engine/Core/Application.h"
#include "Engine/ECS/Component/TransformComponent.h"
#include "Engine/ECS/Entity/Entity.h"
#include "Engine/Input/Input.h"

namespace Engine
{
	EditorSceneCameraControllerComponent::EditorSceneCameraControllerComponent(EditorSceneCamera* sceneCameraRef) :
		AComponent{(Entity*)sceneCameraRef}
	{
	}

	EditorSceneCameraControllerComponent::~EditorSceneCameraControllerComponent()
	{
	}

	void EditorSceneCameraControllerComponent::UpdateController()
	{
		const auto keyCode  = Input::Keyboard().KeyCode;
		const auto keyState = Input::Keyboard().KeyState;

		const auto mouseButton = Input::Mouse().Button;
		const auto mouseState  = Input::Mouse().State;

		const float deltaTime = (float)Application::DeltaTime();

		const auto currentPosition = m_EntityRef->Transform().Position;
		const auto currentRotation = m_EntityRef->Transform().Rotation;

		Vector3Float newPosition = Vector3Float();
		Vector3Float newRotation = Vector3Float();

		m_CurrentState = State::None;

		if (m_IsTrackingMouse)
		{
			if (mouseState == MouseState::ButtonReleased)
			{
				m_IsTrackingMouse = false;
			}
		}
		else if (!m_IsTrackingMouse)
		{
			if (mouseState == MouseState::ButtonPressed)
			{
				if (mouseButton == m_StartPan ||
				    mouseButton == m_StartOrbit)
				{
					m_IsTrackingMouse = true;
				}
			}
		}

		if (m_IsTrackingMouse)
		{
			if (mouseButton == m_StartPan) { m_CurrentState = State::Panning; }
			else if (mouseButton == m_StartOrbit) { m_CurrentState = State::Orbiting; }

			auto deltaMousePosition = Vector3Float((float)Input::Mouse().DeltaMousePosition.x,
			                                       (float)Input::Mouse().DeltaMousePosition.y,
			                                       0.0f);
			deltaMousePosition.Normalize();

			if (m_CurrentState == State::Panning)
			{
				m_PanDirection = Vector3Float(deltaMousePosition.x, deltaMousePosition.y, 0.0f);
			}
			else if (m_CurrentState == State::Orbiting)
			{
				m_OrbitDirection = Vector3Float(deltaMousePosition.y, deltaMousePosition.x, 0.0f);
			}
		}

		if (keyState == KeyState::KeyDown)
		{
			KeyboardInputControls(keyCode);
		}

		newPosition += ProcessPanning();

		newRotation += ProcessOrbiting();

		newPosition += ProcessZooming();

		m_EntityRef->Transform().Position += newPosition * deltaTime;
		m_EntityRef->Transform().Rotation += newRotation * deltaTime;
	}

	void EditorSceneCameraControllerComponent::
	KeyboardInputControls(KeyCode keyPressed)
	{
		if (keyPressed == m_MoveForward)
		{
			m_CurrentState  = State::Zooming;
			m_ZoomDirection = Vector3Float(0.0f, 0.0f, 1.0f);
		}
		else if (keyPressed == m_MoveBackward)
		{
			m_CurrentState  = State::Zooming;
			m_ZoomDirection = Vector3Float(0.0f, 0.0f, -1.0f);
		}

		if (keyPressed == m_OribitLeftward)
		{
			m_CurrentState   = State::Orbiting;
			m_OrbitDirection = Vector3Float(0.0f, 1.0f, 0.0f);
		}
		else if (keyPressed == m_OribitRightward)
		{
			m_CurrentState   = State::Orbiting;
			m_OrbitDirection = Vector3Float(0.0f, -1.0f, 0.0f);
		}

		if (keyPressed == m_ResetCameraToOrigin)
		{
			m_EntityRef->Transform().Position = Vector3Float(0.0f, 0.0f, -10.0f);
			m_EntityRef->Transform().Rotation = Vector3Float(0.0f, 90.0f, 0.0f);
			m_CurrentState                    = State::None;
		}
	}

	Vector3Float EditorSceneCameraControllerComponent::
	ProcessPanning() const
	{
		if (m_CurrentState == State::Panning)
		{
			return m_PanDirection * PanSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}

	Vector3Float EditorSceneCameraControllerComponent::
	ProcessOrbiting() const
	{
		if (m_CurrentState == State::Orbiting)
		{
			return m_OrbitDirection * OrbitSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}

	Vector3Float EditorSceneCameraControllerComponent::
	ProcessZooming() const
	{
		if (m_CurrentState == State::Zooming)
		{
			return m_ZoomDirection * ZoomSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}
}
