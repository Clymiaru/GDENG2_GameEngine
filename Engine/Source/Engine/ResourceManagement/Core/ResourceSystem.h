#pragma once

#include "Engine/ResourceManagement/Shader/ShaderLibrary.h"
#include "Engine/ResourceManagement/Texture/TextureLibrary.h"

// Idea:
// ResourceSystem::Load<VertexShader>("VertexShaderPath");
// ResourceSystem::Get<VertexShader>("VertexShaderName");
// ResourceSystem::Unload<VertexShader>("VertexShaderName");

namespace Engine
{
	class ResourceSystem
	{
	public:
		ResourceSystem();
		~ResourceSystem();

		template <typename ResourceType>
		void Load(StringView filepath);

		template <typename ResourceType>
		SharedPtr<ResourceType> Get(StringView resourceName);

		template <typename ResourceType>
		void Unload(StringView resourceName);

	private:
		static ResourceSystem* s_Instance;

		ShaderLibrary m_ShaderLibrary;
		TextureLibrary m_TextureLibrary;
	};

	template <typename ResourceType>
	void ResourceSystem::Load(StringView filepath)
	{
		Debug::Log("ResourceSystem Load(): Unimplemented for this resource type!");
	}

	template <>
	inline void ResourceSystem::Load<VertexShader>(const StringView filepath)
	{
		m_ShaderLibrary.Register<VertexShader>(filepath);
	}

	template <>
	inline void ResourceSystem::Load<PixelShader>(const StringView filepath)
	{
		m_ShaderLibrary.Register<PixelShader>(filepath);
	}

	template <>
	inline void ResourceSystem::Load<Texture>(const StringView filepath)
	{
		m_TextureLibrary.Register(filepath);
	}

	template <typename ResourceType>
	SharedPtr<ResourceType> ResourceSystem::Get(StringView resourceName)
	{
		Debug::Log("ResourceSystem Get(): Unimplemented for this resource type!");
		return nullptr;
	}

	template <>
	inline VertexShaderResourceRef ResourceSystem::Get(const StringView resourceName)
	{
		return m_ShaderLibrary.GetShader<VertexShader>(resourceName);
	}

	template <>
	inline PixelShaderResourceRef ResourceSystem::Get(const StringView resourceName)
	{
		return m_ShaderLibrary.GetShader<PixelShader>(resourceName);
	}

	template <>
	inline SharedPtr<TextureResource> ResourceSystem::Get(const StringView resourceName)
	{
		return m_TextureLibrary.GetTexture(resourceName);
	}

	template <typename ResourceType>
	void ResourceSystem::Unload(StringView resourceName)
	{
		Debug::Log("ResourceSystem Unload(): Unimplemented for this resource type!");
	}
}
