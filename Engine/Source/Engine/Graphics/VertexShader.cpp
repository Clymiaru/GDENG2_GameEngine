#include "pch.h"
#include "VertexShader.h"

#include "Engine/Core/Debug.h"

#include "Renderer.h"

namespace Engine
{
	VertexShader::VertexShader(ID3DBlob* vertexShaderBlob) :
		Shader(vertexShaderBlob)
	{
		const HRESULT result = Renderer::CreateVertexShader(m_Blob->GetBufferPointer(),
		                                                    m_Blob->GetBufferSize(),
		                                                    &m_Data);

		Debug::Assert(SUCCEEDED(result), "Vertex shader cannot be created and initialized!");
	}

	VertexShader::~VertexShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
}
