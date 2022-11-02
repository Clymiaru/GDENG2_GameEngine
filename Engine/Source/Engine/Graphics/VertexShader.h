#pragma once
#include <d3d11.h>
#include "Shader.h"

namespace Engine
{
	class DeviceContext;

	class ConstantBuffer;

	class VertexShader final : public Shader
	{
	public:
		explicit VertexShader(ID3DBlob* vertexShaderBlob);

		~VertexShader() override;

		VertexShader(const VertexShader&) = delete;

		VertexShader& operator=(const VertexShader&) = delete;

		VertexShader(const VertexShader&&) = delete;

		VertexShader& operator=(const VertexShader&&) = delete;

	private:
		ID3D11VertexShader* m_Data;

		friend DeviceContext;
	};
}
