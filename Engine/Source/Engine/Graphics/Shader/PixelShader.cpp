#include "pch.h"
#include "PixelShader.h"

#include "Engine/Graphics/RenderDevice.h"

namespace Engine
{
	PixelShader::PixelShader(ID3D11Device& deviceRef,
	                         ID3DBlob* blob) :
		Shader(blob),
		m_Data{nullptr}
	{
		const HRESULT result = deviceRef.CreatePixelShader(blob->GetBufferPointer(),
		                                                   blob->GetBufferSize(),
		                                                   nullptr,
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
