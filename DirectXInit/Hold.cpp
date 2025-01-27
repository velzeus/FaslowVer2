#include "Hold.h"
#include <algorithm> // std::min, std::max
#include <iostream>

Hold::Hold()
    : isSelecting(false), currentSaveIndex(0) {}

void Hold::Update(MouseInput& mouseInput) {
    POINT currentMousePos;

    if (mouseInput.IsLeftButtonDown()) {
        GetCursorPos(&currentMousePos);
        ScreenToClient(GetActiveWindow(), &currentMousePos);

        if (!isSelecting) {
            isSelecting = true;
            startSelection = currentMousePos;
        }

        // �I�𒆂̏I�_���X�V
        endSelection = currentMousePos;
    }
    else {
        if (isSelecting) {
            if (currentSaveIndex < 5) {
                selectedAreas[currentSaveIndex] = std::make_pair(startSelection, endSelection);
                std::cout << "Area saved at index " << currentSaveIndex << std::endl;
                currentSaveIndex++;
            }
            isSelecting = false;
        }
    }
}

void Hold::Render() {
    // �ۑ����ꂽ�G���A��`�悷�邽�߂̉��̃R�[�h
    for (size_t i = 0; i < currentSaveIndex; ++i) {
        std::cout << "Saved Area " << i << ": "
            << "Start: (" << selectedAreas[i].first.x << ", " << selectedAreas[i].first.y << ") "
            << "End: (" << selectedAreas[i].second.x << ", " << selectedAreas[i].second.y << ")\n";
    }
}

void Hold::SelectAreaAtPosition(POINT pos) {
    // �N���b�N�����ʒu�ŁA�ۑ����ꂽ�G���A��I������
    for (size_t i = 0; i < currentSaveIndex; ++i) {
        const auto& area = selectedAreas[i];
        if (pos.x >= area.first.x && pos.x <= area.second.x &&
            pos.y >= area.first.y && pos.y <= area.second.y) {
            currentSaveIndex = i;  // �N���b�N�����ʒu�ɑΉ�����G���A�̃C���f�b�N�X���Z�b�g
            std::cout << "Selected saved area at index " << i << std::endl;
            break;
        }
    }
}

const std::array<std::pair<POINT, POINT>, 5>& Hold::GetSelectedAreas() const {
    return selectedAreas;
}

void Hold::ResetSelection() {
    currentSaveIndex = 0;
}



