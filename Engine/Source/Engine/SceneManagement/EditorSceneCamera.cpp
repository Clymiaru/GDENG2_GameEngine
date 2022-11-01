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
		const auto keyCode  = Input::Keyboard().KeyCode;
		const auto keyState = Input::Keyboard().KeyState;

		const auto mouseButton = Input::Mouse().Button;
		const auto mouseState  = Input::Mouse().State;

		const float deltaTime = (float)Application::DeltaTime();

		const auto currentPosition = Transform().Position;
		const auto currentRotation = Transform().Rotation;

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
					m_IsTrackingMouse    = true;
					m_MousePositionStart = Vector3Float((float)Input::Mouse().MousePosition.x,
					                                    (float)Input::Mouse().MousePosition.y,
					                                    0.0f);
				}
			}
		}

		if (m_IsTrackingMouse)
		{
			if (mouseButton == m_StartPan)
			{
				m_CurrentState = State::Panning;
			}
			else if (mouseButton == m_StartOrbit)
			{
				m_CurrentState = State::Orbiting;
			}

			const auto currentMousePosition = Vector3Float((float)Input::Mouse().MousePosition.x,
			                                               (float)Input::Mouse().MousePosition.y,
			                                               0.0f);
			m_MousePositionCurrent = currentMousePosition;

			Vector3Float deltaMousePosition;

			if (m_MousePositionStart.x == m_MousePositionCurrent.x &&
			    m_MousePositionStart.y == m_MousePositionCurrent.y)
			{
				deltaMousePosition = Vector3Float();
			}
			else
			{
				deltaMousePosition = m_MousePositionStart - m_MousePositionCurrent;
				deltaMousePosition.Normalize();
			}

			if (m_CurrentState == State::Panning)
			{
				m_PanDirection = Vector3Float(deltaMousePosition.x, deltaMousePosition.y, 0.0f);
			}
			else if (m_CurrentState == State::Orbiting)
			{
				m_OrbitDirection = Vector3Float(deltaMousePosition.y, deltaMousePosition.x, 0.0f);
			}

			m_MousePositionStart = m_MousePositionCurrent;
		}

		if (keyState == KeyState::KeyDown)
		{
			KeyboardInputControls(keyCode);
		}

		newPosition += ProcessPanning();

		newRotation += ProcessOrbiting();

		newPosition += ProcessZooming();

		Transform().Position += newPosition * deltaTime;
		Transform().Rotation += newRotation * deltaTime;
	}

	void EditorSceneCamera::KeyboardInputControls(KeyCode keyPressed)
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
			Transform().Position = Vector3Float(0.0f, 0.0f, -10.0f);
			Transform().Rotation = Vector3Float(0.0f, 90.0f, 0.0f);
			m_CurrentState = State::None;
		}
	}

	Vector3Float EditorSceneCamera::ProcessPanning() const
	{
		if (m_CurrentState == State::Panning)
		{
			return m_PanDirection * PanSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}

	Vector3Float EditorSceneCamera::ProcessOrbiting() const
	{
		if (m_CurrentState == State::Orbiting)
		{
			return m_OrbitDirection * OrbitSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}

	Vector3Float EditorSceneCamera::ProcessZooming() const
	{
		if (m_CurrentState == State::Zooming)
		{
			return m_ZoomDirection * ZoomSpeed;
		}
		return Vector3Float(0.0f, 0.0f, 0.0f);
	}
}
