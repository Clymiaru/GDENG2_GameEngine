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
		auto GetCount() const -> Uint;

		[[nodiscard]]
		auto GetSize() const -> Uint;

		[[nodiscard]]
		auto Load(const Uint* indexList,
		          Uint indexListCount) -> bool;

	private:
		ID3D11Buffer* m_Data;

		Uint m_DataCount;

		friend class DeviceContext;
	};
}
