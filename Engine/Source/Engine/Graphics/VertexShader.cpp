#include "pch.h"
#include "VertexShader.h"

#include "Engine/Core/Debug.h"

#include "RenderSystem.h"

namespace Engine
{
	VertexShader::VertexShader(ID3DBlob* vertexShaderBlob) :
		Shader(vertexShaderBlob)
	{
		const HRESULT result = RenderSystem::GetDevice().CreateVertexShader(m_Blob->GetBufferPointer(),
		                                                                    m_Blob->GetBufferSize(),
		                                                                    nullptr,
		                                                                    &m_Data);

		ENGINE_ASSERT(SUCCEEDED(result), "Vertex shader cannot be created and initialized!")
	}

	VertexShader::~VertexShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
