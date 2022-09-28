#include "Triangle.h"

#include "Engine/Graphics/Core/Vertex.h"

Engine::Triangle::Triangle(Vector3Float v1,
                           Vector3Float v2,
                           Vector3Float v3,
                           Color32 color) :
	m_Renderable{nullptr},
	m_V1{v1},
	m_V2{v2},
	m_V3{v3},
	m_NextV1{v1},
	m_NextV2{v2},
	m_NextV3{v3},
	m_Color(color),
	m_NextColor{color}
{
}

Engine::Triangle::Triangle(Vector3Float v1,
                           Vector3Float v2,
                           Vector3Float v3,
                           Vector3Float nextV1,
                           Vector3Float nextV2,
                           Vector3Float nextV3,
                           Color32 color,
                           Color32 nextColor) :
	m_Renderable{nullptr},
	m_V1{v1},
	m_V2{v2},
	m_V3{v3},
	m_NextV1{nextV1},
	m_NextV2{nextV2},
	m_NextV3{nextV3},
	m_Color(color),
	m_NextColor{nextColor}
{
}

auto Engine::Triangle::Init(void* shaderByteCode,
                            UINT byteShaderSize) -> void
{
	Vertex v[] =
	{
		{
			m_V1,
			m_NextV1,
			m_Color,
			m_NextColor
		},

		{
			m_V2,
			m_NextV2,
			m_Color,
			m_NextColor
		},

		{
			m_V3,
			m_NextV3,
			m_Color,
			m_NextColor
		}
	};

	constexpr UINT listSize = ARRAYSIZE(v);

	m_Renderable = CreateRef<IRenderable>(v,
	                                      sizeof(Vertex),
	                                      listSize,
	                                      shaderByteCode,
	                                      byteShaderSize);
}

auto Engine::Triangle::GetRenderable() -> const Ref<IRenderable>&
{
	return m_Renderable;
}

Engine::Triangle::~Triangle()
{
}
