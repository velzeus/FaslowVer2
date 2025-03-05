#pragma once
#include"SceneFolder/Scenes/StageScene.h"  
#include"MouseInput.h"
#include<Windows.h>
#include <algorithm>
#include"hold.h"

class CUT 
{
private:
    StageScene*stagescene;  // StageScene �N���X�̃|�C���^��ێ�
   
public:
    CUT(StageScene* stagesceneInstance);  // �R���X�g���N�^�ŃC���X�^���X��n��
    // �}�E�X�I���G���A����ɃO���b�h�f�[�^���X�V
    void UpdateSelection(const POINT& clickPosition, const POINT& releasePosition);
    void Update();
    // �I��͈͂̃}�X���X�V����
    void ClearSelectedArea(int startX, int startY, int endX, int endY);
   
};


