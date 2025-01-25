#include "Hold.h"
#include <algorithm> // std::min, std::max

Hold::Hold(RECT selectionArea)
    : isSelecting(false), selectionArea(selectionArea), currentSaveIndex(0) {}

void Hold::Update(MouseInput& mouseInput) {
    POINT currentMousePos;

    if (mouseInput.IsLeftButtonDown()) {
        GetCursorPos(&currentMousePos);
        ScreenToClient(GetActiveWindow(), &currentMousePos);

        // �}�E�X���L���G���A���ɂ��邩�m�F
        if (currentMousePos.x >= selectionArea.left && currentMousePos.x <= selectionArea.right &&
            currentMousePos.y >= selectionArea.top && currentMousePos.y <= selectionArea.bottom) {
            if (!isSelecting) {
                // �I���̊J�n
                isSelecting = true;
                startSelection = currentMousePos;
            }
            // �I�𒆂̏I�_���X�V
            endSelection = currentMousePos;
        }
    }
    else {
        if (isSelecting) {
            // �I���I�����ɃG���A��ۑ�
            if (currentSaveIndex < 5) {
                selectedAreas[currentSaveIndex] = std::make_pair(startSelection, endSelection);
                currentSaveIndex++;
            }
            isSelecting = false;
        }
    }
}

const std::array<std::pair<POINT, POINT>, 5>& Hold::GetSelectedAreas() const {
    return selectedAreas;
}

void Hold::ResetSelection() {
    // �C���f�b�N�X�����Z�b�g���čė��p�ł���悤�ɂ���
    currentSaveIndex = 0;
}


