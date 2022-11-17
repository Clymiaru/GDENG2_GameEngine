#pragma once
#include <filesystem>
namespace Engine
{
	class TextFileResource
	{
		
	};
	
	class TextFileLibrary
	{
	public:
		void Load(StringView filepath);

		SharedPtr<TextFileResource> Get(StringView resourceName);

		void Unload(StringView resourceName);

	private:
		HashMap<String, TextFileResource> m_TextFileResourceMap;
	};
}

