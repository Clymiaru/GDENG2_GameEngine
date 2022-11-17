#pragma once

// Idea:
// ResourceSystem::Load<VertexShader>("VertexShaderPath");
// ResourceSystem::Get<VertexShader>("VertexShaderName");
// ResourceSystem::Unload<VertexShader>("VertexShaderName");

namespace Engine
{
	class ResourceSystem
	{
	public:
		template <typename ResourceType>
		void Load(StringView filepath);

		template <typename ResourceType>
		SharedPtr<ResourceType> Get(StringView resourceName);

		template <typename ResourceType>
		void Unload(StringView resourceName);
		
	private:
		// Respective ResourceLibraries
		
	};
	
	template <typename ResourceType>
	void ResourceSystem::Load(StringView filepath)
	{
		Debug::Log("ResourceSystem Load(): Unimplemented for this resource type!");
	}
	
	template <typename ResourceType>
	SharedPtr<ResourceType> ResourceSystem::Get(StringView resourceName)
	{
		Debug::Log("ResourceSystem Get(): Unimplemented for this resource type!");
		return nullptr;
	}
	
	template <typename ResourceType>
	void ResourceSystem::Unload(StringView resourceName)
	{
		Debug::Log("ResourceSystem Unload(): Unimplemented for this resource type!");
	}
}
