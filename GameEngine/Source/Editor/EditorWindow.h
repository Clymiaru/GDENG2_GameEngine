﻿#pragma once
#include "Engine/Window.h"
#include "Engine/Graphics/ConstantBuffer.h"
#include "Engine/Graphics/PixelShader.h"
#include "Engine/Graphics/VertexShader.h"
#include "Engine/Graphics/Primitives/Quad.h"
#include "Engine/Utils/DataStructures.h"
#include "Engine/Utils/Pointers.h"

namespace Editor
{
	class EditorWindow final : public Engine::Window
	{
	public:
		EditorWindow(const std::wstring& windowName,
		             const Engine::RectUint& windowRect);

		~EditorWindow() override;

		auto OnStart() -> void override;

		auto OnUpdate() -> void override;

		auto OnTerminate() -> void override;

	private:
		float m_Time = 0;
		Engine::List<Engine::UniquePtr<Engine::Quad>> m_Quads;
	};
}
