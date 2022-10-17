#include "pch.h"
#include "Primitive.h"

#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	void Primitive::Initialize(VertexData vertexData,
	                               VertexLayoutData vertexLayoutData,
	                               IndexData indexLayoutData,
	                               const WString shaderName)
	{
		m_VertexData       = std::move(&vertexData);
		m_VertexLayoutData = std::move(&vertexLayoutData);
		m_IndexData        = std::move(&indexLayoutData);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);
	}

	void Primitive::InitializeBuffers(size_t vertexSize,
									  void* constantBufferData,
									  size_t constantBufferDataSize)
	{
		m_VertexBuffer = CreateUniquePtr<VertexBuffer>(m_VertexData->VertexList,
													   vertexSize,
													   m_VertexData->VertexListCount,
													   m_VertexShader->GetByteCodeData(),
													   static_cast<Uint>(m_VertexShader->GetByteCodeSizeData()),
													   m_VertexLayoutData->VertexLayout,
													   m_VertexLayoutData->VertexLayoutCount);

		m_IndexBuffer = CreateUniquePtr<IndexBuffer>(m_IndexData->IndexList,
													 m_IndexData->IndexListCount);

		m_ConstantBuffer = CreateUniquePtr<ConstantBuffer>(constantBufferData, constantBufferDataSize);
	}

	void Primitive::Draw(void* newConstantData)
	{
		// Create geometry
		// Create Vertex buffer
		// Create index buffer
		// Create Constant Buffer
		//==========

		// Clear Render Target and Depth and Stencil Views

		//===========
		// Set Shaders that will be used
		RenderSystem::SetShader<VertexShader>(*m_VertexShader);
		RenderSystem::SetShader<PixelShader>(*m_PixelShader);

		// Update and Set Constant Buffers that will be used by the shaders
		RenderSystem::GetDeviceContext().UpdateConstantBuffer(*m_ConstantBuffer, newConstantData);

		RenderSystem::SetConstantBuffer<VertexShader>(*m_ConstantBuffer);
		RenderSystem::SetConstantBuffer<PixelShader>(*m_ConstantBuffer);

		// IDEA
		// RenderData data = {};
		// RenderSystem::Draw(data);

		// Set Vertex and Index Buffer

		// Set Topology of the rendering

		// DrawIndexed
		RenderSystem::Draw(*m_VertexBuffer, *m_IndexBuffer);
	}

	void Primitive::Terminate() const
	{
		m_VertexBuffer->Release();
		m_IndexBuffer->Release();
	}

	Primitive::Primitive() :
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr},
		m_ConstantBuffer{nullptr}
	{
	}

	Primitive::~Primitive() = default;

	VertexBuffer& Primitive::GetVertexBuffer() const
	{
		return *m_VertexBuffer;
	}

	IndexBuffer& Primitive::GetIndexBuffer() const
	{
		return *m_IndexBuffer;
	}
}
