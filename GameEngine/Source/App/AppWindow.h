#pragma once

#include "Engine/Window.h"
#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/VertexBuffer.h"

namespace App
{
	class AppWindow : public Engine::Window
	{
	public:
		AppWindow(const std::wstring& windowName,
				  Engine::Vector2Int windowSize);
		~AppWindow() override;

		virtual void OnCreate() override;
		virtual void OnUpdate() override;
		virtual void OnDestroy() override;

	private:
		Engine::VertexBuffer* m_VB;
	};
}
