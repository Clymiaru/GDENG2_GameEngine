#include "pch.h"
#include "Shader.h"

namespace Engine
{
	Shader::Shader(ID3DBlob* blob) :
		m_Blob{blob}
	{
	}

	Shader::~Shader()
	{
		m_Blob->Release();
	}

	void* Shader::ByteCodeData() const
	{
		return m_Blob->GetBufferPointer();
	}

	size_t Shader::ByteCodeSizeData() const
	{
		return m_Blob->GetBufferSize();
	}
}

