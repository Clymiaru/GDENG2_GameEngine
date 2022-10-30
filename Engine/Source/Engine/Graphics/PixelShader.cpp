#include "pch.h"

#include "PixelShader.h"

#include "RenderSystem.h"
#include "Renderer.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	PixelShader::PixelShader(ID3DBlob* blob,
	                         Renderer* renderer) :
		Shader(blob, renderer)
	{
		const auto result = renderer->CreatePixelShader(blob->GetBufferPointer(),
		                                                blob->GetBufferSize(),
		                                                &m_Data);

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Shader cannot be created and initialized!")
	}

	PixelShader::~PixelShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
