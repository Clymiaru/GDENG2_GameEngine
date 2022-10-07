#pragma once
#include <d3d11.h>

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

		auto Update(DeviceContext& deviceContext,
		            void* buffer) -> void;

		auto Release() -> bool;

	private:
		ID3D11Buffer* m_BufferData;

		friend class DeviceContext;
	};
}
