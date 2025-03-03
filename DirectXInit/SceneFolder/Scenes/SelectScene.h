#pragma once
#include "../Scene.h"

//画面に表示するものの状態
enum DRAWSTATE
{
    WORLDSELECTSCENE = 0,
    STAGESELECTSCENE,
    SETSTAGE,
    MOVEFLAME,
};

#define FLAMENUM (20)

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
    Object selectImage_world[6];

    //Worldの文字
    Object worldNameImage[6];

    //番号
    Object numberText[6];

    //ステージ
    Object selectImage_stage[5];

    //Stageの文字
    Object stageNameImage[5];
    
    //戻るボタン
    Object backButton;

    //背景
    Object backGround;

    //ステージ画面
    Object stageTexture;

    //ステージ名
    Object stageName;

    //ステージ名の枠
    Object stageNameFlame;

    //ステージ名の番号
    Object stageNameNumber;

    //スタートボタン
    Object startButton;

    //メニューボタン
    Object menuButton;

    //動かす用の枠
    Object moveFlame;

    //枠を動かす
    bool MoveFlame();

    //正規化した方向ベクトル
    DirectX::XMFLOAT3 normalizedDirection;

    DirectX::XMFLOAT3 normalizedScaleVector;

    //移動する速度
    float moveSpeed;

    //大きさの変化量
    float deltaScale;

    //目標地点の座標
    //DirectX::XMFLOAT3 targetPos;

    //移動処理をしたフレーム数
    int moveCount;

    ////目標の大きさ
    //DirectX::XMFLOAT3 targetScale;
    //方向ベクトル
    //DirectX::XMFLOAT3 direction;

    //ベクトルの長さ

};

