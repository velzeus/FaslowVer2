#pragma once
#include "../Scene.h"
class ResultScene :
    public Scene
{
public:
    ResultScene();
    ~ResultScene();

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;


private:
    
   // MouseInput* mouseInput;

    TS::TS_InputSystem* inputSystem;

    Input* input;
    Object resultImage;

    //次のステージへボタン
    Object nextStage;
};

