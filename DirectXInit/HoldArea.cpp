#include "HoldArea.h"


void HoldArea::Init(HWND hWnd)
{
    // �z�[���h�G���A�̒��S���W
    float centerX = -190.0f;
    float centerY = -403.0f;

    // �e�u���b�N�̏�����
    for (int x = 0; x < 19; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            // ���ꂼ��̃u���b�N�̏�����
            blocks[x][y].Init(L"asset/block.png");  // �u���b�N�摜���Z�b�g
            blocks[x][y].SetSize(40.0f, 40.0f, 0.0f);  // �u���b�N�T�C�Y40x40�ɐݒ�

            // ���W��ݒ� (���S����v�Z)
            blocks[x][y].SetPos(centerX + x * 80.0f, centerY + y * 80.0f, 0.0f);
        }
    }
}

void HoldArea::Draw()
{
    // �e�u���b�N��`��
    for (int x = 0; x < 19; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            blocks[x][y].Draw();
        }
    }
}

void HoldArea::SetPos(float x, float y, float z)
{
    // �z�[���h�G���A�S�̂̈ʒu��ݒ�
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            blocks[i][j].SetPos(x, y, z);
        }
    }
}

void HoldArea::SetSize(float width, float height, float depth)
{
    // �z�[���h�G���A�S�̂̃T�C�Y��ݒ�
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            blocks[i][j].SetSize(width, height, depth);
        }
    }
}
