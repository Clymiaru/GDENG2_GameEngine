#include "pch.h"
#include "Buffer.h"

Engine::Buffer::Buffer(const Uint elementCount,
                       const size_t dataTypeSize) :
	m_Data{nullptr},
	m_DataTypeSize{dataTypeSize},
	m_BufferSize{elementCount * dataTypeSize},
	m_ElementCount{elementCount}
{
}

Engine::Buffer::~Buffer()
{
}

Engine::Uint Engine::Buffer::ElementCount() const
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
