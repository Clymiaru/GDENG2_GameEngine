#include "VertexShader.h"

#include <iostream>

#include "Engine/Graphics/GraphicsEngine.h"

Engine::VertexShader::VertexShader() :
	m_Data{nullptr},
	m_Length{0}
{
}

auto Engine::VertexShader::Init(const void* shaderByteCode,
                                size_t byteCodeSize) -> bool
{
	const auto result = GraphicsEngine::GetInstance().m_D3DDevice->CreateVertexShader(shaderByteCode,
	                                                                                  byteCodeSize,
	                                                                                  nullptr,
	                                                                                  &m_Data);

	if (!SUCCEEDED(result))
	{
		std::cout << "Error init vertex shader!\n";
		return false;
	}
	return true;
}

auto Engine::VertexShader::Release() const -> void
{
	m_Data->Release();
}
