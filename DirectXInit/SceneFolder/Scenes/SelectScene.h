#pragma once
#include "../Scene.h"

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
    

    WORLDNUMBER worldNum;
    STAGENUMBER stageNum;

    DRAWSTATE stateNum;

   // MouseInput* mouseInput;
    
    TS::TS_InputSystem* inputSystem;

    //ワールド
    Object world_image[6];

    //ステージ
    Object stage_image[5];
    
    //戻るボタン
    Object backButton;

    //背景
    Object backGround;
};

