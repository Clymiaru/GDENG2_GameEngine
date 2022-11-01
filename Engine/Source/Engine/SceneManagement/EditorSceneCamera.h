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
		enum class State
		{
			None, Panning, Zooming, Orbiting
		};
		
		EditorSceneCamera(String name);

		~EditorSceneCamera() override;

		void UpdateController();

		float ZoomSpeed = 1000.0f;
		float PanSpeed = 1000.0f;
		float OrbitSpeed = 1000.0f;

	protected:
		EditorSceneCameraControllerComponent* m_CameraController;

		State m_CurrentState = State::None;

		void KeyboardInputControls(KeyCode keyPressed);
		Vector3Float ProcessPanning() const;
		Vector3Float ProcessOrbiting() const;
		Vector3Float ProcessZooming() const;

		Vector3Float m_ZoomDirection;
		Vector3Float m_PanDirection;
		Vector3Float m_OrbitDirection;
		
		// Keyboard Controls
		KeyCode m_MoveForward = KeyCode::W;
		KeyCode m_MoveBackward = KeyCode::S;
		KeyCode m_OribitRightward = KeyCode::D;
		KeyCode m_OribitLeftward = KeyCode::A;
		KeyCode m_ResetCameraToOrigin = KeyCode::Space;
		// Mouse Controls
		MouseButton m_StartPan = MouseButton::MiddleButton;
		MouseButton m_StartOrbit = MouseButton::RightButton;
		bool m_IsTrackingMouse = true;
		Vector3Float m_MousePositionStart;
		Vector3Float m_MousePositionCurrent;
	};
}
