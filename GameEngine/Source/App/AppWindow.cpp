#include "AppWindow.h"
#include "Engine/Graphics/GraphicsEngine.h"
#include "Engine/Graphics/SwapChain.h"
#include "Engine/Utils/Debug.h"
#include "Engine/Utils/Math.h"

namespace App
{
	struct Vertex
	{
		Engine::Vector3Float Position;
		Engine::Color32 Color;
	};

	AppWindow::AppWindow(const std::wstring& windowName,
	                     const Engine::Vector2Int windowSize) :
		Window(windowName, windowSize),
		m_SwapChain{nullptr},
		m_VertexBuffers{},
		m_VertexShader{nullptr},
		m_PixelShader{nullptr}
	{
	}

	AppWindow::~AppWindow()
	{
	}

	auto AppWindow::OnCreate() -> void
	{
		Window::OnCreate();
		Engine::GraphicsEngine::GetInstance().Init();
		m_SwapChain = Engine::GraphicsEngine::GetInstance().CreateSwapChain();

		RECT rc = GetClientWindowRect();
		m_SwapChain->Init(m_Handle, {rc.right - rc.left, rc.bottom - rc.top});

		Vertex rainbowRectangle[] =
		{
			{{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{-0.30f - 0.60f, 0.30f + 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.30f - 0.60f, 0.30f + 0.55f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
			{{0.30f - 0.60f, 0.30f + 0.55f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}},
			{{0.30f - 0.60f, -0.30f + 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.30f - 0.60f, -0.30f + 0.55f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}}
		};

		Vertex rainbowTriangle[] =
		{
			{{-0.30f - 0.1f, -0.30f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{0.0f - 0.1f, 0.30f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.30f - 0.1f, -0.30f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
		};

		Vertex greenRectangle[] =
		{
			{{-0.30f + 0.60f, -0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.30f + 0.60f, 0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.30f + 0.60f, 0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.30f + 0.60f, 0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.30f + 0.60f, -0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{-0.30f + 0.60f, -0.30f - 0.55f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}}
		};

		for (int i = 0; i < 3; i++)
		{
			m_VertexBuffers.push_back(Engine::GraphicsEngine::GetInstance().CreateVertexBuffer());
		}
		constexpr UINT rainbowRectangleListSize = ARRAYSIZE(rainbowRectangle);
		constexpr UINT rainbowTriangleListSize = ARRAYSIZE(rainbowTriangle);
		constexpr UINT greenRectangleListSize = ARRAYSIZE(greenRectangle);

		void* shader_byte_code = nullptr;
		size_t size_shader     = 0;
		Engine::GraphicsEngine::GetInstance().CompileVertexShader(L"VertexShader.hlsl",
		                                                          "vsmain",
		                                                          &shader_byte_code,
		                                                          &size_shader);

		m_VertexShader = Engine::GraphicsEngine::GetInstance().CreateVertexShader(shader_byte_code, size_shader);

		// BASIC RENDERER OUTPUTS
		m_VertexBuffers[2]->Load(rainbowRectangle, sizeof(Vertex), rainbowRectangleListSize, shader_byte_code, static_cast<UINT>(size_shader));
		m_VertexBuffers[1]->Load(rainbowTriangle, sizeof(Vertex), rainbowTriangleListSize, shader_byte_code, static_cast<UINT>(size_shader));
		m_VertexBuffers[0]->Load(greenRectangle, sizeof(Vertex), greenRectangleListSize, shader_byte_code, static_cast<UINT>(size_shader));

		Engine::GraphicsEngine::GetInstance().ReleaseCompiledShader();

		Engine::GraphicsEngine::GetInstance().CompilePixelShader(L"PixelShader.hlsl",
																  "main",
																  &shader_byte_code,
																  &size_shader);

		m_PixelShader = Engine::GraphicsEngine::GetInstance().CreatePixelShader(shader_byte_code, size_shader);

		Engine::GraphicsEngine::GetInstance().ReleaseCompiledShader();
	}

	auto AppWindow::OnUpdate() -> void
	{
		Window::OnUpdate();
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->ClearRenderTarget(
			m_SwapChain, {0.5f, 0.5f, 1.0f, 1.0f});

		RECT rc = GetClientWindowRect();
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left,
		                                                                                   rc.bottom - rc.top);

		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexShader(m_VertexShader);
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetPixelShader(m_PixelShader);


		for (const auto& vb : m_VertexBuffers)
		{
			Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexBuffer(vb);
			Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->DrawTriangleList(
				vb->GetVertexListSize(), 0);
		}

		m_SwapChain->Present(true);
	}

	auto AppWindow::OnDestroy() -> void
	{
		Window::OnDestroy();
		for (const auto& vb : m_VertexBuffers)
		{
			vb->Release();
		}
		m_SwapChain->Release();
		Engine::GraphicsEngine::GetInstance().Release();
	}
}
