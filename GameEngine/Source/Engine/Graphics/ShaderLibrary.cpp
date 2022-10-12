#include "pch.h"
#include "ShaderLibrary.h"

Engine::ShaderLibrary& Engine::ShaderLibrary::GetInstance()
{
	static ShaderLibrary instance;
	return instance;
}

void Engine::ShaderLibrary::Initialize()
{
}

void Engine::ShaderLibrary::Terminate()
{
	m_VertexShaderMap.clear();
	m_PixelShaderMap.clear();
}

void Engine::ShaderLibrary::RegisterVertexAndPixelShader(const std::wstring& fileName,
                                                         const std::string& vertexShaderEntryPointName,
                                                         const std::string& pixelShaderEntryPointName)
{
	Register<VertexShader>(fileName, vertexShaderEntryPointName);
	Register<PixelShader>(fileName, pixelShaderEntryPointName);
}

Engine::ShaderLibrary::ShaderLibrary() :
	m_VertexShaderMap{},
	m_PixelShaderMap{}
{
}

Engine::ShaderLibrary::~ShaderLibrary() = default;
