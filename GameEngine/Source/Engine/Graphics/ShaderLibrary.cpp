#include "pch.h"
#include "ShaderLibrary.h"


auto Engine::ShaderLibrary::GetInstance() -> ShaderLibrary&
{
	static ShaderLibrary instance;
	return instance;
}

auto Engine::ShaderLibrary::Initialize() -> void
{
}

auto Engine::ShaderLibrary::Terminate() -> void
{
	m_VertexShaderMap.clear();
	m_PixelShaderMap.clear();
}

auto Engine::ShaderLibrary::RegisterVertexAndPixelShader(const std::wstring& fileName,
                                                         const std::string& vertexShaderEntryPointName,
                                                         const std::string& pixelShaderEntryPointName) -> void
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
