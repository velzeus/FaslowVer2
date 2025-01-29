#pragma once
#include "SceneFolder/Scene.h"
#include"MouseInput.h"
#include"Object.h"

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
    SceneManager* manager;

    WORLDNUMBER worldNum;
    STAGENUMBER stageNum;

    DRAWSTATE stateNum;

    //��ŏ����Ă���--------------
    MouseInput mouseInput;
    //----------------------------

    //���[���h
    Object world_image[6];

    //�X�e�[�W
    Object stage_image[5];
    
    //POINT imagePos;

};

