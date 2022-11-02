#pragma once
#include <d3d11.h>
#include "Shader.h"

namespace Engine
{
	class DeviceContext;
	class PixelShader final : public Shader
	{
	public:
		explicit PixelShader(ID3DBlob* blob);

		~PixelShader() override;

		PixelShader(const PixelShader&) = delete;

		PixelShader& operator=(const PixelShader&) = delete;

		PixelShader(const PixelShader&&) = delete;

		PixelShader& operator=(const PixelShader&&) = delete;

	private:
		ID3D11PixelShader* m_Data;
		friend DeviceContext;
	};
}
