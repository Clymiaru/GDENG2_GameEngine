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
		
		void Update();

		void Render();

	private:
		CameraSystem* m_CameraSystem;
		RenderSystem* m_RenderSystem;
	};
}
