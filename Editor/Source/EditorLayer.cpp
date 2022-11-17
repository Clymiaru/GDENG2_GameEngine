#include "EditorLayer.h"

#include <Engine/Core/Debug.h>

// #include <Engine/Core/Application.h>
// #include <Engine/ECS/Component/RenderComponent.h>
// #include <Engine/Graphics/Renderer.h>
// #include <Engine/Resource/ShaderLibrary.h>
// #include <Engine/Input/Input.h>
//
// #include <Engine/ECS/Component/TransformComponent.h>
//
// #include <Engine/Graphics/RenderQuad.h>
//
// #include <Engine/Graphics/PostProcessEffect/PostProcessHandler.h>
// #include <Engine/Graphics/Primitives/Primitive.h>
// #include <Engine/UI/UISystem.h>
//
// #include <Utils/Random.h>
//
// #include "../../Engine/Dependencies/ImGui/imgui.h"
//
// #include "Screen/PlaceholderHUD.h"
// #include "Screen/EntityPropertiesPanel.h"
// #include "Screen/PostProcessingPanel.h"
// #include "Screen/WorldOutlinerPanel.h"

namespace Editor
{
	EditorLayer::EditorLayer() :
		Layer{"EditorLayer"}
	{
	}

	EditorLayer::~EditorLayer() = default;

	void EditorLayer::OnAttach()
	{
		using namespace Engine;
		Debug::Log("Editor Layer Start");
	}

	void EditorLayer::OnPollInput()
	{
	}

	void EditorLayer::OnUpdate()
	{
		using namespace Engine;
	}
	
	void EditorLayer::OnRender()
	{
		using namespace Engine;
	}

	void EditorLayer::OnDetach()
	{
		using namespace Engine;
		Debug::Log("Editor Layer End");
	}
}
