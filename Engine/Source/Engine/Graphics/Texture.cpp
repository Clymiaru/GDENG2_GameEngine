#include "pch.h"
#include "Texture.h"

namespace Engine
{
	Texture::Texture(StringView path) :
		m_TextureView{nullptr}
	{
		
	}
	Texture::~Texture()
	{
		if (m_TextureView != nullptr)
			m_TextureView->Release();
	}
}
