#pragma once
#include <d3d11.h>

namespace Engine
{
	class Texture
	{
	public:
		explicit Texture(StringView path);
		~Texture();
	private:
		ID3D11ShaderResourceView* m_TextureView;
	};
}
