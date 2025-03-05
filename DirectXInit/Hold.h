#pragma once
#include <vector>
#include "CUT.h"
#include"SceneFolder/Scenes/StageScene.h"  
class Hold
{
public:
    // 1�̑I���G���A��ێ�����\����
    struct Area
    {
        int startX, startY, endX, endY; // �I��͈͂̊J�n�E�I�����W
        std::vector<std::vector<int>> gridData;
    };

    Hold();  // �R���X�g���N�^

    // �G���A��ۑ�����֐��i�ő�5�j
    void SaveArea(const int startX, const int startY, const int endX, const int endY);

    // �ۑ������G���A��`�悷��֐�
   // void DrawSavedAreas();
    const std::vector<Area>& GetHoldData() const { return savedAreas; }
    // �w�肵���C���f�b�N�X�̃G���A���擾����֐�
    Area GetSavedArea(int index) const;
   

private:
    std::vector<Area> savedAreas;  // �ۑ����ꂽ�G���A�̃��X�g
    static const int maxSavedAreas = 5;  // �ۑ�����ő吔
    StageScene* stagescene;
};


