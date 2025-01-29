#include"./TitleScene.h"
#include"../../SelectScene.h"
#include<iostream>

TitleScene::TitleScene():
	Scene(SCENENAME::TITLE),manager(SceneManager::GetInstance())
{
	//manager = SceneManager::GetInstance();
}

TitleScene::~TitleScene()
{
}

int TitleScene::Start()
{
	std::cout << "TitleSceneStart" << std::endl;
	return 0;
}

int TitleScene::Update()
{
	

	manager->AddScene(SCENENAME::SELECT, std::make_unique<SelectScene>());
	manager->ChangeScene(SELECT);

	return 0;
}

int TitleScene::Draw()
{
	std::cout << "TitleSceneDraw" << std::endl;
	return 0;
}

int TitleScene::End()
{
	return 0;
}
