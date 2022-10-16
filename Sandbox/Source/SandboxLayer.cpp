﻿#include "SandboxLayer.h"

#include <Engine/Core/Application.h>
#include <Engine/Core/Debug.h>
#include <Engine/Core/Math.h>
#include <Engine/Core/Window.h>
#include <Engine/Graphics/DeviceContext.h>
#include <Engine/Graphics/RenderSystem.h>
#include <Engine/Graphics/ShaderLibrary.h>

#include <Engine/Graphics/RenderObjects/Quad.h>

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
	auto topLeftPosition    = Vector3(-200.0f, 300.0f, 0.0f);
	auto tileSize = Vector2(100.f, 100.0f);

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
}

void Sandbox::SandboxLayer::OnUpdate()
{
	m_CurrentTime += static_cast<float>(Engine::Application::DeltaTime());
	//Engine::Debug::Log("Time {0}", m_CurrentTime);

	for (const auto& quad : m_Tiles)
	{
		quad->Update(m_CurrentTime);
	}
}

void Sandbox::SandboxLayer::OnRender()
{
	// if (m_CurrentTime > m_MaxTime)
	// {
	// 	m_CurrentTime = 0.0f;
	// 	Engine::Debug::Log("Time Render {0}", m_CurrentTime);
	// }

	Engine::RenderSystem::Clear({0.0f, 0.5f, 1.0f, 1.0f});

	// Engine::Vector2 size = Engine::Application::WindowRef().GetSize();
	// Engine::RenderSystem::GetDeviceContext().SetViewportSize(size);
	
	for (const auto& quad : m_Tiles)
	{
		quad->Render();
	}

	Engine::RenderSystem::ShowFrame();
}

void Sandbox::SandboxLayer::OnDetach()
{
	m_Tiles.clear();
}
