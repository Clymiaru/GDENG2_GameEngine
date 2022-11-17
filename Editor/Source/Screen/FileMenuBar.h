#pragma once
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class FileMenuBar final : public Engine::AUIScreen
	{
	public:
		explicit FileMenuBar(Engine::ScreenID id);
		~FileMenuBar() override;

	private:
		void DrawImpl() override;
	};
}
