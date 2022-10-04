#pragma once
#include <d3dcommon.h>

namespace Engine
{
	template <typename T>
	class Shader
	{
	public:
		explicit Shader(ID3DBlob* blob);

		virtual ~Shader();

		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;
		Shader(const Shader&&) = delete;
		Shader& operator=(const Shader&&) = delete;
		
		[[nodiscard]]
		auto GetByteCodeData() const -> void*;

		[[nodiscard]]
		auto GetByteCodeSizeData() const -> size_t;

		[[nodiscard]]
		auto GetData() -> T*;

	protected:
		T* m_Data;
		ID3DBlob* m_Blob;
	};

	template <typename T>
	Shader<T>::Shader(ID3DBlob* blob) :
		m_Data{nullptr},
		m_Blob{blob}
	{
	}

	template <typename T>
	Shader<T>::~Shader()
	{
	}

	template <typename T>
	auto Shader<T>::GetByteCodeData() const -> void*
	{
		return m_Blob->GetBufferPointer();
	}

	template <typename T>
	auto Shader<T>::GetByteCodeSizeData() const -> size_t
	{
		return m_Blob->GetBufferSize();
	}

	template <typename T>
	auto Shader<T>::GetData() -> T*
	{
		return m_Data;
	}
}
