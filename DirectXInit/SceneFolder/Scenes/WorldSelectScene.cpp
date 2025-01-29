#include "WorldSelectScene.h"
#include"TitleScene.h"
//#include"../../ClassA.h"

WorldSelectScene::WorldSelectScene() :Scene(SCENENAME::RESULT), manager(SceneManager::GetInstance())
{
	//manager = SceneManager::GetInstance();
}

WorldSelectScene::~WorldSelectScene()
{
}

int WorldSelectScene::Start()
{

	std::cout << "TitleSceneStart" << std::endl;
	return 0;
}

int WorldSelectScene::Update()
{
	manager->AddScene(SCENENAME::STAGE, std::make_unique<WorldSelectScene>());
	manager->ChangeScene(STAGE);

	return 0;
}

int WorldSelectScene::Draw()
{
	std::cout << "TitleSceneDraw" << std::endl;
	return 0;
}

int WorldSelectScene::End()
{
	return 0;
}
