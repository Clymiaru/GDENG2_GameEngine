#include "EditorUILayer.h"

#include <Engine/Core/Debug.h>
#include <Engine/UI/UISystem.h>

#include "Screen/FileMenuBar.h"
#include "Screen/ViewportScreen.h"
#include "Screen/WorldOutlinerScreen.h"

namespace Editor
{
	EditorUILayer::EditorUILayer() :
		Layer{"EditorUILayer"} {}
	
	EditorUILayer::~EditorUILayer() = default;
	
	void EditorUILayer::OnAttach()
	{
		using namespace Engine;
		Debug::Log("Editor UI Layer Start");

		UISystem::Create<FileMenuBar>();

		UISystem::Create<WorldOutlinerScreen>();

		UISystem::Create<ViewportScreen>();
		
	}
	
	void EditorUILayer::OnPollInput() {}
	
	void EditorUILayer::OnUpdate() {}
	
	void EditorUILayer::OnRender()
	{
		using namespace Engine;

		UISystem::DrawUI();
	}
	
	void EditorUILayer::OnDetach()
	{
		using namespace Engine;
		Debug::Log("Editor UI Layer End");
	}
}
