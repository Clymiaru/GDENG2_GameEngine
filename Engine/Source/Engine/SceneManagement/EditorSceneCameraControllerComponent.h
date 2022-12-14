#pragma once
#include "Engine/ECS/Core/AComponent.h"
#include "Engine/Input/KeyboardInput.h"
#include "Engine/Input/MouseInput.h"

namespace Engine
{
	class EditorSceneCamera;
	class EditorSceneCameraControllerComponent final : public AComponent
	{
	public:
		enum class State
		{
			None, Panning, Zooming, Orbiting
		};

		explicit EditorSceneCameraControllerComponent(EditorSceneCamera& sceneCameraRef);
		~EditorSceneCameraControllerComponent() override;

		void UpdateController();

		MAKE_COMPONENT(EditorSceneCameraController)

		float ZoomSpeed = 1000.0f;
		float PanSpeed = 1000.0f;
		float OrbitSpeed = 1000.0f;

	private:
		State m_CurrentState = State::None;

		void KeyboardInputControls(KeyCode keyPressed);
		
		[[nodiscard]]
		Vector3Float ProcessPanning() const;

		[[nodiscard]]
		Vector3Float ProcessOrbiting() const;

		[[nodiscard]]
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

