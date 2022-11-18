#include "pch.h"
#include "ComponentSystemHandler.h"

namespace Engine
{
	ComponentSystemHandler::ComponentSystemHandler() :
		m_CameraSystem{new CameraSystem()},
		m_RenderSystem{new RenderSystem()} { }

	ComponentSystemHandler::~ComponentSystemHandler()
	{
		delete m_CameraSystem;
	}

	void ComponentSystemHandler::Update()
	{
		m_CameraSystem->CameraUpdate();
	}

	void ComponentSystemHandler::Render()
	{
		m_RenderSystem->Render();
	}
}
