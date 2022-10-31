#pragma once
#include "EditorSceneCamera.h"

namespace Engine
{
	class EditorSceneCameraHandler final
	{
	public:
		EditorSceneCameraHandler(int expectedEditorSceneCameras);
		~EditorSceneCameraHandler();
		
		void Initialize(int numberOfEditorSceneCamera,
		                List<Vector3Float> cameraPositions,
		                List<Vector3Float> cameraRotation);

		void Terminate();

		void UpdateSceneCameraOfId(int editorSceneCameraId);

		EditorSceneCamera& GetSceneCamera(int editorSceneCameraId) const;

	private:
		List<EditorSceneCamera*> m_EditorSceneCameraList;
	};
}
