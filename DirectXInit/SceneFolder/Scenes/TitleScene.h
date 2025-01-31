#pragma once
#include "../Scene.h"


class TitleScene :
    public Scene
{

public:

    // �R���X�g���N�^/�f�X�g���N�^
    TitleScene();
    ~TitleScene() override;


    // 
    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

private:

    //MouseInput* mouseInput;

    TS::TS_InputSystem* inputSystem;

    Input* input;

    Object StartButton;
    Object EndButton;
};

