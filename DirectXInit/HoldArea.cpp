#include "HoldArea.h"

// �R���X�g���N�^
HoldArea::HoldArea(Hold* holdInstance)
{
    hold = holdInstance;
}

// ����������
void HoldArea::Init()
{
    // �e�ۑ��G���A�̃X�v���C�g��������
    for (int i = 0; i < 5; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                holdBlocks[i][x][y].Init(L"asset/block.png");  // �摜�̏�����
                holdBlocks[i][x][y].SetSize(40.0f, 40.0f, 0.0f);  // �T�C�Y�ݒ�
            }
        }
    }
}
void HoldArea::Update()
{
    MouseInput* mouse = MouseInput::GetInstance();

    if (!mouse->IsLeftButtonDown()) return;  // �N���b�N����Ă��Ȃ���Ζ���

    POINT clickPos = mouse->GetClickPosition();
    const auto& holdData = hold->GetHoldData();

    for (size_t i = 0; i < holdData.size(); i++) {
        int areaX = 130 + i * (40 * 3 + 80);
        int areaY = 895;
        int areaW = 40 * 3;
        int areaH = 40 * 3;

        if (clickPos.x >= areaX && clickPos.x < areaX + areaW &&
            clickPos.y >= areaY && clickPos.y < areaY + areaH)
        {
            selectedIndex = i; // �I�������G���A���L�^
            break;
        }
    }
}
// �`�揈��
void HoldArea::Draw()
{
    // �ő�ۑ��G���A�����擾�i�ő�5�܂ŕۑ��j
    const int maxSavedAreas = 5;

    for (int i = 0; i < maxSavedAreas; i++)
    {
        // �ۑ����ꂽ�G���A�����擾
        Hold::Area area = hold->GetSavedArea(i);  // �C���f�b�N�Xi�̃G���A���擾

        // 3x3�}�X�ȓ��͈̔͂ŕ`��
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                // �͈͓��̃u���b�N�̂ݕ`��
                if (area.startX + x <= area.endX && area.startY + y <= area.endY)
                {
                    int blockType = world->GetGridData(area.startX + x, area.startY + y);  // �G���A�̃u���b�N�����擾

                    if (blockType != NULLBLOCK)
                    {
                        // �`��ʒu��ݒ�
                        holdBlocks[i][x][y].SetPos
                        (
                            130 + i * (40 * 3 + 80) + x * 40,
                            895 + y * 40,
                            0.0f
                        );
                        holdBlocks[i][x][y].Draw();  // �u���b�N��`��
                    }
                }
            }
        }
    }
}

