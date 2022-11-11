#pragma once
#include <Engine/UI/AUIHUD.h>

namespace Editor
{
	class ColorPickerHUD : public Engine::AUIHUD
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
