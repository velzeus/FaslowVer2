#pragma once
#include "Object.h"  

class HoldArea
{
private:
    // 19�~3�̃u���b�N�z��
    Object blocks[23][3];

public:
    // �R���X�g���N�^�E�f�X�g���N�^
    HoldArea() = default;
    ~HoldArea() = default;

    // ���������\�b�h
    void Init(HWND hWnd);

    // �`�惁�\�b�h
    void Draw();

    // �e��ݒ�֐�
    void SetPos(float x, float y, float z);  // ���W�ݒ�
    void SetSize(float width, float height, float depth); // �T�C�Y�ݒ�
};

