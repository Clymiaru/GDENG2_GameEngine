#include "pch.h"
#include "VertexShader.h"

#include "Engine/Graphics/RenderDevice.h"

namespace Engine
{
	VertexShader::VertexShader(ID3D11Device& deviceRef,
	                           ID3DBlob* vertexShaderBlob) :
		Shader(vertexShaderBlob),
		m_Data{nullptr}
	{
		const HRESULT result = deviceRef.CreateVertexShader(m_Blob->GetBufferPointer(),
		                                                    m_Blob->GetBufferSize(),
		                                                    nullptr,
		                                                    &m_Data);

		Debug::Assert(SUCCEEDED(result),
		              "Vertex shader cannot be created and initialized!");
	}

	VertexShader::~VertexShader()
	{
		m_Data->Release();
		m_Blob->Release();
	}
	
	ID3D11VertexShader& VertexShader::GetData() const
	{
		return *m_Data;
	}
}
