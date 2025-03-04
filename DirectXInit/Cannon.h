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
    //�P�ʃx�N�g��
    void SetNormalizedDirection(DirectX::XMFLOAT3 _normalizedDirection);
    DirectX::XMFLOAT3 GetNormalizedDirection();

    //�X�e�[�W���Ƃ�
    
private:
    //��C�̕���
    RotateCannon rotation;
    
    //��C�̔ԍ�
    int index;

    bool cannonModeFlg;

    bool setPosFlg;

    //�i�ޕ����̒P�ʃx�N�g��
    DirectX::XMFLOAT3 normalizedDirection;

};

