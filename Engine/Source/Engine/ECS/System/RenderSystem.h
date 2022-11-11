#pragma once
#include "Engine/ECS/Core/ListMapStorage.h"

namespace Engine
{
	class RenderComponent;

	class RenderSystem
	{
	public:
		void Register(RenderComponent* toRegister);
		void Deregister(RenderComponent* toRegister);
		
	private:
		ListMapStorage<String, RenderComponent*> m_RenderComponentStorage; 
	};
}

