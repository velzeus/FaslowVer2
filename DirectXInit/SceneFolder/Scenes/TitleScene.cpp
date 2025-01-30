#include"./TitleScene.h"
#include"../../SelectScene.h"
#include<iostream>

#define BUTTONSIZE_X (float)370
#define BUTTONSIZE_Y (float)75
#define BUTTONSIZE_Z (float)1

// ButtonのX座標とY座標は固定
#define BUTTON_POS_X (float)-100	
#define BUTTON_POS_Z (float)-100


#define START_BUTTON_POS_Y	(float)-100		// StartButton
#define END_BUTTON_POS_Y	(float)-150		// EndButton

#define BUTTON_COLOR (float)1



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



	StartButton.Init(L"./asset/UI/スタート.png",1,1);
	StartButton.SetSize(BUTTONSIZE_X, BUTTONSIZE_Y, BUTTONSIZE_Z);
	StartButton.SetPos(0, START_BUTTON_POS_Y, 0);
	StartButton.SetColor(1, 1, 1, 1);

	EndButton.Init(L"./asset/UI/エンド.png", 1, 1);
	EndButton.SetSize(BUTTONSIZE_X, BUTTONSIZE_Y, BUTTONSIZE_Z);
	EndButton.SetPos(0,-150,0);
	EndButton.SetColor(1,1,1,1);



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
	StartButton.Draw();
	return 0;
}

int TitleScene::End()
{
	
	return 0;
}
