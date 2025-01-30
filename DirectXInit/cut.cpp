#include "CUT.h"

CUT::CUT(World1_Stage* worldInstance) {
    world = worldInstance;  // �n���ꂽ World1_Stage �̃C���X�^���X��ێ�
}

// �}�E�X�I���G���A����ɃO���b�h�f�[�^���X�V
void CUT::UpdateSelection(const POINT& clickPosition, const POINT& releasePosition) {
    // �N���b�N���ꂽ�ʒu���痣���ꂽ�ʒu�����ƂɁA�I��͈͂̍���ƉE���̃}�X������
    int startX = std::min<int>(clickPosition.x, releasePosition.x);
    int startY = std::min<int>(clickPosition.y, releasePosition.y);
    int endX = std::max<int>(clickPosition.x, releasePosition.x);
    int endY = std::max<int>(clickPosition.y, releasePosition.y);

    // 40px�̃}�X�T�C�Y�Ŕ͈͂��}�X�P�ʂɕϊ�
    startX = (startX - 130) / BLOCKSIZE_X;
    startY = (startY - 130) / BLOCKSIZE_Y;
    endX = (endX - 130) / BLOCKSIZE_X;
    endY = (endY - 130) / BLOCKSIZE_Y;

    // 3x3�}�X�ȓ��͈̔͂ɐ���
    endX = std::min<int>(endX, startX + 2);
    endY = std::min<int>(endY, startY + 2);

    // �I�����ꂽ�G���A��NULLBLOCK�ɒu������
    ClearSelectedArea(startX, startY, endX, endY);
}

// �I��͈͂̃}�X���X�V����
void CUT::ClearSelectedArea(int startX, int startY, int endX, int endY) {
    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            // STICKY_BLOCK �� SLIP_BLOCK �� NULLBLOCK �ɒu��������
            int currentGridData = world->GetGridData(x, y); // GetGridData ���g�p���Ď擾
            if (currentGridData == STICKY_BLOCK || currentGridData == SLIP_BLOCK) {
                world->SetGridData(x, y, NULLBLOCK);  // SetGridData ���g�p���čX�V
            }
        }
    }
}
