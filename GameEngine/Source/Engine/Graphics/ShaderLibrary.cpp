#include "pch.h"
#include "ShaderLibrary.h"

#include <d3dcompiler.h>

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
}

auto Engine::ShaderLibrary::RegisterVertexShader(const std::wstring& fileName,
                                                 const std::string& entryPointName) -> void
{
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* blob      = nullptr;
	const auto result   = D3DCompileFromFile(fileName.c_str(),
	                                         nullptr,
	                                         nullptr,
	                                         entryPointName.c_str(),
	                                         "vs_5_0",
	                                         0,
	                                         0,
	                                         &blob,
	                                         &errorBlob);
	if (!SUCCEEDED(result))
	{
		if (errorBlob)
		{
			std::cout << "Vertex shader cannot be compiled! (" << static_cast<char*>(errorBlob->GetBufferPointer()) <<
					")\n";
			errorBlob->Release();
		}
	}

	m_VertexShaderMap[fileName] = CreateSharedPtr<VertexShader>(std::move(blob));
}

auto Engine::ShaderLibrary::RegisterPixelShader(const std::wstring& fileName,
                                                const std::string& entryPointName) -> void
{
	ID3DBlob* errorBlob = nullptr;
	ID3DBlob* blob      = nullptr;
	const auto result   = D3DCompileFromFile(fileName.c_str(),
	                                         nullptr,

	                                         nullptr,
	                                         entryPointName.c_str(),
	                                         "ps_5_0",
	                                         0,
	                                         0,
	                                         &blob,
	                                         &errorBlob);

	if (!SUCCEEDED(result))
	{
		if (errorBlob)
		{
			std::cout << "Pixel shader cannot be compiled! (" << static_cast<char*>(errorBlob->GetBufferPointer()) <<
					")\n";
			errorBlob->Release();
		}
	}

	m_PixelShaderMap[fileName] = CreateSharedPtr<PixelShader>(std::move(blob));
}

auto Engine::ShaderLibrary::GetVertexShader(const std::wstring& filename) -> VertexShader&
{
	return *m_VertexShaderMap[filename];
}

auto Engine::ShaderLibrary::GetPixelShader(const std::wstring& filename) -> PixelShader&
{
	return *m_PixelShaderMap[filename];
}

auto Engine::ShaderLibrary::GetVertexShaderRef(const std::wstring& filename) -> SharedPtr<VertexShader>
{
	return m_VertexShaderMap[filename];
}

auto Engine::ShaderLibrary::GetPixelShaderRef(const std::wstring& filename) -> SharedPtr<PixelShader>
{
	return m_PixelShaderMap[filename];
}

Engine::ShaderLibrary::ShaderLibrary() :
	m_VertexShaderMap{},
	m_PixelShaderMap{}
{
}

Engine::ShaderLibrary::~ShaderLibrary() = default;

