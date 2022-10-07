#pragma once
#include <unordered_map>

#include "PixelShader.h"
#include "VertexShader.h"

#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class ShaderLibrary final
	{
	public:
		ShaderLibrary(const ShaderLibrary&) = delete;
		
		static auto GetInstance() -> ShaderLibrary&;

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto RegisterVertexShader(const std::wstring& fileName,
		                          const std::string& entryPointName) -> void;

		auto RegisterPixelShader(const std::wstring& fileName,
		                         const std::string& entryPointName) -> void;

		auto GetVertexShader(const std::wstring& filename) -> VertexShader&;

		auto GetPixelShader(const std::wstring& filename) -> PixelShader&;

		auto GetVertexShaderRef(const std::wstring& filename) -> SharedPtr<VertexShader>;

		auto GetPixelShaderRef(const std::wstring& filename) -> SharedPtr<PixelShader>;

	private:
		ShaderLibrary();

		~ShaderLibrary();

		

		std::unordered_map<std::wstring, SharedPtr<VertexShader>> m_VertexShaderMap;

		std::unordered_map<std::wstring, SharedPtr<PixelShader>> m_PixelShaderMap;
	};
}
