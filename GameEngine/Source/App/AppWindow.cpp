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
		m_VB{nullptr},
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

		Vertex list[] =
		{
			{{-0.5f, -0.5f, 0.0f}, {1.0f, 0.0f, 0.0f, 1.0f}},
			{{0.0f, 0.5f, 0.0f}, {0.0f, 1.0f, 0.0f, 1.0f}},
			{{0.5f, -0.5f, 0.0f}, {0.0f, 0.0f, 1.0f, 1.0f}}
		};

		m_VB                    = Engine::GraphicsEngine::GetInstance().CreateVertexBuffer();
		constexpr UINT listSize = ARRAYSIZE(list);

		void* shader_byte_code = nullptr;
		size_t size_shader     = 0;
		Engine::GraphicsEngine::GetInstance().CompileVertexShader(L"VertexShader.hlsl",
		                                                          "vsmain",
		                                                          &shader_byte_code,
		                                                          &size_shader);

		m_VertexShader = Engine::GraphicsEngine::GetInstance().CreateVertexShader(shader_byte_code, size_shader);
		m_VB->Load(list, sizeof(Vertex), listSize, shader_byte_code, static_cast<UINT>(size_shader));

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

		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexBuffer(m_VB);

		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->DrawTriangleList(
			m_VB->GetVertexListSize(), 0);

		m_SwapChain->Present(true);
	}

	auto AppWindow::OnDestroy() -> void
	{
		Window::OnDestroy();
		m_VB->Release();
		m_SwapChain->Release();
		m_VertexShader->Release();
		m_PixelShader->Release();
		Engine::GraphicsEngine::GetInstance().Release();
	}
}
