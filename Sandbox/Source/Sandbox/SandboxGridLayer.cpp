#include "pch.h"
#include "SandboxGridLayer.h"

#include "Engine/Application.h"
#include "Engine/Time.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Graphics/RenderObjects/Quad.h"
#include "Engine/Utils/Color32.h"
#include "Engine/Utils/Math.h"

Sandbox::SandboxGridLayer::SandboxGridLayer() :
	Layer("SandboxGridLayer")
{
}

Sandbox::SandboxGridLayer::~SandboxGridLayer()
{
}

void Sandbox::SandboxGridLayer::OnAttach()
{
	// Shader Resource Initialization
	using namespace Engine;
	ShaderLibrary::Register<VertexShader>(L"Assets/DefaultShader.hlsl",
	                                      "vsmain");

	ShaderLibrary::Register<PixelShader>(L"Assets/DefaultShader.hlsl",
	                                     "psmain");
	
	// Object initialization
	auto topLeftPosition    = Vector3Float{-200.0f, 300.0f, 0.0f};
	constexpr auto tileSize = Vector2Float{100.f, 100.0f};

	const auto colors = List<Color32>
	{
		Color32{0.68f, 0, 0.83f, 1.0f},
		Color32{0.48f, 0.12f, 0.75f, 1.0f}
	};

	auto colorCycleCounter = 0;
	const auto maxXSize    = 6;
	const auto maxYSize    = 6;
	const auto spacing     = 5.0f;

	for (auto x = 0; x < maxXSize; x++)
	{
		for (auto y = 0; y < maxYSize; y++)
		{
			m_Tiles.push_back(CreateUniquePtr<Quad>(Vector3Float{
				                                        topLeftPosition.X + (tileSize.X * x) + (spacing * x),
				                                        topLeftPosition.Y - tileSize.Y * y - (spacing * y),
				                                        0.0f
			                                        },
			                                        tileSize,
			                                        colors[colorCycleCounter % colors.size()],
			                                        L"DefaultShader"));
		}
		colorCycleCounter++;
	}
}

void Sandbox::SandboxGridLayer::OnUpdate()
{
	for (const auto& quad : m_Tiles)
	{
		quad->Update(0.0f);
	}
	std::cout << Engine::Time::GetDeltaTime() << "\n";
}

void Sandbox::SandboxGridLayer::OnRender()
{
	Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});

	const auto [left, top, right, bottom] = Engine::Application::GetClientWindowRect();
	Engine::RenderSystem::GetDeviceContext().SetViewportSize(
		Engine::Vector2Uint{
			static_cast<Engine::Uint>(right - left),
			static_cast<Engine::Uint>(bottom - top)
		});

	for (const auto& quad : m_Tiles)
	{
		quad->Render();
	}

	Engine::RenderSystem::ShowFrame();
}

void Sandbox::SandboxGridLayer::OnDetach()
{
	m_Tiles.clear();
}
