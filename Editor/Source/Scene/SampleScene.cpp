#include "SampleScene.h"

namespace Editor
{
	SampleScene::SampleScene() :
		Scene{0, "Default Scene"} {}
	
	SampleScene::~SampleScene()
	{
		Scene::~Scene();
	}
	
	void SampleScene::OnBegin()
	{
		Scene::OnBegin();
	}
	
	void SampleScene::OnEnd()
	{
		Scene::OnEnd();
	}
}
