#include "pch.h"
#include "RenderObject.h"

#include "Engine/Graphics/ShaderLibrary.h"

namespace Engine
{
	void RenderObject::InitializeImpl(VertexData vertexData,
	                              VertexLayoutData vertexLayoutData,
	                              IndexData indexLayoutData,
	                              const std::wstring shaderName)
	{
		m_VertexData       = std::move(&vertexData);
		m_VertexLayoutData = std::move(&vertexLayoutData);
		m_IndexData        = std::move(&indexLayoutData);
		m_VertexShader     = ShaderLibrary::GetShaderRef<VertexShader>(shaderName);
		m_PixelShader      = ShaderLibrary::GetShaderRef<PixelShader>(shaderName);
		InitializeBuffers();
	}

	void RenderObject::TerminateImpl() const
	{
		m_VertexBuffer->Release();
		m_IndexBuffer->Release();
	}

	RenderObject::RenderObject() :
		m_VertexData{nullptr},
		m_VertexLayoutData{nullptr},
		m_IndexData{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr},
		m_VertexBuffer{nullptr},
		m_IndexBuffer{nullptr}
	{
	}

	RenderObject::~RenderObject() = default;

	VertexBuffer& RenderObject::GetVertexBuffer() const
	{
		return *m_VertexBuffer;
	}

	IndexBuffer& RenderObject::GetIndexBuffer() const
	{
		return *m_IndexBuffer;
	}
}
