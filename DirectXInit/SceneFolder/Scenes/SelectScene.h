#pragma once
#include "../Scene.h"

//��ʂɕ\��������̂̏��
enum DRAWSTATE
{
    WORLDSELECTSCENE = 0,
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
    Object selectImage_world[6];

    //World�̕���
    Object worldNameImage[6];

    //�ԍ�
    Object numberText[6];

    //�X�e�[�W
    Object selectImage_stage[5];
    
    //�߂�{�^��
    Object backButton;

    //�w�i
    Object backGround;

    //�X�e�[�W���
    Object stageTexture;

    //�X�e�[�W��
    Object stageName;

    //�X�^�[�g�{�^��
    Object startButton;

    //���j���[�{�^��
    Object menuButton;
};

