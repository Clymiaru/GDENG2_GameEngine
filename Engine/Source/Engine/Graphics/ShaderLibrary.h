#pragma once
#include <d3dcompiler.h>

#include "Engine/Core/Core.h"
#include "Engine/Core/Debug.h"
#include "Utils/Utils.h"

#include "VertexShader.h"
#include "PixelShader.h"

namespace Engine
{
	class ShaderLibrary final
	{
	public:
		static void Initialize(size_t expectedShaderCountOfAllShaders);

		static void Terminate();

		template <typename T>
		static void Register(const std::string& fileName,
		                     const std::string& entryPointName);

		template <typename T>
		static bool IsShaderRegistered(const std::string& name);

		template <typename T>
		static T& GetShader(const std::string& name);

		template <typename T>
		static SharedPtr<T> GetShaderRef(const std::string& name);

		ShaderLibrary(const ShaderLibrary&) = delete;

		ShaderLibrary& operator=(const ShaderLibrary&) = delete;

		ShaderLibrary(const ShaderLibrary&&) = delete;

		ShaderLibrary& operator=(const ShaderLibrary&&) = delete;

	private:
		ShaderLibrary();

		~ShaderLibrary();

		static std::string GetShaderNameFromFilename(const std::string& fileName);

		static ShaderLibrary s_Instance;

		HashMap<std::string, SharedPtr<VertexShader>> m_VertexShaderMap;

		HashMap<std::string, SharedPtr<PixelShader>> m_PixelShaderMap;
	};

	//---------- IS SHADER REGISTERED
	template <typename T>
	bool ShaderLibrary::IsShaderRegistered(const std::string& name)
	{
		return false;
	}

	template <>
	inline bool ShaderLibrary::IsShaderRegistered<VertexShader>(const std::string& name)
	{
		return s_Instance.m_VertexShaderMap.contains(name);
	}

	template <>
	inline bool ShaderLibrary::IsShaderRegistered<PixelShader>(const std::string& name)
	{
		return s_Instance.m_PixelShaderMap.contains(name);
	}

	//---------- REGISTER SHADER
	template <typename T>
	void ShaderLibrary::Register(const std::string& fileName,
	                             const std::string& entryPointName)
	{
	}

	template <>
	inline void ShaderLibrary::Register<VertexShader>(const std::string& fileName,
	                                                  const std::string& entryPointName)
	{
		const std::string& shaderName = GetShaderNameFromFilename(fileName);

		if (IsShaderRegistered<VertexShader>(shaderName))
		{
			return;
		}

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;

		const std::wstring filenameWideStr = Utils::CStringToWString(fileName);

		const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
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
				std::string errorString = "Vertex shader cannot be compiled! (";
				errorString += static_cast<char*>(errorBlob->GetBufferPointer());
				errorString += ")\n";
				Debug::Assert(errorBlob == nullptr, errorString);
				errorBlob->Release();
			}
		}

		s_Instance.m_VertexShaderMap[shaderName] = CreateSharedPtr<VertexShader>(blob);
	}

	template <>
	inline void ShaderLibrary::Register<PixelShader>(const std::string& fileName,
	                                                 const std::string& entryPointName)
	{
		const std::string& shaderName = GetShaderNameFromFilename(fileName);

		if (IsShaderRegistered<PixelShader>(shaderName))
		{
			return;
		}

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;

		const std::wstring filenameWideStr = Utils::CStringToWString(fileName);

		const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
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
				Debug::Assert(errorBlob == nullptr, errorString);
				errorBlob->Release();
			}
		}

		s_Instance.m_PixelShaderMap[shaderName] = CreateSharedPtr<PixelShader>(blob);
	}

	//---------- GET SHADER
	template <typename T>
	T& ShaderLibrary::GetShader(const std::string& name)
	{
		return T();
	}

	template <>
	inline VertexShader& ShaderLibrary::GetShader<VertexShader>(const std::string& name)
	{
		const bool isFound = IsShaderRegistered<VertexShader>(name);
		Debug::Assert(isFound, "Vertex Shader is not registered!");
		return *s_Instance.m_VertexShaderMap[name];
	}

	template <>
	inline PixelShader& ShaderLibrary::GetShader<PixelShader>(const std::string& name)
	{
		const bool isFound = IsShaderRegistered<PixelShader>(name);
		Debug::Assert(isFound, "Pixel Shader is not registered!");
		return *s_Instance.m_PixelShaderMap[name];
	}

	//---------- GET SHADER REF
	template <typename T>
	inline SharedPtr<T> ShaderLibrary::GetShaderRef(const std::string& name)
	{
		return nullptr;
	}

	template <>
	inline SharedPtr<VertexShader> ShaderLibrary::GetShaderRef<VertexShader>(const std::string& name)
	{
		const bool isFound = IsShaderRegistered<VertexShader>(name);
		Debug::Assert(isFound, "Vertex Shader is not registered!");
		return s_Instance.m_VertexShaderMap[name];
	}

	template <>
	inline SharedPtr<PixelShader> ShaderLibrary::GetShaderRef<PixelShader>(const std::string& name)
	{
		const bool isFound = IsShaderRegistered<PixelShader>(name);
		Debug::Assert(isFound, "Pixel Shader is not registered!");
		return s_Instance.m_PixelShaderMap[name];
	}
}
