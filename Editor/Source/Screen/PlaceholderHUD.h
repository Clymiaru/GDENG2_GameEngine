#pragma once
#include <Engine/UI/AUIScreen.h>

#include "ColorPickerHUD.h"

namespace Editor
{
	class PlaceholderHUD : public Engine::AUIScreen
	{
	public:
		PlaceholderHUD();
		~PlaceholderHUD() override;

		void Open();
		void Close();
	private:
		void DrawImpl() override;
		bool m_IsOpen;
		ColorPickerHUD* m_ColorPickerHUD;
	};
}
