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
		static auto GetInstance() -> ShaderLibrary&;

		auto Initialize() -> void;

		auto Terminate() -> void;

		auto RegisterVertexShader(const std::wstring& fileName,
		                          const std::string& entryPointName) -> void;

		auto RegisterPixelShader(const std::wstring& fileName,
		                         const std::string& entryPointName) -> void;

		auto GetVertexShader(const std::wstring& filename) -> VertexShader&;

		auto GetPixelShader(const std::wstring& filename) -> PixelShader&;

	private:
		ShaderLibrary();

		~ShaderLibrary();

		ShaderLibrary(const ShaderLibrary&);

		ShaderLibrary(const ShaderLibrary&&) noexcept;

		std::unordered_map<std::wstring, SharedPtr<VertexShader>> m_VertexShaderMap;

		std::unordered_map<std::wstring, SharedPtr<PixelShader>> m_PixelShaderMap;

		ID3D11VertexShader* m_VertexShader = nullptr;

		ID3D11PixelShader* m_PixelShader = nullptr;
	};
}
