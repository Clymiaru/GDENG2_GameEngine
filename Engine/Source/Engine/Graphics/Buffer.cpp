#include "pch.h"
#include "Buffer.h"

namespace Engine
{
	Buffer::Buffer(const uint32_t elementCount,
	               const size_t dataTypeSize) :
		m_Data{nullptr},
		m_DataTypeSize{dataTypeSize},
		m_BufferSize{elementCount * dataTypeSize},
		m_ElementCount{elementCount}
	{
	}

	Buffer::Buffer(ID3D11Buffer* bufferData,
	               const uint32_t elementCount,
	               const size_t dataTypeSize) :
		m_Data{bufferData},
		m_DataTypeSize{dataTypeSize},
		m_BufferSize{elementCount * dataTypeSize},
		m_ElementCount{elementCount}
	{
	}

	Buffer::~Buffer()
	{
	}

	uint32_t Buffer::ElementCount() const
	{
		return m_ElementCount;
	}

	size_t Buffer::DataTypeSize() const
	{
		return m_DataTypeSize;
	}

	size_t Buffer::ByteSize() const
	{
		return m_BufferSize;
	}
}
