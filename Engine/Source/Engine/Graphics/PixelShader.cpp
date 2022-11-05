#include "pch.h"
#include "PixelShader.h"
#include "Renderer.h"

namespace Engine
{
	PixelShader::PixelShader(ID3DBlob* blob) :
		Shader(blob),
		m_Data{nullptr}
	{
		const HRESULT result = Renderer::CreatePixelShader(blob->GetBufferPointer(),
		                                                   blob->GetBufferSize(),
		                                                   &m_Data);

		Debug::Assert(SUCCEEDED(result),
		              "Pixel Shader cannot be created and initialized!");
	}

	PixelShader::~PixelShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
