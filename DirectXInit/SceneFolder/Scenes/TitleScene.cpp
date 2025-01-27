#include"./TitleScene.h"
#include<iostream>

TitleScene::TitleScene():Scene(SCENENAME::TITLE)
{
	
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
