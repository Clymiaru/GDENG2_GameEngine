#include "SandboxLayer.h"

#include "Engine/Engine.h"

#include "Engine/Graphics/RenderObjects/Cube.h"

Sandbox::SandboxLayer::SandboxLayer() :
	Layer{"SandboxLayer"},
	m_CurrentTime{0.0f},
	m_MaxTime{5.0f}
{
}

Sandbox::SandboxLayer::~SandboxLayer() = default;

void Sandbox::SandboxLayer::OnAttach()
{
	using namespace Engine;
	ShaderLibrary::Register<VertexShader>(L"Assets/DefaultShader.hlsl",
	                                      "vsmain");

	ShaderLibrary::Register<PixelShader>(L"Assets/DefaultShader.hlsl",
	                                     "psmain");

	// Object initialization
	auto topLeftPosition = Vector3(-200.0f, 300.0f, 0.0f);
	auto tileSize        = Vector2(100.f, 100.0f);

	const auto colors = List<Color>
	{
		Color(0.68f, 0, 0.83f, 1.0f),
		Color(0.48f, 0.12f, 0.75f, 1.0f)
	};

	auto colorCycleCounter = 0;
	const auto maxXSize    = 6;
	const auto maxYSize    = 6;
	const auto spacing     = 5.0f;

	for (auto x = 0; x < maxXSize; x++)
	{
		for (auto y = 0; y < maxYSize; y++)
		{
			m_Tiles.push_back(CreateUniquePtr<Quad>(Vector3(
				                                        topLeftPosition.X() + (tileSize.X() * x) + (spacing * x),
				                                        topLeftPosition.Y() - tileSize.Y() * y - (spacing * y),
				                                        0.0f
			                                        ),
			                                        tileSize,
			                                        colors[colorCycleCounter % colors.size()],
			                                        L"DefaultShader"));
		}
		colorCycleCounter++;
	}

	m_Cube = CreateUniquePtr<Cube>(Vector3(0, 0, 0),
	                               Vector3(100, 100, 100),
	                               L"DefaultShader");

	
}

void Sandbox::SandboxLayer::OnUpdate()
{
	for (const auto& quad : m_Tiles)
	{
		quad->Update(m_CurrentTime);
	}

	m_Cube->Update(m_CurrentTime);
}

void Sandbox::SandboxLayer::OnRender()
{
	for (const auto& quad : m_Tiles)
	{
		quad->Render();
	}
	m_Cube->Render();
}

void Sandbox::SandboxLayer::OnDetach()
{
	m_Tiles.clear();
}
