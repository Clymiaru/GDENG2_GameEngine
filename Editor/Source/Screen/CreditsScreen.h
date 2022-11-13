#pragma once

#include <d3d11.h>

#include <Engine/UI/AUIScreen.h>

namespace Editor
{
	class CreditsScreen final : public Engine::AUIScreen
	{
	public:
		CreditsScreen();
		~CreditsScreen() override;

		void Open();
		void Close();

	private:
		void DrawImpl() override;
		ID3D11ShaderResourceView* m_TextureView;
		int m_ImageWidth;
		int m_ImageHeight;
		bool m_IsOpen;
	};
}
