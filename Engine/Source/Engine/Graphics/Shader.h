#pragma once
#include <d3d11.h>

namespace Engine
{
	class Shader
	{
	public:
		explicit Shader(ID3DBlob* blob);

		virtual ~Shader();

		[[nodiscard]]
		void* ByteCodeData() const;

		[[nodiscard]]
		size_t ByteCodeSizeData() const;

		Shader(const Shader&) = delete;

		Shader& operator=(const Shader&) = delete;

		Shader(const Shader&&) = delete;

		Shader& operator=(const Shader&&) = delete;

	protected:
		ID3DBlob* m_Blob;
	};
}
