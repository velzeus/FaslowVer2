#include"./TitleScene.h"

TitleScene::TitleScene()
{
	
}

TitleScene::~TitleScene()
{
}

int TitleScene::Start()
{
	titleImage.Init(L"../../asset/back_img_01.png");
	return 0;
}

int TitleScene::Update()
{

	return 0;
}

int TitleScene::Draw()
{
	titleImage.Draw();
	return 0;
}

int TitleScene::End()
{
	return 0;
}
