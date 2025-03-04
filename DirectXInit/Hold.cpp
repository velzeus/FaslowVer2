#include "Hold.h"

// �R���X�g���N�^
Hold::Hold()
{
    // �������F�ۑ����ꂽ�G���A���Ȃ����
    savedAreas.clear();
}

// �G���A��ۑ�����
void Hold::SaveArea(int startX, int startY, int endX, int endY) {
    if (savedAreas.size() >= maxSavedAreas) {
        savedAreas.erase(savedAreas.begin());  // �Â��f�[�^���폜
    }

    Area newArea;
    newArea.startX = startX;
    newArea.startY = startY;
    newArea.endX = endX;
    newArea.endY = endY;

    // 3x3 �̃u���b�N����ۑ�
    newArea.gridData.resize(3, std::vector<int>(3, NULLBLOCK));
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            newArea.gridData[x][y] = world->GetGridData(startX + x, startY + y);
        }
    }

    savedAreas.push_back(newArea);
}


// �w�肵���C���f�b�N�X�̃G���A���擾����֐�
Hold::Area Hold::GetSavedArea(int index) const
{
    if (index >= 0 && index < savedAreas.size()) {
        return savedAreas[index];
    }
    return { 0, 0, 0, 0 };
}