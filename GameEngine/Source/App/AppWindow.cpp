#include "pch.h"

#include "AppWindow.h"
#include "Windows.h"

#include "Engine/Graphics/RenderSystem.h"
#include "Engine/Graphics/Core/ConstantBuffer.h"
#include "Engine/Graphics/Core/DeviceContext.h"
#include "Engine/Graphics/Core/GraphicsEngine.h"
#include "Engine/Graphics/Core/Vertex.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

namespace App
{
	__declspec(align(16))
	struct Constant
	{
		float Angle;
	};

	AppWindow::AppWindow(const std::wstring& windowName,
	                     const Engine::Vector2Int windowSize) :
		Window(windowName, windowSize),
		m_ConstantBuffer{nullptr},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr}
	{
	}

	AppWindow::~AppWindow() = default;

	auto AppWindow::OnCreate() -> void
	{
		Window::OnCreate();

		RECT rc = GetClientWindowRect();
		Engine::GraphicsEngine::GetInstance().Init();
		Engine::RenderSystem::GetInstance().Initialize(m_Handle, {rc.right - rc.left, rc.bottom - rc.top});
		Vertex rainbowRectangle[] =
		{
			{
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 1.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f}
			},

			{
				Engine::Vector3Float{-0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f}
			},

			{
				Engine::Vector3Float{0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f}
			},

			{
				Engine::Vector3Float{0.30f - 0.60f, 0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, 0.30f + 0.55f, 0.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
			},

			{
				Engine::Vector3Float{0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{0.30f, -0.30f - 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 0.0f, 1.0f},
				Engine::Color32{0.0f, 0.0f, 1.0f, 1.0f},
			},

			{
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Vector3Float{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f},
				Engine::Color32{1.0f, 0.0f, 1.0f, 1.0f},
				Engine::Color32{0.0f, 0.5f, 1.0f, 1.0f},
			}
		};

		constexpr UINT rainbowRectangleListSize = ARRAYSIZE(rainbowRectangle);
		// constexpr UINT rainbowTriangleListSize = ARRAYSIZE(rainbowTriangle);
		// constexpr UINT greenRectangleListSize = ARRAYSIZE(greenRectangle);

		void* shaderByteCode      = nullptr;
		size_t shaderByteCodeSize = 0;
		Engine::GraphicsEngine::GetInstance().CompileVertexShader(L"VertexShader.hlsl",
		                                                          "vsmain",
		                                                          &shaderByteCode,
		                                                          &shaderByteCodeSize);

		m_VertexShader = Engine::GraphicsEngine::GetInstance().CreateVertexShader(shaderByteCode, shaderByteCodeSize);

		// m_Triangle = Engine::CreateScope<Engine::Triangle>(Engine::Vector3Float{-0.30f - 0.60f, -0.30f - 0.55f, 0.0f},
		//                                                    Engine::Vector3Float{-0.30f - 0.60f, 0.30f - 0.55f, 0.0f},
		//                                                    Engine::Vector3Float{0.30f - 0.60f, 0.30f - 0.55f, 0.0f},
		//                                                    Engine::Vector3Float{-0.30f - 0.60f, -0.30f - 0.55f, 0.0f},
		//                                                    Engine::Vector3Float{-0.30f, 0.30f - 0.55f, 0.0f},
		//                                                    Engine::Vector3Float{0.30f, 0.30f - 0.55f, 0.0f},
		//                                                    Engine::Color32{1.0f, 1.0f, 0.0f, 1.0f},
		//                                                    Engine::Color32{0.0f, 1.0f, 1.0f, 1.0f});
		//
		// m_Triangle2 = Engine::CreateScope<Engine::Triangle>(Engine::Vector3Float{0.30f - 0.60f, 0.30f - 0.55f, 0.0f},
		//                                                     Engine::Vector3Float{0.30f - 0.60f, -0.30f - 0.55f, 0.0f},
		//                                                     Engine::Vector3Float{-0.30f - 0.60f, -0.30f - 0.55f, 0.0f},
		//                                                     Engine::Vector3Float{0.30f, 0.30f - 0.55f, 0.0f},
		//                                                     Engine::Vector3Float{0.30f - 0.60f, -0.30f - 0.55f, 0.0f},
		//                                                     Engine::Vector3Float{0.30f - 0.60f, 0.30f - 0.55f, 0.0f},
		//                                                     Engine::Color32{0.0f, 1.0f, 1.0f, 1.0f},
		//                                                     Engine::Color32{1.0f, 1.0f, 0.0f, 1.0f});
		//
		// m_Triangle->Init(shaderByteCode, shaderByteCodeSize);
		// m_Triangle2->Init(shaderByteCode, shaderByteCodeSize);

		Engine::RenderSystem::GetInstance().RegisterObject(rainbowRectangle,
		                                                   sizeof(Vertex),
		                                                   rainbowRectangleListSize,
		                                                   shaderByteCode,
		                                                   shaderByteCodeSize);
		// Engine::RenderSystem::RegisterObject(m_Triangle->GetRenderable());
		// Engine::RenderSystem::RegisterObject(m_Triangle2->GetRenderable());

		Engine::GraphicsEngine::GetInstance().ReleaseCompiledShader();

		Engine::GraphicsEngine::GetInstance().CompilePixelShader(L"PixelShader.hlsl",
		                                                         "psmain",
		                                                         &shaderByteCode,
		                                                         &shaderByteCodeSize);

		m_PixelShader = Engine::GraphicsEngine::GetInstance().CreatePixelShader(shaderByteCode, shaderByteCodeSize);
		Engine::GraphicsEngine::GetInstance().ReleaseCompiledShader();

		Constant constant = {};
		constant.Angle    = 0;
		m_ConstantBuffer  = Engine::GraphicsEngine::GetInstance().CreateConstantBuffer();
		m_ConstantBuffer->Load(&constant, sizeof(Constant));
	}

	auto AppWindow::OnUpdate() -> void
	{
		Window::OnUpdate();
		Engine::RenderSystem::Clear({0.5f, 0.5f, 1.0f, 1.0f});

		const RECT rc = GetClientWindowRect();
		Engine::GraphicsEngine::SetViewportSize(rc.right - rc.left,
		                                        rc.bottom - rc.top);

		unsigned long newTime = 0;
		if (m_OldTime)
			newTime = GetTickCount() - m_OldTime;
		m_DeltaTime = static_cast<float>(newTime) / 1000.0f;
		m_OldTime   = GetTickCount();

		m_Angle += 1.57f * m_DeltaTime;
		Constant constant = {};
		constant.Angle    = m_Angle;

		m_ConstantBuffer->Update(Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext(), &constant);

		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetConstantBuffer(
			m_VertexShader, m_ConstantBuffer);
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetConstantBuffer(
			m_PixelShader, m_ConstantBuffer);

		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexShader(m_VertexShader);
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetPixelShader(m_PixelShader);

		Engine::RenderSystem::Draw();
	}

	auto AppWindow::OnDestroy() -> void
	{
		Window::OnDestroy();
		m_ConstantBuffer->Release();
		Engine::GraphicsEngine::GetInstance().Release();
	}
}
