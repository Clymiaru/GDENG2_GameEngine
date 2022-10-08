#include "pch.h"
#include "EditorWindow.h"

#include "Windows.h"

#include "Engine/Time.h"
#include "Engine/Graphics/DeviceContext.h"
#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/ShaderLibrary.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

#include "Engine/Graphics/RenderObjects/Quad.h"

namespace Editor
{
	EditorWindow::EditorWindow(const std::wstring& windowName,
	                           const Engine::RectUint& windowRect) :
		Window()
	{
	}

	EditorWindow::~EditorWindow() = default;

	auto EditorWindow::OnStart() -> void
	{
		std::cout << "Editor Window Start\n";

		// Shader Resource Initialization
		Engine::ShaderLibrary::GetInstance().RegisterVertexShader(L"SinTimeAnimShader.hlsl",
		                                                          "vsmain");

		Engine::ShaderLibrary::GetInstance().RegisterPixelShader(L"SinTimeAnimShader.hlsl",
		                                                         "psmain");

		Engine::ShaderLibrary::GetInstance().RegisterVertexShader(L"QuadAnimShader.hlsl",
		                                                          "vsmain");

		Engine::ShaderLibrary::GetInstance().RegisterPixelShader(L"QuadAnimShader.hlsl",
		                                                         "psmain");

		// Object initialization
		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{-300.0f, 100.0f, 0.0f},
		                                                        Engine::Vector2Float{400.f, 400.0f},
		                                                        Engine::Color32{0.68f, 0, 0.83f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{200.0f, 125.0f, 0.0f},
		                                                        Engine::Vector2Float{225.0f, 425.0f},
		                                                        Engine::Color32{0.27f, 0.51f, 0.41f, 1.0f}));

		m_Quads.push_back(Engine::CreateUniquePtr<Engine::Quad>(Engine::Vector3Float{200.0f, -225.0f, 0.0f},
		                                                        Engine::Vector2Float{500.0f, 225.0f},
		                                                        Engine::Color32{0.21f, 0.21f, 0.78f, 1.0f}));

		const auto [left, top, right, bottom] = GetClientWindowRect();

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
#define CHALLENGE_1
#undef CHALLENGE_1

#ifdef CHALLENGE_1
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

	auto EditorWindow::OnUpdate() -> void
	{
		m_Time += static_cast<float>(Engine::Time::GetDeltaTime()) / 10.0f; 

#ifdef CHALLENGE_1
		auto ratio = std::sin(m_Time * m_Time);
#else
		auto ratio = std::sin(100.0f / ((m_Time * m_Time) + 1.0f));
#endif
		std::cout << ratio << "\n";
		for (const auto& quad : m_AnimQuads)
		{
			quad->Update(ratio);
		}
	}

	auto EditorWindow::OnRender() -> void
	{
		Engine::RenderSystem::GetInstance().Clear({0.5f, 0.5f, 1.0f, 1.0f});

		const auto [left, top, right, bottom] = GetClientWindowRect();
		Engine::RenderSystem::GetInstance().GetDeviceContext().SetViewportSize(
			Engine::Vector2Uint{
				static_cast<Engine::Uint>(right - left),
				static_cast<Engine::Uint>(bottom - top)
			});

		for (const auto& quad : m_AnimQuads)
		{
			quad->Render();
			Engine::RenderSystem::GetInstance().Draw(quad->GetVertexBuffer(),
			                                         quad->GetIndexBuffer());
		}

		Engine::RenderSystem::GetInstance().ShowFrame();
	}

	auto EditorWindow::OnTerminate() -> void
	{
	}
}
