#pragma once
#include "Engine/ResourceManagement/Core/Resource.h"

#include "Utils/Utils.h"

namespace Engine
{
	constexpr const char* VertexShaderEntryPointName = "VSMain";
	constexpr const char* PixelShaderEntryPointName = "PSMain";

	class ShaderLoader
	{
	public:
		template <typename ShaderType>
		SharedPtr<ShaderResource<ShaderType>> Load(StringView filename);

		// TODO: Implement unloading
		// template <typename ShaderType>
		// void Unload();
	};

	template <typename ShaderType>
	SharedPtr<ShaderResource<ShaderType>> ShaderLoader::Load(StringView filename)
	{
		return nullptr;
	}

	template <>
	inline SharedPtr<VertexShaderResource> ShaderLoader::Load(const StringView filename)
	{
		const std::string& shaderName = GetNameFromFilename(filename.data());

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;

		const std::wstring filenameWideStr = Utils::CStringToWString(filename.data());

		const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
		                                          nullptr,
		                                          nullptr,
		                                          VertexShaderEntryPointName,
		                                          "vs_5_0",
		                                          0,
		                                          0,
		                                          &blob,
		                                          &errorBlob);

		if (!SUCCEEDED(result))
		{
			if (errorBlob)
			{
				const std::string errorMessage = (char*)errorBlob->GetBufferPointer();
				Debug::Assert(errorBlob == nullptr, errorMessage);
				errorBlob->Release();
				return nullptr;
			}
		}

		return CreateSharedPtr<VertexShaderResource>(shaderName, blob);
	}

	template <>
	inline SharedPtr<PixelShaderResource> ShaderLoader::Load(const StringView filename)
	{
		const std::string& shaderName = GetNameFromFilename(filename.data());

		ID3DBlob* errorBlob = nullptr;
		ID3DBlob* blob      = nullptr;

		const std::wstring filenameWideStr = Utils::CStringToWString(filename.data());

		const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
		                                          nullptr,
		                                          nullptr,
		                                          PixelShaderEntryPointName,
		                                          "ps_5_0",
		                                          0,
		                                          0,
		                                          &blob,
		                                          &errorBlob);

		if (!SUCCEEDED(result))
		{
			if (errorBlob)
			{
				const std::string errorMessage = (char*)errorBlob->GetBufferPointer();
				Debug::Assert(errorBlob == nullptr, errorMessage);
				errorBlob->Release();
				return nullptr;
			}
		}

		return CreateSharedPtr<PixelShaderResource>(shaderName, blob);
	}

	// template <typename ShaderType>
	// void ShaderLoader::Unload(StringView shaderName) {}
	//
	// template <>
	// void ShaderLoader::Unload<VertexShader>(StringView shaderName)
	// {
	// 	
	// }
	//
	// template <>
	// void ShaderLoader::Unload<PixelShader>(StringView shaderName)
	// {
	// 	
	// }

	class ShaderLibrary final
	{
	public:
		ShaderLibrary();
		~ShaderLibrary();

		template <typename ShaderType>
		void Register(StringView filename);

		template <typename ShaderType>
		bool HasShader(StringView name);

		template <typename ShaderType>
		SharedPtr<ShaderResource<ShaderType>> GetShader(StringView name);

		ShaderLibrary(const ShaderLibrary&)             = delete;
		ShaderLibrary& operator=(const ShaderLibrary&)  = delete;
		ShaderLibrary(const ShaderLibrary&&)            = delete;
		ShaderLibrary& operator=(const ShaderLibrary&&) = delete;

	private:
		ShaderLoader m_ShaderLoader;

		HashMap<String, VertexShaderResourceRef> m_VertexShaderMap{};

		HashMap<String, PixelShaderResourceRef> m_PixelShaderMap{};
	};

	//---------- IS SHADER REGISTERED
	template <typename ShaderType>
	bool ShaderLibrary::HasShader(StringView name)
	{
		return false;
	}

	template <>
	inline bool ShaderLibrary::HasShader<VertexShader>(const StringView name)
	{
		return m_VertexShaderMap.contains(name.data());
	}

	template <>
	inline bool ShaderLibrary::HasShader<PixelShader>(const StringView name)
	{
		return m_PixelShaderMap.contains(name.data());
	}

	//---------- REGISTER SHADER
	template <typename T>
	void ShaderLibrary::Register(const StringView filename) { }

	template <>
	inline void ShaderLibrary::Register<VertexShader>(const StringView filename)
	{
		const std::string& shaderName = GetNameFromFilename(filename.data());

		if (HasShader<VertexShader>(shaderName))
		{
			return;
		}

		m_VertexShaderMap[shaderName] = m_ShaderLoader.Load<VertexShader>(filename);
	}

	template <>
	inline void ShaderLibrary::Register<PixelShader>(const StringView filename)
	{
		const std::string& shaderName = GetNameFromFilename(filename.data());

		if (HasShader<PixelShader>(shaderName))
		{
			return;
		}

		m_PixelShaderMap[shaderName] = m_ShaderLoader.Load<PixelShader>(filename);
	}

	//---------- GET SHADER
	template <typename ShaderType>
	SharedPtr<ShaderResource<ShaderType>> ShaderLibrary::GetShader(const StringView name)
	{
		return nullptr;
	}

	template <>
	inline VertexShaderResourceRef ShaderLibrary::GetShader<VertexShader>(const StringView name)
	{
		const bool isFound = HasShader<VertexShader>(name);
		Debug::Assert(isFound, "Vertex Shader is not registered!");
		return m_VertexShaderMap[name.data()];
	}

	template <>
	inline PixelShaderResourceRef ShaderLibrary::GetShader<PixelShader>(const StringView name)
	{
		const bool isFound = HasShader<PixelShader>(name);
		Debug::Assert(isFound, "Pixel Shader is not registered!");
		return m_PixelShaderMap[name.data()];
	}
}
