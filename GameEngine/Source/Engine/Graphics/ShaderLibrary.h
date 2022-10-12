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

		static ShaderLibrary& GetInstance();

		void Initialize();

		void Terminate();

		template <typename T>
		void Register(const std::wstring& fileName,
		              const std::string& entryPointName);

		void RegisterVertexAndPixelShader(const std::wstring& fileName,
		                                  const std::string& vsEntryPointName,
		                                  const std::string& psEntryPointName);

		template <typename T>
		bool IsShaderRegistered(const std::wstring& name);

		template <typename T>
		T& GetShader(const std::wstring& name);

		template <typename T>
		SharedPtr<T> GetShaderRef(const std::wstring& name);

	private:
		ShaderLibrary();

		~ShaderLibrary();

		std::unordered_map<std::wstring, SharedPtr<VertexShader>> m_VertexShaderMap;

		std::unordered_map<std::wstring, SharedPtr<PixelShader>> m_PixelShaderMap;
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
		return m_VertexShaderMap.contains(name);
	}

	template <>
	inline bool ShaderLibrary::IsShaderRegistered<PixelShader>(const std::wstring& name)
	{
		return m_PixelShaderMap.contains(name);
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
	inline void ShaderLibrary::Register<PixelShader>(const std::wstring& fileName,
	                                                 const std::string& entryPointName)
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
	T& ShaderLibrary::GetShader(const std::wstring& name)
	{
		return T();
	}

	template <>
	inline VertexShader& ShaderLibrary::GetShader<VertexShader>(const std::wstring& name)
	{
		bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return *m_VertexShaderMap[name];
	}

	template <>
	inline PixelShader& ShaderLibrary::GetShader<PixelShader>(const std::wstring& name)
	{
		bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return *m_PixelShaderMap[name];
	}

	//---------- GET SHADER REF
	template <typename T>
	inline SharedPtr<T> ShaderLibrary::GetShaderRef(const std::wstring& name)
	{
		return nullptr;
	}

	template <>
	inline SharedPtr<VertexShader> ShaderLibrary::GetShaderRef<VertexShader>(const std::wstring& name)
	{
		bool isFound = IsShaderRegistered<VertexShader>(name);
		ENGINE_ASSERT(isFound, "Vertex Shader is not registered!")
		return m_VertexShaderMap[name];
	}

	template <>
	inline SharedPtr<PixelShader> ShaderLibrary::GetShaderRef<PixelShader>(const std::wstring& name)
	{
		bool isFound = IsShaderRegistered<PixelShader>(name);
		ENGINE_ASSERT(isFound, "Pixel Shader is not registered!")
		return m_PixelShaderMap[name];
	}
}
