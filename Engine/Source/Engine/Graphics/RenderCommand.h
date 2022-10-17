#pragma once
#include "VertexShader.h"
#include "PixelShader.h"
#include "ConstantBuffer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"


namespace Engine
{
	//TODO: RenderCommands and RenderData for RenderSystem ay
	struct RenderCommand
	{
		enum class Command
		{
			DrawIndexed
		};

		virtual void Perform() = 0;
	};

	struct DrawIndexedCommand : public RenderCommand
	{
		VertexShader& VertexShader;
		PixelShader& PixelShader;
		ConstantBuffer& ConstantBuffer;
		void* UpdatedConstantBuffer;
		VertexBuffer& VertexBuffer;
		IndexBuffer& IndexBuffer;
		D3D11_PRIMITIVE_TOPOLOGY Topology;

		void Perform() override;
	};

	struct RenderData
	{
		
	};
}