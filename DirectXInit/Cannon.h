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
    Cannon(int _worldNum,int _stageNum,int _index,int _cannonNum);
    //~Cannon();

    void SetCannnonModeFlg(bool _cannnonModeFlg);
    bool GetCannonModeFlg();

    void SetPosFlg(bool _setPosFlg);
    bool GetPosFlg();
    //単位ベクトル
    void SetNormalizedDirection(DirectX::XMFLOAT3 _normalizedDirection);
    DirectX::XMFLOAT3 GetNormalizedDirection();

    int GetRotateCannon();

    int GetIndex();
    int GetCannonNum();

    void SetAnimationCount(int _count);
    int GetAnimationCount();

    void SetAnimFlg(bool _animFlg);
    bool GetAnimFlg();

    void SetCollisionPos(float _x, float _y, float _z);
    DirectX::XMFLOAT3 GetCollisionPos();

    void SetCollisionScale(float _x, float _y, float _z);
    DirectX::XMFLOAT3 GetCollisionScale();

    //ステージごとに
    
private:
    //大砲の方向
    RotateCannon rotation;
    
    //マスの位置で見た大砲の番号
    int index;

    int cannonNum;

    int animationCount;

    bool animFlg;

    bool cannonModeFlg;

    bool setPosFlg;

    //進む方向の単位ベクトル
    DirectX::XMFLOAT3 normalizedDirection;

    //当たり判定用の座標
    DirectX::XMFLOAT3 collisionPos;

    DirectX::XMFLOAT3 collisionScale;

};

