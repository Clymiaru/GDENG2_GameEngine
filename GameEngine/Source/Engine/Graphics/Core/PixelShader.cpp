#include "PixelShader.h"

#include "GraphicsEngine.h"

#include "Engine/Utils/Debug.h"

Engine::PixelShader::PixelShader(const void* shaderByteCode,
                                 size_t shaderByteCodeSize) :
	m_DataSize{shaderByteCodeSize}
{
	const auto result = GraphicsEngine::GetInstance().m_D3DDevice->CreatePixelShader(shaderByteCode,
																							m_DataSize,
																							nullptr,
																							&m_Data);
	
	ENGINE_ASSERT(SUCCEEDED(result), "Shader cannot be created and initialized!")
}

Engine::PixelShader::~PixelShader()
{
	m_Data->Release();
	m_DataSize = 0;
}