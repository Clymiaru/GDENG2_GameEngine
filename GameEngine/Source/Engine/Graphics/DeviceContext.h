#pragma once

#include <d3d11.h>
#include "Engine/Utils/Color32.h"

namespace Engine
{
	class SwapChain;
	class VertexBuffer;

	class DeviceContext
	{
	public:
		DeviceContext(ID3D11DeviceContext* deviceContext);
		~DeviceContext();

		bool Release();

		void ClearRenderTarget(SwapChain* swapChain, Color32 color);

		void SetVertexBuffer(VertexBuffer* vertexBuffer);

		void DrawTriangleList(UINT vertexCount, UINT startVertexIndex);

		void SetViewportSize(UINT width, UINT height);

	private:
		ID3D11DeviceContext* m_DeviceContext;

	};
}