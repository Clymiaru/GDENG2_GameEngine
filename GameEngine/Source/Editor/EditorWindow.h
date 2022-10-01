#pragma once
#include "Engine/Window.h"
#include "Engine/Graphics/Primitives/Quad.h"
#include "Engine/Utils/DataStructures.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class ConstantBuffer;

	class PixelShader;

	class VertexShader;
}

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
		Engine::UniquePtr<Engine::ConstantBuffer> m_ConstantBuffer;

		Engine::UniquePtr<Engine::VertexShader> m_VertexShader;

		Engine::UniquePtr<Engine::PixelShader> m_PixelShader;

		unsigned long m_OldTime = 0;

		float m_DeltaTime = 0;

		float m_Time = 0;

		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Quads;
	};
}
