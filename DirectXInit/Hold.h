#pragma once
#include <vector>
#include <utility> // std::pair
#pragma once
#include <array>
#include <utility> // std::pair
#include "MouseInput.h"

class Hold {
private:
    POINT startSelection; // �I���̊J�n�_
    POINT endSelection;   // �I���̏I���_
    bool isSelecting;     // �I�𒆂��ǂ���

    // �z��ŃG���A��ۑ��i�ő�5��j
    std::array<std::pair<POINT, POINT>, 5> selectedAreas;
    size_t currentSaveIndex; // ���ɕۑ�����C���f�b�N�X

    RECT selectionArea; // �}�E�X���͂��L���ȃG���A

public:
    Hold(RECT selectionArea);

    void Update(MouseInput& mouseInput); // �}�E�X���͂Ɋ�Â��đI����Ԃ��X�V
    const std::array<std::pair<POINT, POINT>, 5>& GetSelectedAreas() const; // �I�����ꂽ�G���A���擾
    void ResetSelection(); // �I����Ԃ����Z�b�g
};
