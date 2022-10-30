#include "pch.h"
#include "VertexShader.h"

#include "Engine/Core/Debug.h"

#include "Renderer.h"

namespace Engine
{
	VertexShader::VertexShader(ID3DBlob* vertexShaderBlob,
	                           Renderer* renderer) :
		Shader(vertexShaderBlob, renderer)
	{
		const HRESULT result = renderer->CreateVertexShader(m_Blob->GetBufferPointer(),
		                                                    m_Blob->GetBufferSize(),
		                                                    &m_Data);

		ENGINE_ASSERT_TRUE(SUCCEEDED(result), "Vertex shader cannot be created and initialized!")
	}

	VertexShader::~VertexShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
