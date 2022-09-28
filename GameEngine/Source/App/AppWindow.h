#pragma once
#include "Engine/Window.h"
#include "Engine/Graphics/Core/GraphicsEngine.h"
#include "Engine/Graphics/Core/PixelShader.h"
#include "Engine/Graphics/Core/VertexShader.h"
#include "Engine/Graphics/Primitives/Triangle.h"

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
		Engine::Scope<Engine::ConstantBuffer> m_ConstantBuffer;

		Engine::Scope<Engine::VertexShader> m_VertexShader;

		Engine::Scope<Engine::PixelShader> m_PixelShader;

		Engine::Scope<Engine::Triangle> m_Triangle;

		unsigned long m_OldTime = 0;
		float m_DeltaTime = 0;
		float m_Angle = 0;
	};
}
