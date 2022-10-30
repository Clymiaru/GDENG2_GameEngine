#pragma once
#include <d3d11.h>

#include "Shader.h"

namespace Engine
{
	class PixelShader final : public Shader<ID3D11PixelShader>
	{
	public:
		explicit PixelShader(ID3DBlob* blob, Renderer* renderer);

		~PixelShader() override;
	};
}
