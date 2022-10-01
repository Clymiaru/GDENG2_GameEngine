#pragma once
#include "Engine/Window.h"
#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexShader.h"

namespace Editor
{
	class EditorWindow final : public Engine::Window
	{
	public:
		EditorWindow(const std::wstring& windowName,
		             Engine::Vector2Int windowSize);

		~EditorWindow() override;

		auto OnCreate() -> void override;

		auto OnStart() -> void override;

		auto OnUpdate() -> void override;

		auto OnTerminate() -> void override;

	private:
		Engine::ScopePtr<Engine::ConstantBuffer> m_ConstantBuffer;

		Engine::ScopePtr<Engine::VertexShader> m_VertexShader;

		Engine::ScopePtr<Engine::PixelShader> m_PixelShader;

		unsigned long m_OldTime = 0;

		float m_DeltaTime = 0;

		float m_Angle = 0;
	};
}
