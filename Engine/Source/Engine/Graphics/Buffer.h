﻿#pragma once
#include <d3d11.h>

namespace Engine
{
	class Renderer;

	class Buffer
	{
	public:
		Buffer(uint32_t elementCount,
		       size_t dataTypeSize,
		       Renderer* renderer);

		virtual ~Buffer();

		virtual void Release() = 0;

		[[nodiscard]]
		uint32_t ElementCount() const;

		[[nodiscard]]
		size_t DataTypeSize() const;

		[[nodiscard]]
		size_t ByteSize() const;

	protected:
		ID3D11Buffer* m_Data;

		size_t m_DataTypeSize;

		size_t m_BufferSize;

		uint32_t m_ElementCount;
	};
}
