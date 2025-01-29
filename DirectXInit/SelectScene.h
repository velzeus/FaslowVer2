#pragma once
#include "SceneFolder/Scene.h"
#include"MouseInput.h"
#include"Object.h"

//画面に表示するものの状態
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

    //後で消しておく--------------
    MouseInput mouseInput;
    //----------------------------

    //ワールド
    Object world_image[6];

    //ステージ
    Object stage_image[5];
    
    //POINT imagePos;

};

