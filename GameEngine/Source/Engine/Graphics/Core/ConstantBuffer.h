#pragma once
#include <d3d11.h>
#include "Engine/Utils/Pointers.h"

namespace Engine
{
	class DeviceContext;

	class ConstantBuffer final
	{
	public:
		ConstantBuffer();

		~ConstantBuffer();

		auto Load(const void* buffer,
		          UINT bufferSize) -> bool;

		auto Update(const Scope<DeviceContext>& deviceContext,
		            void* buffer) -> void;

		auto Release() const -> bool;

	private:
		ID3D11Buffer* m_BufferData;

		friend class DeviceContext;
	};
}
