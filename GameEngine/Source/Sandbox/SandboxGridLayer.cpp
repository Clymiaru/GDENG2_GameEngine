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

auto Sandbox::SandboxGridLayer::OnAttach() -> void
{
	// Shader Resource Initialization
	using namespace Engine;
	ShaderLibrary::GetInstance().RegisterVertexAndPixelShader(L"DefaultShader.hlsl",
	                                                          "vsmain",
	                                                          "psmain");
	// Object initialization

	Vector3Float topLeftPosition = Vector3Float{-200.0f, 300.0f, 0.0f};
	constexpr auto tileSize      = Vector2Float{100.f, 100.0f};

	const auto colors = List<Color32>
	{
		Color32{0.68f, 0, 0.83f, 1.0f},
		Color32{0.48f, 0.12f, 0.75f, 1.0f}
	};

	auto colorCycleCounter = 0;
	const auto maxXSize = 6;
	const auto maxYSize = 6;
	const auto spacing = 5.0f;
	
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

auto Sandbox::SandboxGridLayer::OnUpdate() -> void
{

	if (m_ElapsedTime < 10.0f)
	{
		m_ElapsedTime += Engine::Time::GetDeltaTime();
		m_Frames++;
		std::cout << "Elapsed Time: " << m_ElapsedTime << " Frames: " << m_Frames << "\n";
	}
	
	for (const auto& quad : m_Tiles)
	{
		quad->Update(0.0f);
	}

	//std::cout << Engine::ShaderLibrary::GetShaderRef<Engine::VertexShader>(L"DefaultShader").use_count() << "\n";
}

auto Sandbox::SandboxGridLayer::OnRender() -> void
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

auto Sandbox::SandboxGridLayer::OnDetach() -> void
{
}
