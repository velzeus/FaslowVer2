#include"./TitleScene.h"
#include"../../SelectScene.h"
#include<iostream>


TitleScene::TitleScene()
	:Scene(SCENENAME::TITLE), input(nullptr), mouseInput(nullptr)
{
	std::cout << SceneManager::GetInstance()->SceneNameToString(GetSceneName()) 
		<< "�R���X�g���N�^" << std::endl;
	std::cout << "    SceneName(" << sceneName << ")" << std::endl;

}

TitleScene::~TitleScene()
{
}

int TitleScene::Start()
{
	input = Input::GetInstance();
	mouseInput = MouseInput::GetInstance();



	titleImage.Init(L"./SceneFolder/Scenes/TextureTest/back_img_01.png",1,1);
	titleImage.SetSize(100, 100, 1);
	titleImage.SetPos(0, 0, 0);
	titleImage.SetColor(1, 1, 1, 1);
	return 0;
}

int TitleScene::Update()
{
	if (mouseInput->IsLeftButtonDown()) {
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}


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
