#include "Reposition.h"

// �R���X�g���N�^
Reposition::Reposition(Hold* holdInstance, World1_Stage* worldInstance) {
    hold = holdInstance;
    world = worldInstance;
}

void Reposition::PlaceArea(int holdIndex, int targetX, int targetY) {
    Hold::Area area = hold->GetSavedArea(holdIndex);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int blockType = area.gridData[x][y];  // �ۑ����ꂽ�u���b�N�����擾
            if (blockType != NULLBLOCK) {  // NULLBLOCK �ȊO�̃u���b�N��z�u
                world->SetGridData(targetX + x, targetY + y, blockType);
            }
        }
    }
}




