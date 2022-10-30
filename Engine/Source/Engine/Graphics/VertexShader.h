#pragma once
#include <d3d11.h>
#include "Shader.h"

namespace Engine
{
	class VertexShader final : public Shader<ID3D11VertexShader>
	{
	public:
		explicit VertexShader(ID3DBlob* vertexShaderBlob);

		~VertexShader() override;
	};
}
