#pragma once

#include "CameraSystem.h"
#include "RenderSystem.h"

namespace Engine
{
	class ComponentSystemHandler final
	{
	public:
		ComponentSystemHandler();
		~ComponentSystemHandler();

		CameraSystem& GetCameraSystem() const;
		
		void Update();

		void Render(CameraComponent& camera);

	private:
		CameraSystem* m_CameraSystem;
		RenderSystem* m_RenderSystem;
	};
}
