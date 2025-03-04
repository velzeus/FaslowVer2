#include "Reposition.h"

// �R���X�g���N�^
Reposition::Reposition(Hold* holdInstance, StageScene* stagesceneInstance) {
    hold = holdInstance;
    stagescene= stagesceneInstance;
}

void Reposition::PlaceArea(int holdIndex, int targetX, int targetY) {
    Hold::Area area = hold->GetSavedArea(holdIndex);

    // ���݂̃O���b�h��Ԃ��擾
    std::vector<std::vector<int>> gridStateList = stagescene->GetGridStateList();

    // �z�u����G���A���X�V
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int blockType = area.gridData[x][y];  // �ۑ����ꂽ�u���b�N�����擾
            if (blockType != NULLBLOCK) {  // NULLBLOCK �ȊO�̃u���b�N��z�u
                // �V�����ʒu�Ƀu���b�N��z�u
                gridStateList[targetY + y][targetX + x] = blockType;
            }
        }
    }

    // �X�V�����O���b�h��Ԃ��Z�b�g
    stagescene->SetGridStateList(gridStateList);
}






