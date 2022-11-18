#pragma once
#include "Shader.h"

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class VertexShader final : public Shader
	{
	public:
		explicit VertexShader(ID3D11Device& deviceRef,
							  ID3DBlob* vertexShaderBlob);

		~VertexShader() override;
		
		VertexShader(const VertexShader&) = delete;
		VertexShader& operator=(const VertexShader&) = delete;
		VertexShader(const VertexShader&&) = delete;
		VertexShader& operator=(const VertexShader&&) = delete;

	private:
		ID3D11VertexShader* m_Data;

		friend RenderDevice;
		friend RenderContext;
	};
}
