#pragma once
#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class ColorPickerHUD : public Engine::AUIScreen
	{
	public:
		ColorPickerHUD();
		~ColorPickerHUD() override;

		void Open();
		void Close();
	private:
		void DrawImpl() override;

		bool m_IsOpen = false;
	};
}
