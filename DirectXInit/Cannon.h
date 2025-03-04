#pragma once
#include "Object.h"
enum RotateCannon
{
    TOWARD_UP=0,
    TOWARD_RIGHTUP,
    TOWARD_RIGHT,
    TOWARD_RIGHTDOWN,
    TOWARD_DOWN,
    TOWARD_LEFTDOWN,
    TOWARD_LEFT,
    TOWARD_LEFTUP,
};


class Cannon :
    public Object
{
public:
    Cannon();
    Cannon(int _worldNum,int _stageNum,int _index);
    //~Cannon();

    void SetCannnonModeFlg(bool _cannnonModeFlg);
    bool GetCannonModeFlg();
    //単位ベクトル
    void SetNormalizedDirection(DirectX::XMFLOAT3 _normalizedDirection);
    DirectX::XMFLOAT3 GetNormalizedDirection();

    //ステージごとに
    
private:
    //大砲の方向
    RotateCannon rotation;
    
    //大砲の番号
    int index;

    bool cannonModeFlg;

    bool setPosFlg;

    //進む方向の単位ベクトル
    DirectX::XMFLOAT3 normalizedDirection;

};

