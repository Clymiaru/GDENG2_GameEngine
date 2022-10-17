#include "SandboxLayer.h"

#include <Utils/Random.h>

#include "../../Engine/Dependencies/ImGui/imgui.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_dx11.h"
#include "../../Engine/Dependencies/ImGui/imgui_impl_win32.h"

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

	for (size_t i = 0; i < Random::Range<int>(100, 200); i++)
	{
		m_Cubes.push_back(CreateUniquePtr<Cube>(Vector3(Random::Range<float>(-500.0f, 500.0f),
			Random::Range<float>(-300.0f, 300.0f),
			Random::Range<float>(-0.0f, 0.0f)),
			Vector3(Random::Range<float>(100, 200),
				Random::Range<float>(100, 200),
				Random::Range<float>(100, 200)),
			L"DefaultShader"));
	}
	Debug::Log("Cubes: {0}", m_Cubes.size());

}

void Sandbox::SandboxLayer::OnUpdate()
{
	for (const auto& quad : m_Tiles)
	{
		quad->Update(m_CurrentTime);
	}

	for (const auto& cube : m_Cubes)
	{
		cube->Update(m_CurrentTime);
	}
}

void Sandbox::SandboxLayer::OnRender()
{
	for (const auto& quad : m_Tiles)
	{
		quad->Render();
	}
	for (const auto& cube : m_Cubes)
	{
		cube->Render();
	}
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	static bool showDemoWindow = true;

	if (showDemoWindow)
	{
		ImGui::ShowDemoWindow(&showDemoWindow);
	}
	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	ImGui::EndFrame();
}

void Sandbox::SandboxLayer::OnDetach()
{
	m_Tiles.clear();
}
