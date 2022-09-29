#include "pch.h"

#include "VertexShader.h"

#include <iostream>

#include "Engine/Graphics/Core/GraphicsEngine.h"
#include "Engine/Utils/Debug.h"

Engine::VertexShader::VertexShader(const void* shaderByteCode,
                                   size_t shaderByteCodeSize) :
	m_DataSize{shaderByteCodeSize}
{
	const auto result = GraphicsEngine::GetInstance().m_D3DDevice->CreateVertexShader(shaderByteCode,
	                                                                                  m_DataSize,
	                                                                                  nullptr,
	                                                                                  &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::VertexShader::~VertexShader()
{
	m_Data->Release();
	m_DataSize = 0;
}
