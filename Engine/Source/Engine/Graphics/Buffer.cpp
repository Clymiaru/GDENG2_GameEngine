#include "pch.h"
#include "Buffer.h"

Engine::Buffer::Buffer(const uint32_t elementCount,
                       const size_t dataTypeSize,
                       Renderer* renderer) :
	m_Data{nullptr},
	m_DataTypeSize{dataTypeSize},
	m_BufferSize{elementCount * dataTypeSize},
	m_ElementCount{elementCount}
{
}

Engine::Buffer::~Buffer()
{
}

uint32_t Engine::Buffer::ElementCount() const
{
	return m_ElementCount;
}

size_t Engine::Buffer::DataTypeSize() const
{
	return m_DataTypeSize;
}

size_t Engine::Buffer::ByteSize() const
{
	return m_BufferSize;
}
