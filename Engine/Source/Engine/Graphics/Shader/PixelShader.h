#pragma once
#include "Shader.h"

namespace Engine
{
	class RenderDevice;
	class RenderContext;

	class PixelShader final : public Shader
	{
	public:
		explicit PixelShader(ID3D11Device& deviceRef,
							 ID3DBlob* blob);

		~PixelShader() override;
		
		ID3D11PixelShader& GetData() const;

		PixelShader(const PixelShader&)             = delete;
		PixelShader& operator=(const PixelShader&)  = delete;
		PixelShader(const PixelShader&&)            = delete;
		PixelShader& operator=(const PixelShader&&) = delete;

	private:
		

		ID3D11PixelShader* m_Data;

		friend class RenderDevice;
		friend class RenderContext;
	};
}
