#include "pch.h"

#include "VertexShader.h"

#include <iostream>

#include "RenderSystem.h"

#include "Engine/Utils/Debug.h"

Engine::VertexShader::VertexShader(const void* shaderByteCode,
                                   size_t shaderByteCodeSize) :
	m_DataSize{shaderByteCodeSize}
{
	auto device       = RenderSystem::GetInstance().GetDevice();
	const auto result = device->CreateVertexShader(shaderByteCode,
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
