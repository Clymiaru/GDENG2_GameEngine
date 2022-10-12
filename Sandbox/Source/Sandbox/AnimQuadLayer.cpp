#include "pch.h"
#include "AnimQuadLayer.h"

#include "AnimatedQuad.h"

#include "Engine/Application.h"
#include "Engine/Time.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Utils/Color32.h"

Editor::AnimQuadLayer::AnimQuadLayer() :
	Layer("AnimQuadLayer")
{
}

Editor::AnimQuadLayer::~AnimQuadLayer()
{
}

void Editor::AnimQuadLayer::OnAttach()
{
	// Shader Resource Initialization
	Engine::ShaderLibrary::GetInstance().RegisterVertexAndPixelShader(L"QuadAnimShader.hlsl",
	                                                                  "vsmain",
	                                                                  "psmain");

	const auto [left, top, right, bottom] = Engine::Application::GetClientWindowRect();

	auto width  = static_cast<float>(right - left);
	auto height = static_cast<float>(bottom - top);

	auto Map2 = [](float x,
	               float in_min,
	               float in_max,
	               float out_min,
	               float out_max)-> float
	{
		return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
	};

	auto colorInt = [](int r,
	                   int g,
	                   int b) -> Engine::Color32
	{
		return Engine::Color32(static_cast<float>(r) / 255.0f,
		                       static_cast<float>(g) / 255.0f,
		                       static_cast<float>(b) / 255.0f,
		                       1.0f);
	};
#define CHALLENGE 1  

#if CHALLENGE 1
		m_AnimQuads.push_back(Engine::CreateUniquePtr<AnimatedQuad>(
			Engine::Vector3Float{-100.0f, -107.0f, 0.0f}, Engine::Vector3Float{-400.0f, -212.0f, 0.0f},
			Engine::Vector3Float{88-100.0f, 241.0f, 0.0f}, Engine::Vector3Float{-425.0f, 200.0f, 0.0f},
			Engine::Vector3Float{532-100.0f, 237.0f, 0.0f}, Engine::Vector3Float{335.0f, 200.0f, 0.0f},
			Engine::Vector3Float{487-100.0f, -237.0f, 0.0f}, Engine::Vector3Float{350.0f, -151.0f, 0.0f},
			Engine::Color32{colorInt(0, 138, 0)}, Engine::Color32{colorInt(58, 57, 0)},
			Engine::Color32{colorInt(254, 236, 0)}, Engine::Color32{colorInt(248, 239, 0)},
			Engine::Color32{colorInt(87, 101, 249)}, Engine::Color32{colorInt(255, 255, 255)},
			Engine::Color32{colorInt(177, 26, 101)}, Engine::Color32{colorInt(0, 0, 254)}));

#else
	m_AnimQuads.push_back(Engine::CreateUniquePtr<AnimatedQuad>(
		Engine::Vector3Float{-380.0f, -301.0f, 0.0f}, Engine::Vector3Float{-200.0f, -125.0f, 0.0f},
		Engine::Vector3Float{-565.0f, 145.0f, 0.0f}, Engine::Vector3Float{-200.0f, 300.0f, 0.0f},
		Engine::Vector3Float{-360.0f, -200.0f, 0.0f}, Engine::Vector3Float{100.0f, 300.0f, 0.0f},
		Engine::Vector3Float{550.0f, 10.0f, 0.0f}, Engine::Vector3Float{400.0f, -200.0f, 0.0f},
		Engine::Color32{colorInt(100, 2, 2)}, Engine::Color32{colorInt(0, 207, 0)},
		Engine::Color32{colorInt(243, 229, 0)}, Engine::Color32{colorInt(255, 237, 0)},
		Engine::Color32{colorInt(27, 228, 32)}, Engine::Color32{colorInt(11, 20, 254)},
		Engine::Color32{colorInt(0, 15, 255)}, Engine::Color32{colorInt(255, 28, 4)}));

#endif
}

void Editor::AnimQuadLayer::OnUpdate()
{
	m_Time += static_cast<float>(Engine::Time::GetDeltaTime() / 1000.0f);
	std::cout << m_Time << "\n";

#if CHALLENGE 1
	auto ratio = std::sin(m_Time);
#else
	auto ratio = std::sin(1.0f / ((m_Time * m_Time) + 1.0f));
#endif
	//std::cout << ratio << "\n";
	
	for (const auto& quad : m_AnimQuads)
	{
		quad->Update(ratio);
	}
}

void Editor::AnimQuadLayer::OnRender()
{
	Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});

	const auto [left, top, right, bottom] = Engine::Application::GetClientWindowRect();
	Engine::RenderSystem::GetDeviceContext().SetViewportSize(
		Engine::Vector2Uint{
			static_cast<Engine::Uint>(right - left),
			static_cast<Engine::Uint>(bottom - top)
		});

	for (const auto& quad : m_AnimQuads)
	{
		quad->Render();
	}

	Engine::RenderSystem::ShowFrame();
}

void Editor::AnimQuadLayer::OnDetach()
{
}
