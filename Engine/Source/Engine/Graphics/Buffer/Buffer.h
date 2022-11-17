#pragma once
#include <d3d11.h>

namespace Engine
{
	class Buffer
	{
	public:
		Buffer(uint32_t elementCount,
		       size_t dataTypeSize);

		virtual ~Buffer();

		[[nodiscard]]
		uint32_t ElementCount() const;

		[[nodiscard]]
		size_t DataTypeSize() const;

		[[nodiscard]]
		size_t ByteSize() const;

		Buffer(const Buffer&) = delete;
		Buffer& operator=(const Buffer&) = delete;
		Buffer(Buffer&&) noexcept = delete;
		Buffer& operator=(Buffer&&) = delete;

	protected:
		ID3D11Buffer* m_Data;

		size_t m_DataTypeSize;
		size_t m_BufferSize;
		uint32_t m_ElementCount;
	};
}
