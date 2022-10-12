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

		bool Load(const void* buffer,
		          UINT bufferSize);

		void Update(DeviceContext& deviceContext,
		            void* buffer) const;

		bool Release() const;

	private:
		ID3D11Buffer* m_BufferData;

		friend class DeviceContext;
	};
}
