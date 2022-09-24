#include "PixelShader.h"

#include "GraphicsEngine.h"

Engine::PixelShader::PixelShader()
{
}

auto Engine::PixelShader::Release() -> void
{
	m_Data->Release();
}

auto Engine::PixelShader::Init(const void* shaderByteCode,
							   size_t byteCodeSize) -> bool
{
	if (!SUCCEEDED(GraphicsEngine::GetInstance().m_D3DDevice->CreatePixelShader(shaderByteCode,
																				  byteCodeSize,
																				  nullptr,
																				  &m_Data)))
	{
		return false;
	}

	return true;
}
