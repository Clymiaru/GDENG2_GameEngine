// #pragma once
// #include <d3dcompiler.h>
// #include "Utils/Utils.h"
// #include "Engine/Graphics/Shader.h"
// #include "Engine/Graphics/VertexShader.h"
// #include "Engine/Graphics/PixelShader.h"
//
// #include <functional>
//
// namespace Engine
// {
// 	constexpr const char* VertexShaderEntryPointName = "VSMain";
//
// 	constexpr const char* PixelShaderEntryPointName = "PSMain";
//
// 	inline std::string GetNameFromFilename(const StringView filename)
// 	{
// 		std::string result = filename.data();
//
// 		size_t finalBackslashPos = result.find_last_of(L'/');
//
// 		if (finalBackslashPos == std::string::npos)
// 			finalBackslashPos = 0ULL;
// 		else
// 			finalBackslashPos += 1;
//
// 		const size_t startOfExtensionPos = result.find(L'.');
//
// 		std::string shaderName = result.substr(finalBackslashPos,
// 											   startOfExtensionPos - finalBackslashPos);
// 		return shaderName;
// 	}
//
// 	template <typename ShaderType>
// 	class ShaderResource
// 	{
// 	public:
// 		ShaderResource(const StringView shaderName, ID3DBlob* shaderBlob) :
// 			m_Name{shaderName.data()},
// 			m_ShaderData{CreateUniquePtr<ShaderType>(shaderBlob)}
// 		{
// 		}
//
// 		~ShaderResource()
// 		{
// 			for (auto callback : m_ResourceUnloadCallbackList)
// 			{
// 				callback();
// 			}
// 		}
// 		
// 		const String& GetName() const
// 		{
// 			return m_Name;
// 		}
// 		
// 		ShaderType& GetShader()
// 		{
// 			
// 		}
// 	private:
// 		String m_Name;
// 		UniquePtr<ShaderType> m_ShaderData;
// 		List<std::function<void()>> m_ResourceUnloadCallbackList;
//
//
// 		// if invoked, trigger this
//
// 	};
//
// 	class ShaderLoader
// 	{
// 	public:
//
// 		template <typename ShaderType>
// 		static SharedPtr<ShaderResource<ShaderType>> Load(StringView filename)
// 		{
// 			const std::string& shaderName = GetNameFromFilename(filename.data());
//
// 			ID3DBlob* errorBlob = nullptr;
// 			ID3DBlob* blob      = nullptr;
//
// 			const std::wstring filenameWideStr = Utils::CStringToWString(filename.data());
//
// 			const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
// 												  nullptr,
// 												  nullptr,
// 												  VertexShaderEntryPointName,
// 												  "vs_5_0",
// 												  0,
// 												  0,
// 												  &blob,
// 												  &errorBlob);
//
// 			if (!SUCCEEDED(result))
// 			{
// 				if (errorBlob)
// 				{
// 					const std::string errorMessage = (char*)errorBlob->GetBufferPointer();
// 					Debug::Assert(errorBlob == nullptr, errorMessage);
// 					errorBlob->Release();
// 					return nullptr;
// 				}
// 			}
//
// 			return CreateSharedPtr<ShaderResource<ShaderType>>(blob);
// 		}
//
// 		template <typename ShaderType>
// 		static void Unload(StringView shaderName)
// 		{
// 			
// 		}
// 	};
//
// 	class ShaderLibrary final
// 	{
// 	public:
// 		static void Initialize(size_t expectedShaderCountOfAllShaders);
//
// 		static void Terminate();
//
// 		template <typename T>
// 		static void Register(StringView filename);
//
// 		template <typename T>
// 		static bool HasShader(StringView name);
//
// 		template <typename T>
// 		static T& GetShader(StringView name);
//
// 		template <typename T>
// 		static SharedPtr<T> GetShaderRef(StringView name);
//
// 		ShaderLibrary(const ShaderLibrary&) = delete;
//
// 		ShaderLibrary& operator=(const ShaderLibrary&) = delete;
//
// 		ShaderLibrary(const ShaderLibrary&&) = delete;
//
// 		ShaderLibrary& operator=(const ShaderLibrary&&) = delete;
//
// 	private:
// 		ShaderLibrary();
//
// 		~ShaderLibrary();
//
// 		static ShaderLibrary s_Instance;
//
// 		ShaderLoader m_ShaderLoader;
//
// 		HashMap<String, SharedPtr<ShaderResource<VertexShader>>> m_VertexShaderMap{};
//
// 		HashMap<String, SharedPtr<PixelShader>> m_PixelShaderMap{};
// 	};
//
// 	//---------- IS SHADER REGISTERED
// 	template <typename T>
// 	bool ShaderLibrary::HasShader(StringView name)
// 	{
// 		return false;
// 	}
//
// 	template <>
// 	inline bool ShaderLibrary::HasShader<VertexShader>(const StringView name)
// 	{
// 		return s_Instance.m_VertexShaderMap.contains(name.data());
// 	}
//
// 	template <>
// 	inline bool ShaderLibrary::HasShader<PixelShader>(const StringView name)
// 	{
// 		return s_Instance.m_PixelShaderMap.contains(name.data());
// 	}
//
// 	//---------- REGISTER SHADER
// 	template <typename T>
// 	void ShaderLibrary::Register(const StringView filename)
// 	{
// 	}
//
// 	template <>
// 	inline void ShaderLibrary::Register<VertexShader>(const StringView filename)
// 	{
// 		// const std::string& shaderName = GetNameFromFilename(filename.data());
// 		//
// 		// if (HasShader<VertexShader>(shaderName))
// 		// {
// 		// 	return;
// 		// }
// 		//
// 		// SharedPtr<ShaderResource<VertexShader>> resource = m_ShaderLoader.Load<VertexShader>(filename);
// 		//
// 		// s_Instance.m_VertexShaderMap[shaderName] = CreateSharedPtr<VertexShader>(blob);
// 	}
//
// 	template <>
// 	inline void ShaderLibrary::Register<PixelShader>(const StringView filename)
// 	{
// 		// const std::string& shaderName = GetNameFromFilename(filename.data());
// 		//
// 		// if (HasShader<PixelShader>(shaderName))
// 		// {
// 		// 	return;
// 		// }
// 		//
// 		// ID3DBlob* errorBlob = nullptr;
// 		// ID3DBlob* blob      = nullptr;
// 		//
// 		// const std::wstring filenameWideStr = Utils::CStringToWString(filename.data());
// 		//
// 		// const HRESULT result = D3DCompileFromFile(filenameWideStr.c_str(),
// 		//                                           nullptr,
// 		//                                           nullptr,
// 		//                                           PixelShaderEntryPointName,
// 		//                                           "ps_5_0",
// 		//                                           0,
// 		//                                           0,
// 		//                                           &blob,
// 		//                                           &errorBlob);
// 		//
// 		// if (!SUCCEEDED(result))
// 		// {
// 		// 	if (errorBlob)
// 		// 	{
// 		// 		std::string errorString = "Pixel shader cannot be compiled! (";
// 		// 		errorString += static_cast<char*>(errorBlob->GetBufferPointer());
// 		// 		errorString += ")\n";
// 		// 		Debug::Assert(errorBlob == nullptr, errorString);
// 		// 		errorBlob->Release();
// 		// 	}
// 		// }
// 		//
// 		// s_Instance.m_PixelShaderMap[shaderName] = CreateSharedPtr<PixelShader>(blob);
// 	}
//
// 	//---------- GET SHADER
// 	template <typename T>
// 	T& ShaderLibrary::GetShader(const StringView name)
// 	{
// 		return T();
// 	}
//
// 	template <>
// 	inline VertexShader& ShaderLibrary::GetShader<VertexShader>(const StringView name)
// 	{
// 		const bool isFound = HasShader<VertexShader>(name);
// 		Debug::Assert(isFound, "Vertex Shader is not registered!");
// 		const char* shaderName = name.data();
// 		return *s_Instance.m_VertexShaderMap[shaderName];
// 	}
//
// 	template <>
// 	inline PixelShader& ShaderLibrary::GetShader<PixelShader>(const StringView name)
// 	{
// 		const bool isFound = HasShader<PixelShader>(name);
// 		Debug::Assert(isFound, "Pixel Shader is not registered!");
// 		const char* shaderName = name.data();
// 		return *s_Instance.m_PixelShaderMap[shaderName];
// 	}
//
// 	//---------- GET SHADER REF
// 	template <typename T>
// 	inline SharedPtr<T> ShaderLibrary::GetShaderRef(const StringView name)
// 	{
// 		return nullptr;
// 	}
//
// 	template <>
// 	inline SharedPtr<VertexShader> ShaderLibrary::GetShaderRef<VertexShader>(const StringView name)
// 	{
// 		const bool isFound = HasShader<VertexShader>(name);
// 		Debug::Assert(isFound, "Vertex Shader is not registered!");
// 		const char* shaderName = name.data();
// 		return s_Instance.m_VertexShaderMap[shaderName];
// 	}
//
// 	template <>
// 	inline SharedPtr<PixelShader> ShaderLibrary::GetShaderRef<PixelShader>(const StringView name)
// 	{
// 		const bool isFound = HasShader<PixelShader>(name);
// 		Debug::Assert(isFound, "Pixel Shader is not registered!");
// 		const char* shaderName = name.data();
// 		return s_Instance.m_PixelShaderMap[shaderName];
// 	}
// }
