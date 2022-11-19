#pragma once
#include <Engine/Math/Math.h>
#include <Engine/UI/AUIScreen.h>

namespace Engine
{
	class EditorCamera;
}
namespace Editor
{
	class EditorViewportScreen final : Engine::AUIScreen
	{
	public:
		explicit EditorViewportScreen(Engine::ScreenID id,
		                              Engine::EditorCamera* editorCamera);
		~EditorViewportScreen() override;

		EditorViewportScreen(const EditorViewportScreen&)                = delete;
		EditorViewportScreen& operator=(const EditorViewportScreen&)     = delete;
		EditorViewportScreen(EditorViewportScreen&&) noexcept            = delete;
		EditorViewportScreen& operator=(EditorViewportScreen&&) noexcept = delete;

	private:
		void DrawImpl() override;

		Engine::EditorCamera* m_EditorCameraRef = nullptr;
		Engine::Vector2Uint m_ViewportSize;
	};
}
