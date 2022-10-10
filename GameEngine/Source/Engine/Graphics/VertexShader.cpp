#include "pch.h"

#include "VertexShader.h"

#include <iostream>

#include "RenderSystem.h"

#include "Engine/Utils/Debug.h"

namespace Engine
{
	VertexShader::VertexShader(ID3DBlob* vertexShaderBlob) :
		Shader(vertexShaderBlob)
	{
		const auto result = RenderSystem::GetDevice().CreateVertexShader(m_Blob->GetBufferPointer(),
		                                                                 m_Blob->GetBufferSize(),
		                                                                 nullptr,
		                                                                 &m_Data);

		ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
	}

	VertexShader::~VertexShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
