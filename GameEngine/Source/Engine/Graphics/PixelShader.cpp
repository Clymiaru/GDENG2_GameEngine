#include "pch.h"

#include "PixelShader.h"

#include "RenderSystem.h"

#include "Engine/Utils/Debug.h"

namespace Engine
{
	PixelShader::PixelShader(ID3DBlob* blob) :
		Shader(blob)
	{
		const auto device = RenderSystem::GetInstance().GetDevice();
		const auto result = device->CreatePixelShader(blob->GetBufferPointer(),
		                                              blob->GetBufferSize(),
		                                              nullptr,
		                                              &m_Data);

		ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
	}

	PixelShader::~PixelShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
