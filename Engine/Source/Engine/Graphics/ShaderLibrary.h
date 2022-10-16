#pragma once
#include <d3dcompiler.h>

#include "Engine/Core/Debug.h"

#include "Shader.h"

#include "VertexShader.h"

#include "PixelShader.h"

namespace Engine
{
	class PixelShader;

	class VertexShader;

	class ShaderLibrary final // NOLINT(cppcoreguidelines-special-member-functions)
	{
	public:
		static void Initialize(const size_t expectedShaderCountOfAllShaders);

		static void Terminate();

		template <typename T>
		static void Register(const std::wstring& fileName,
		                     const std::string& entryPointName);

		template <typename T>
		static bool IsShaderRegistered(const std::wstring& name);

		template <typename T>
		static T& GetShader(const std::wstring& name);

		template <typename T>
		static ShaderRef<T> GetShaderRef(const std::wstring& name);

	private:
		ShaderLibrary();

		~ShaderLibrary();

		static std::wstring GetShaderNameFromFilename(const std::wstring& fileName);

		static ShaderLibrary s_Instance;

		HashMap<std::wstring, ShaderRef<VertexShader>> m_VertexShaderMap;

		HashMap<std::wstring, ShaderRef<PixelShader>> m_PixelShaderMap;
	};

	//---------- IS SHADER REGISTERED
	template <typename T>
	bool ShaderLibrary::IsShaderRegistered(const std::wstring& name)
	{
		return false;
	}

	template <>
	inline bool ShaderLibrary::IsShaderRegistered<VertexShader>(const std::wstring& name)
	{
		return s_Instance.m_VertexShaderMap.contains(name);
	}

	template <>
	inline bool ShaderLibrary::IsShaderRegistered<PixelShader>(const std::wstring& name)
	{
		return s_Instance.m_PixelShaderMap.contains(name);
	}

	//---------- REGISTER SHADER
	template <typename T>
	void ShaderLibrary::Register(const std::wstring& fileName,
	                             const std::string& entryPointName)
	{
	}

	template <>
	inline void ShaderLibrary::Register<VertexShader>(const std::wstring& fileName,
	                                                  const std::string& entryPointName)
	{
		const std::wstring& shaderName = GetShaderNameFromFilename(fileName);

		if (IsShaderRegistered<VertexShader>(shaderName))
		{
			return;
		}

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;
		// ReSharper disable once CppTooWideScopeInitStatement
		const HRESULT result = D3DCompileFromFile(fileName.c_str(), nullptr, nullptr,
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

		s_Instance.m_VertexShaderMap[shaderName] = CreateSharedPtr<VertexShader>(std::move(blob));
	}

	template <>
	inline void ShaderLibrary::Register<PixelShader>(const std::wstring& fileName,
	                                                 const std::string& entryPointName)
	{
		const std::wstring& shaderName = GetShaderNameFromFilename(fileName);

		if (IsShaderRegistered<PixelShader>(shaderName))
		{
			return;
		}

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;
		// ReSharper disable once CppTooWideScopeInitStatement
		const HRESULT result = D3DCompileFromFile(fileName.c_str(),
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

		s_Instance.m_PixelShaderMap[shaderName] = CreateSharedPtr<PixelShader>(std::move(blob));
	}

	//---------- GET SHADER
	template <typename T>
	T& ShaderLibrary::GetShader(const std::wstring& name)
	{
		return T();
	}

	template <>
	inline VertexShader& ShaderLibrary::GetShader<VertexShader>(const std::wstring& name)
	{
		const bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return *s_Instance.m_VertexShaderMap[name];
	}

	template <>
	inline PixelShader& ShaderLibrary::GetShader<PixelShader>(const std::wstring& name)
	{
		const bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return *s_Instance.m_PixelShaderMap[name];
	}

	//---------- GET SHADER REF
	template <typename T>
	inline ShaderRef<T> ShaderLibrary::GetShaderRef(const std::wstring& name)
	{
		return nullptr;
	}

	template <>
	inline ShaderRef<VertexShader> ShaderLibrary::GetShaderRef<VertexShader>(const std::wstring& name)
	{
		const bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return s_Instance.m_VertexShaderMap[name];
	}

	template <>
	inline ShaderRef<PixelShader> ShaderLibrary::GetShaderRef<PixelShader>(const std::wstring& name)
	{
		const bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return s_Instance.m_PixelShaderMap[name];
	}
}
