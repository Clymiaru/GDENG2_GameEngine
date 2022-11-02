#include "pch.h"

#include "PixelShader.h"

#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	PixelShader::PixelShader(ID3DBlob* blob) :
		Shader(blob)
	{
		const auto result = Renderer::CreatePixelShader(blob->GetBufferPointer(),
		                                                blob->GetBufferSize(),
		                                                &m_Data);

		Debug::Assert(SUCCEEDED(result), "Shader cannot be created and initialized!");
	}

	PixelShader::~PixelShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
