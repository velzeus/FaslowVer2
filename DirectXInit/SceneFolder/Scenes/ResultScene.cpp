#include "ResultScene.h"

ResultScene::ResultScene() 
    :Scene(SCENENAME::RESULT), input(nullptr), mouseInput(nullptr)
{
    std::cout << SceneManager::GetInstance()->SceneNameToString(GetSceneName())
        << "コンストラクタ" << std::endl;
    std::cout << "    SceneName(" << sceneName << ")" << std::endl;
}

ResultScene::~ResultScene()
{
}

int ResultScene::Start()
{
    mouseInput = MouseInput::GetInstance();
    resultImage.Init(L"./asset/back_img_02.jpg");
    resultImage.SetColor(1, 1, 1, 1);
    resultImage.SetPos(0, 0, 0);
    resultImage.SetSize(100, 100, 1);
   
    return 0;
}

int ResultScene::Update()
{
    if (mouseInput->IsLeftButtonDown()) {
        SceneManager::GetInstance()->ChangeScene(TITLE);
    }
    return 0;
}

int ResultScene::Draw()
{
    resultImage.Draw();
    return 0;
}

int ResultScene::End()
{
    return 0;
}
