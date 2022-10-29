#include "pch.h"

#include "PixelShader.h"

#include "RenderSystem.h"

#include "Engine/Core/Debug.h"

namespace Engine
{
	PixelShader::PixelShader(ID3DBlob* blob) :
		Shader(blob)
	{
		const auto result = RenderSystem::GetDevice().CreatePixelShader(blob->GetBufferPointer(),
		                                                                blob->GetBufferSize(),
		                                                                nullptr,
		                                                                &m_Data);

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Shader cannot be created and initialized!")
	}

	PixelShader::~PixelShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
