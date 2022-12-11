#pragma once
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class EditorConsoleScreen final : Engine::AUIScreen
	{
	public:
		explicit EditorConsoleScreen(Engine::ScreenID id);
		~EditorConsoleScreen() override;

		EditorConsoleScreen(const EditorConsoleScreen&)                = delete;
		EditorConsoleScreen& operator=(const EditorConsoleScreen&)     = delete;
		EditorConsoleScreen(EditorConsoleScreen&&) noexcept            = delete;
		EditorConsoleScreen& operator=(EditorConsoleScreen&&) noexcept = delete;

	private:
		void DrawImpl() override;
	};
}
