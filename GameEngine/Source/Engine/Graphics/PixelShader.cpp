#include "pch.h"

#include "PixelShader.h"

#include "RenderSystem.h"

#include "Engine/Utils/Debug.h"

Engine::PixelShader::PixelShader(const void* shaderByteCode,
                                 size_t shaderByteCodeSize) :
	m_DataBlob{nullptr},
	m_DataSize{shaderByteCodeSize}
{
	const auto result = RenderSystem::GetInstance().GetDevice()->CreatePixelShader(shaderByteCode,
	                                                                               m_DataSize,
	                                                                               nullptr,
	                                                                               &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::PixelShader::PixelShader(ID3DBlob* pixelShaderBlob)
{
	m_DataBlob        = std::move(pixelShaderBlob);
	m_DataSize        = m_DataBlob->GetBufferSize();
	const auto result = RenderSystem::GetInstance().GetDevice()->CreatePixelShader(m_DataBlob->GetBufferPointer(),
	                                                                               m_DataBlob->GetBufferSize(),
	                                                                               nullptr,
	                                                                               &m_Data);

	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::PixelShader::~PixelShader()
{
	m_DataBlob->Release();
	m_Data->Release();
	m_DataSize = 0;
}

auto Engine::PixelShader::GetData() -> void*
{
	return m_DataBlob->GetBufferPointer();
}

auto Engine::PixelShader::GetDataSize() -> size_t
{
	return m_DataBlob->GetBufferSize();
}
