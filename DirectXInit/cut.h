#pragma once
#include "Word1_Stage.h"  
#include"MouseInput.h"
#include<Windows.h>
#include <algorithm>// std::min, std::max ���g�����߂ɕK�v

class CUT {
private:
    World1_Stage* world;  // World1_Stage �N���X�̃|�C���^��ێ�

public:
    CUT(World1_Stage* worldInstance);  // �R���X�g���N�^�ŃC���X�^���X��n��

    // �}�E�X�I���G���A����ɃO���b�h�f�[�^���X�V
    void UpdateSelection(const POINT& clickPosition, const POINT& releasePosition);

    // �I��͈͂̃}�X���X�V����
    void ClearSelectedArea(int startX, int startY, int endX, int endY);
};


