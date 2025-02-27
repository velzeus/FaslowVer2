#pragma once
#include "Hold.h"
#include "Object.h"
#include"Word1_Stage.h"

class HoldArea 
{
private:
    Hold* hold;
    Object holdBlocks[5][3][3];  // 5��3�~3�u���b�N
    World1_Stage* world;
    int selectedIndex = -1;  // �I�����ꂽ�G���A�̃C���f�b�N�X
public:
    HoldArea(Hold* holdInstance);

    // �`��p�̃Z�b�g�A�b�v
    void Init();
    void Update();
    // �ۑ��f�[�^�̕\��
    void Draw();
};
