#include "pch.h"
#include "EditorSceneCameraHandler.h"

#include "Engine/Core/Debug.h"
#include "Engine/ECS/Component/TransformComponent.h"

namespace Engine
{
	EditorSceneCameraHandler::EditorSceneCameraHandler(int expectedEditorSceneCameras) :
		m_EditorSceneCameraList{List<EditorSceneCamera*>()}
	{
		m_EditorSceneCameraList.reserve(expectedEditorSceneCameras);
	}

	EditorSceneCameraHandler::~EditorSceneCameraHandler()
	{
	}

	void EditorSceneCameraHandler::Initialize(int numberOfEditorSceneCamera,
	                                          List<Vector3Float> cameraPositions,
	                                          List<Vector3Float> cameraRotation)
	{
		for (auto i = 0; i < numberOfEditorSceneCamera; i++)
		{
			m_EditorSceneCameraList.push_back(new EditorSceneCamera(L"EditorCamera" + i));
			m_EditorSceneCameraList[i]->Transform().Position = cameraPositions[i];
			m_EditorSceneCameraList[i]->Transform().Rotation = cameraRotation[i];
		}
	}

	void EditorSceneCameraHandler::Terminate()
	{
		for (auto i = 0; i < m_EditorSceneCameraList.size(); i++)
		{
			delete m_EditorSceneCameraList[i];
			m_EditorSceneCameraList[i] = nullptr;
		}

		m_EditorSceneCameraList.clear();
	}

	void EditorSceneCameraHandler::UpdateSceneCameraOfId(int editorSceneCameraId)
	{
		Debug::Assert(editorSceneCameraId <=
		              m_EditorSceneCameraList.size() - 1 &&
		              editorSceneCameraId >= 0);
		m_EditorSceneCameraList[editorSceneCameraId]->UpdateController();
	}

	EditorSceneCamera& EditorSceneCameraHandler::
	GetSceneCamera(const int editorSceneCameraId) const
	{
		Debug::Assert(editorSceneCameraId <=
		              m_EditorSceneCameraList.size() - 1
		              && editorSceneCameraId >= 0);
		return *m_EditorSceneCameraList[editorSceneCameraId];
	}
}
