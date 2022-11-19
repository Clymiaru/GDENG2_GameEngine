#pragma once
#include "Engine/ResourceManagement/Core/Resource.h"

namespace Engine
{
	class TextureLoader
	{
	public:
		[[nodiscard]]
		SharedPtr<TextureResource> Load(const StringView filepath) const
		{
			const std::string& textureName = GetNameFromFilename(filepath.data());

			Texture::Specification textureSpecs;
			textureSpecs.Filepath = filepath.data();

			auto texture = Application::GetRenderer().GetDevice().CreateTexture(textureSpecs);
			return CreateSharedPtr<TextureResource>(textureName, std::move(texture));
		}

		// TODO: Implement unloading
		// void Unload();
	};

	class TextureLibrary final
	{
	public:
		TextureLibrary() = default;
		~TextureLibrary() = default;

		void Register(const StringView filepath)
		{
			const std::string& textureName = GetNameFromFilename(filepath.data());

			if (HasTexture(textureName))
			{
				return;
			}

			m_TextureResourceMap[textureName] = m_TextureLoader.Load(filepath);
		}

		[[nodiscard]]
		bool HasTexture(const StringView name) const
		{
			return m_TextureResourceMap.contains(name.data());
		}

		SharedPtr<TextureResource> GetTexture(const StringView name)
		{
			const bool isFound = HasTexture(name);
			Debug::Assert(isFound, "Texture is not registered!");
			return m_TextureResourceMap[name.data()];
		}

		TextureLibrary(const TextureLibrary&)             = delete;
		TextureLibrary& operator=(const TextureLibrary&)  = delete;
		TextureLibrary(const TextureLibrary&&)            = delete;
		TextureLibrary& operator=(const TextureLibrary&&) = delete;

	private:
		TextureLoader m_TextureLoader;

		HashMap<String, SharedPtr<TextureResource>> m_TextureResourceMap{};
	};
}
