#pragma once
#include "../Scene.h"

//��ʂɕ\��������̂̏��
enum DRAWSTATE
{
    WOELDSELECTSCENE = 0,
    STAGESELECTSCENE,
    SETSTAGE,
};

class SelectScene :
    public Scene
{
public:
    SelectScene();
    ~SelectScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

private:
    

    WORLDNUMBER worldNum;
    STAGENUMBER stageNum;

    DRAWSTATE stateNum;

   // MouseInput* mouseInput;
    
    TS::TS_InputSystem* inputSystem;

    //���[���h
    Object world_image[6];

    //�X�e�[�W
    Object stage_image[5];
    
    //�߂�{�^��
    Object backButton;

    //�w�i
    Object backGround;
};

