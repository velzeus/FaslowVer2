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
    //�P�ʃx�N�g��
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

    //�X�e�[�W���Ƃ�
    
private:
    //��C�̕���
    RotateCannon rotation;
    
    //�}�X�̈ʒu�Ō�����C�̔ԍ�
    int index;

    int cannonNum;

    int animationCount;

    bool animFlg;

    bool cannonModeFlg;

    bool setPosFlg;

    //�i�ޕ����̒P�ʃx�N�g��
    DirectX::XMFLOAT3 normalizedDirection;

    //�����蔻��p�̍��W
    DirectX::XMFLOAT3 collisionPos;

    DirectX::XMFLOAT3 collisionScale;

};

