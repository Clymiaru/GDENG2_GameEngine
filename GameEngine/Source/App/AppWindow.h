#pragma once
#include <vector>

#include "Engine/Window.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Graphics/VertexBuffer.h"
#include "Engine/Graphics/VertexShader.h"
#include "Engine/Graphics/PixelShader.h"

#include "Engine/Utils/Math.h"
#include "Engine/Utils/Pointers.h"

namespace App
{
	class AppWindow final : public Engine::Window
	{
	public:
		AppWindow(const std::wstring& windowName,
		          Engine::Vector2Int windowSize);

		~AppWindow() override;

		auto OnCreate() -> void override;

		auto OnUpdate() -> void override;

		auto OnDestroy() -> void override;

	private:
		Engine::Scope<Engine::SwapChain> m_SwapChain;

		std::vector<Engine::Scope<Engine::VertexBuffer>> m_VertexBuffers;

		Engine::Scope<Engine::VertexShader> m_VertexShader;

		Engine::Scope<Engine::PixelShader> m_PixelShader;
	};
}
