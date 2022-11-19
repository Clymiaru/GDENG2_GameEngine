#pragma once
#include <d3d11.h>

namespace Engine
{
	class RenderContext;
	class RenderDevice;
	
	// Supported image format:
	// PNG 
	class Texture
	{
	public:
		struct Specification
		{
			const char* Filepath = " ";
			// unsigned int Width;
			// unsigned int Height;
			// unsigned int MipLevels;
			// DXGI_FORMAT Format;
			// unsigned char* TextureData;
		};

		struct Profile
		{
			unsigned int Width = 0;
			unsigned int Height = 0;
			DXGI_FORMAT Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
		};

		explicit Texture(ID3D11Device& device,
						 const Specification& specs);
		~Texture();

		[[nodiscard]]
		const Profile& GetInfo() const;

		[[nodiscard]]
		Profile GetInfo();

		[[nodiscard]]
		ID3D11ShaderResourceView& GetView() const;

		[[nodiscard]]
		ID3D11SamplerState& GetSampler() const;
		
	private:
		

		Profile m_Profile;
		ID3D11ShaderResourceView* m_TextureView;
		ID3D11SamplerState* m_TextureSampler;

		friend class RenderContext;
		friend class RenderDevice;
	};
}
