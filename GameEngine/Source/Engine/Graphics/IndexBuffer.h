#pragma once
#include <d3d11.h>

#include "Engine/Utils/Math.h"

namespace Engine
{
	class DeviceContext;

	class IndexBuffer
	{
	public:
		IndexBuffer();

		~IndexBuffer();

		[[nodiscard]]
		Uint GetCount() const;

		[[nodiscard]]
		Uint GetSize() const;

		[[nodiscard]]
		bool Load(const Uint* indexList,
		          Uint indexListCount);

	private:
		ID3D11Buffer* m_Data;

		Uint m_DataCount;

		friend class DeviceContext;
	};
}
