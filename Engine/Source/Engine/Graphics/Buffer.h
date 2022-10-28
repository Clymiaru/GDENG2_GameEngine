#pragma once
#include <d3d11.h>

namespace Engine
{
	class Buffer
	{
	public:
		RECT
		Buffer(Uint elementCount,
		       size_t dataTypeSize);

		virtual ~Buffer();

		virtual void Release() = 0;

		[[nodiscard]]
		Uint ElementCount() const;

		[[nodiscard]]
		size_t DataTypeSize() const;

		[[nodiscard]]
		size_t ByteSize() const;

	protected:
		ID3D11Buffer* m_Data;

		size_t m_DataTypeSize;

		size_t m_BufferSize;

		Uint m_ElementCount;
	};
}
