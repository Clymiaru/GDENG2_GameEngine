#pragma once
#include <d3dcompiler.h>

#include "Engine/Graphics/Renderer.h"
#include "Engine/Graphics/RenderDevice.h"

#include "Engine/Graphics/Shader/VertexShader.h"
#include "Engine/Graphics/Shader/PixelShader.h"

#include "Engine/Core/Application.h"

namespace Engine
{
	inline std::string GetNameFromFilename(const StringView filename)
	{
		std::string result = filename.data();

		size_t finalBackslashPos = result.find_last_of(L'/');

		if (finalBackslashPos == std::string::npos)
			finalBackslashPos = 0ULL;
		else
			finalBackslashPos += 1;

		const size_t startOfExtensionPos = result.find(L'.');

		std::string shaderName = result.substr(finalBackslashPos,
											   startOfExtensionPos - finalBackslashPos);
		return shaderName;
	}

	class Resource
	{
	public:
		explicit Resource(StringView shaderName);

		~Resource() = default;

		const String& GetName() const
		{
			return m_Name;
		}

		Resource(const Resource&)                = delete;
		Resource& operator=(const Resource&)     = delete;
		Resource(Resource&&) noexcept            = delete;
		Resource& operator=(Resource&&) noexcept = delete;

	private:
		String m_Name;
		// List<std::function<void()>> m_ResourceUnloadCallbackList; // if invoked, trigger this
	};

	template <typename ShaderType>
	class ShaderResource final : public Resource
	{
	public:
		ShaderResource(StringView shaderName, ID3DBlob* shaderBlob);

		~ShaderResource()
		{
			// for (auto callback : m_ResourceUnloadCallbackList)
			// {
			// 	callback();
			// }
		}

		ShaderType& GetShader()
		{
			return *m_ShaderData;
		}

		ShaderResource(const ShaderResource&)                = delete;
		ShaderResource& operator=(const ShaderResource&)     = delete;
		ShaderResource(ShaderResource&&) noexcept            = delete;
		ShaderResource& operator=(ShaderResource&&) noexcept = delete;

	private:
		UniquePtr<ShaderType> m_ShaderData;
		// List<std::function<void()>> m_ResourceUnloadCallbackList; // if invoked, trigger this
	};

	using VertexShaderResource = ShaderResource<VertexShader>;
	using PixelShaderResource = ShaderResource<PixelShader>;

	using VertexShaderResourceRef = SharedPtr<VertexShaderResource>;
	using PixelShaderResourceRef = SharedPtr<PixelShaderResource>;

	template <typename ShaderType>
	ShaderResource<ShaderType>::ShaderResource(const StringView shaderName, ID3DBlob* shaderBlob) :
		Resource{"Unnamed"},
		m_ShaderData{nullptr} {}

	template <>
	inline VertexShaderResource::ShaderResource(const StringView shaderName, ID3DBlob* shaderBlob) :
		Resource{shaderName.data()},
		m_ShaderData{Application::GetRenderer().GetDevice().CreateVertexShader(shaderBlob)}
	{
	}

	template <>
	inline PixelShaderResource::ShaderResource(const StringView shaderName, ID3DBlob* shaderBlob) :
		Resource{shaderName.data()},
		m_ShaderData{Application::GetRenderer().GetDevice().CreatePixelShader(shaderBlob)}
	{
	}
}
