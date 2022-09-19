#include "AppWindow.h"
#include "Engine/Graphics/GraphicsEngine.h"


namespace App
{
	struct Vec3
	{
		float x, y, z;
	};

	struct Vertex
	{
		Vec3 position;
	};

	AppWindow::AppWindow(const std::wstring& windowName,
						 Engine::Vector2Int windowSize) : 
		Engine::Window(windowName, windowSize)
	{
	}

	AppWindow::~AppWindow()
	{
	}

	void AppWindow::OnCreate()
	{
		Window::OnCreate();
		RECT rc = GetClientWindowRect();
		Engine::GraphicsEngine::GetInstance().Init(m_Handle, { rc.right - rc.left, rc.bottom - rc.top });

		Vertex list[] =
		{
			{-0.5f, -0.5f, 0.0f},
			{0.0f, 0.5f, 0.0f },
			{0.5f, -0.5f, 0.0f}
		};

		m_VB = Engine::GraphicsEngine::GetInstance().CreateVertexBuffer();

		UINT listSize = ARRAYSIZE(list);

		Engine::GraphicsEngine::GetInstance().Cre();

		void* shader_byte_code = nullptr;
		UINT size_shader = 0;
		Engine::GraphicsEngine::GetInstance()->getShaderBufferAndSize(&shader_byte_code, &size_shader);

		m_VB->load(list, sizeof(Vertex), listSize, shader_byte_code, size_shader);

	}

	void AppWindow::OnUpdate()
	{
		Window::OnUpdate();

		Engine::GraphicsEngine::GetInstance().Clear({ 1.0f, 0.0f, 1.0f, 1.0f });
		RECT rc = GetClientWindowRect();
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetViewportSize(rc.right - rc.left, rc.bottom - rc.top);

		Engine::GraphicsEngine::GetInstance().SetShaders();
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->SetVertexBuffer(m_VB);
		Engine::GraphicsEngine::GetInstance().GetImmediateDeviceContext()->DrawTriangleList(m_VB->GetSizeVertexList(), 0);
		Engine::GraphicsEngine::GetInstance().Draw();
	}

	void AppWindow::OnDestroy()
	{
		Window::OnDestroy();
		Engine::GraphicsEngine::GetInstance().Release();
	}
}