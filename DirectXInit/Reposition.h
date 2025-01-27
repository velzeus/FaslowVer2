#pragma once
#include <array>
#include "Hold.h"
#include "MouseInput.h"

class Reposition {
private:
    Hold& hold;  // Hold�̃C���X�^���X
    std::array<RECT, 5> positions; // 5�̔z�u�ʒu
    size_t currentSaveIndex; // ���ݑI������C���f�b�N�X

public:
    Reposition(Hold& hold);

    void Update(MouseInput& mouseInput); // �}�E�X���͂�����
    void Render(); // �Ĕz�u�G���A��`�悷�邽�߂̊֐�
};

                                        
