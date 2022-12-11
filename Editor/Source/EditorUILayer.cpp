#include "EditorUILayer.h"

#include <Engine/Core/Debug.h>
#include <Engine/UI/UISystem.h>

#include "Screen/EditorConsoleScreen.h"
#include "Screen/EntityInspectorScreen.h"
#include "Screen/FileMenuBar.h"
#include "Screen/EditorViewportScreen.h"

namespace Editor
{
	EditorUILayer::EditorUILayer() :
		Layer{"EditorUILayer"} {}

	EditorUILayer::~EditorUILayer() = default;

	void EditorUILayer::OnAttach()
	{
		using namespace Engine;
		Debug::Log("Editor UI Layer Start");

		m_WorldOutlinerScreen = UISystem::Create<WorldOutlinerScreen>();

		UISystem::Create<FileMenuBar>(*m_WorldOutlinerScreen);
	}

	void EditorUILayer::OnStart()
	{
		using namespace Engine;

		UISystem::Create<EntityInspectorScreen>(*m_WorldOutlinerScreen);

		UISystem::Create<EditorConsoleScreen>();
	}
	
	void EditorUILayer::OnPollInput(const Engine::InputData& inputData) {}
	
	void EditorUILayer::OnUpdate(const Engine::TimeData& timeData) {}

	void EditorUILayer::OnRender()
	{
		using namespace Engine;

		const SwapChain& swapChain = Application::GetSwapChain();
		Application::GetRenderer().StartRender(swapChain.GetBackbuffer());

		UISystem::DrawUI();

		Application::GetRenderer().EndRender();
	}

	void EditorUILayer::OnDetach()
	{
		using namespace Engine;
		Debug::Log("Editor UI Layer End");
	}
}
