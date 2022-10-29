#pragma once
#include <d3dcommon.h>

#include "Engine/Core/Core.h"

namespace Engine
{
	template <typename T>
	class Shader
	{
	public:
		explicit Shader(ID3DBlob* blob);

		virtual ~Shader();

		Shader(const Shader&) = delete;

		auto operator=(const Shader&) -> Shader& = delete;

		Shader(const Shader&&) = delete;

		auto operator=(const Shader&&) -> Shader& = delete;

		[[nodiscard]]
		void* GetByteCodeData() const;

		[[nodiscard]]
		size_t GetByteCodeSizeData() const;

		[[nodiscard]]
		T& GetData();

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
	void* Shader<T>::GetByteCodeData() const
	{
		return m_Blob->GetBufferPointer();
	}

	template <typename T>
	size_t Shader<T>::GetByteCodeSizeData() const
	{
		return m_Blob->GetBufferSize();
	}

	template <typename T>
	T& Shader<T>::GetData()
	{
		return *m_Data;
	}

	//---------- USING DECLARATIONS
	template <class ShaderType>
	using ShaderRef = SharedPtr<ShaderType>; 
	
}
