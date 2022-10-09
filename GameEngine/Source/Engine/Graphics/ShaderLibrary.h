#pragma once
#include <d3dcompiler.h>
#include <unordered_map>

#include "PixelShader.h"
#include "VertexShader.h"

#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class ShaderLibrary final
	{
	public:
		ShaderLibrary(const ShaderLibrary&) = delete;

		static auto GetInstance() -> ShaderLibrary&;

		auto Initialize() -> void;

		auto Terminate() -> void;

		template <typename T>
		auto Register(const std::wstring& fileName,
		              const std::string& entryPointName) -> void;

		auto RegisterVertexAndPixelShader(const std::wstring& fileName,
		                                  const std::string& vsEntryPointName,
		                                  const std::string& psEntryPointName) -> void;

		template <typename T>
		auto IsShaderRegistered(const std::wstring& name) -> bool;

		template <typename T>
		auto GetShader(const std::wstring& name) -> T&;

		template <typename T>
		auto GetShaderRef(const std::wstring& name) -> SharedPtr<T>;

	private:
		ShaderLibrary();

		~ShaderLibrary();

		std::unordered_map<std::wstring, SharedPtr<VertexShader>> m_VertexShaderMap;

		std::unordered_map<std::wstring, SharedPtr<PixelShader>> m_PixelShaderMap;
	};

	//---------- IS SHADER REGISTERED
	template <typename T>
	auto ShaderLibrary::IsShaderRegistered(const std::wstring& name) -> bool
	{
		return false;
	}

	template <>
	inline auto ShaderLibrary::IsShaderRegistered<VertexShader>(const std::wstring& name) -> bool
	{
		return m_VertexShaderMap.contains(name);
	}

	template <>
	inline auto ShaderLibrary::IsShaderRegistered<PixelShader>(const std::wstring& name) -> bool
	{
		return m_PixelShaderMap.contains(name);
	}

	//---------- REGISTER SHADER
	template <typename T>
	auto ShaderLibrary::Register(const std::wstring& fileName,
	                             const std::string& entryPointName) -> void
	{
	}

	template <>
	inline auto ShaderLibrary::Register<VertexShader>(const std::wstring& fileName,
	                                                  const std::string& entryPointName) -> void
	{
		auto shaderName = fileName.substr(0, fileName.find(L"."));

		if (IsShaderRegistered<VertexShader>(shaderName))
		{
			return;
		}
		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;
		const auto result   = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr,
		                                         entryPointName.c_str(), "vs_5_0", 0, 0,
		                                         &blob, &errorBlob);
		if (!SUCCEEDED(result))
		{
			if (errorBlob)
			{
				std::string errorString = "Vertex shader cannot be compiled! (";
				errorString += static_cast<char*>(errorBlob->GetBufferPointer());
				errorString += ")\n";
				ENGINE_ASSERT(errorBlob != nullptr, errorString)
				errorBlob->Release();
			}
		}

		m_VertexShaderMap[shaderName] = CreateSharedPtr<VertexShader>(std::move(blob));
	}

	template <>
	inline auto ShaderLibrary::Register<PixelShader>(const std::wstring& fileName,
	                                                 const std::string& entryPointName) -> void
	{
		auto shaderName = fileName.substr(0, fileName.find(L"."));

		if (IsShaderRegistered<PixelShader>(shaderName))
		{
			return;
		}
		
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
				std::string errorString = "Pixel shader cannot be compiled! (";
				errorString += static_cast<char*>(errorBlob->GetBufferPointer());
				errorString += ")\n";
				ENGINE_ASSERT(errorBlob != nullptr, errorString)
				errorBlob->Release();
			}
		}

		m_PixelShaderMap[shaderName] = CreateSharedPtr<PixelShader>(std::move(blob));
	}

	

	//---------- GET SHADER
	template <typename T>
	auto ShaderLibrary::GetShader(const std::wstring& name) -> T&
	{
		return T();
	}

	template <>
	inline auto ShaderLibrary::GetShader<VertexShader>(const std::wstring& name) -> VertexShader&
	{
		bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return *m_VertexShaderMap[name];
	}

	template <>
	inline auto ShaderLibrary::GetShader<PixelShader>(const std::wstring& name) -> PixelShader&
	{
		bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return *m_PixelShaderMap[name];
	}

	//---------- GET SHADER REF
	template <typename T>
	inline auto ShaderLibrary::GetShaderRef(const std::wstring& name) -> SharedPtr<T>
	{
		return nullptr;
	}

	template <>
	inline auto ShaderLibrary::GetShaderRef<VertexShader>(const std::wstring& name) -> SharedPtr<VertexShader>
	{
		bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return m_VertexShaderMap[name];
	}

	template <>
	inline auto ShaderLibrary::GetShaderRef<PixelShader>(const std::wstring& name) -> SharedPtr<PixelShader>
	{
		bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return m_PixelShaderMap[name];
	}
}
