#include "pch.h"

#include "VertexShader.h"

#include <iostream>

#include "RenderSystem.h"

#include "Engine/Utils/Debug.h"

Engine::VertexShader::VertexShader(const void* shaderByteCode,
                                   size_t shaderByteCodeSize) :
	m_DataBlob{nullptr},
	m_DataSize{shaderByteCodeSize}
{
	auto device       = RenderSystem::GetInstance().GetDevice();
	const auto result = device->CreateVertexShader(shaderByteCode,
	                                               m_DataSize,
	                                               nullptr,
	                                               &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::VertexShader::VertexShader(ID3DBlob* vertexShaderBlob)
{
	m_DataBlob = std::move(vertexShaderBlob);
	m_DataSize = m_DataBlob->GetBufferSize();

	const auto result = RenderSystem::GetInstance().GetDevice()->CreateVertexShader(m_DataBlob->GetBufferPointer(),
	                                                                                m_DataBlob->GetBufferSize(),
	                                                                                nullptr,
	                                                                                &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::VertexShader::~VertexShader()
{
	m_DataBlob->Release();
	m_Data->Release();
	m_DataSize = 0;
}

auto Engine::VertexShader::GetData() -> void*
{
	return m_DataBlob->GetBufferPointer();
}

auto Engine::VertexShader::GetDataSize() -> size_t
{
	return m_DataBlob->GetBufferSize();
}
