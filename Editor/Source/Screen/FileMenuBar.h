#pragma once
#include <Engine/UI/AUIScreen.h>

#include "WorldOutlinerScreen.h"

namespace Editor
{
	class FileMenuBar final : public Engine::AUIScreen
	{
	public:
		explicit FileMenuBar(Engine::ScreenID id,
							 WorldOutlinerScreen& worldOutlinerScreenRef);
		~FileMenuBar() override;

		FileMenuBar(const FileMenuBar&)                = delete;
		FileMenuBar& operator=(const FileMenuBar&)     = delete;
		FileMenuBar(FileMenuBar&&) noexcept            = delete;
		FileMenuBar& operator=(FileMenuBar&&) noexcept = delete;

	private:
		void DrawImpl() override;

		WorldOutlinerScreen& m_WorldOutlinerScreenRef;
	};
}
