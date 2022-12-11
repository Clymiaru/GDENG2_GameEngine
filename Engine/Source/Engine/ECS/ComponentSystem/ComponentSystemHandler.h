#pragma once

#include "CameraSystem.h"
#include "InputSystem.h"
#include "RenderSystem.h"


namespace Engine
{
	class ComponentSystemHandler final
	{
	public:
		ComponentSystemHandler();
		~ComponentSystemHandler();

		CameraSystem& GetCameraSystem() const;

		InputSystem& GetInputSystem() const;

		void ProcessInputs(const InputData& inputData);

		void UpdateCameras();
		
		void Render(CameraComponent& camera);

		void Render(EditorCameraComponent& camera);

	private:
		CameraSystem* m_CameraSystem;
		RenderSystem* m_RenderSystem;
		InputSystem* m_InputSystem;
	};
}
