#include "Reposition.h"
#include <iostream>

Reposition::Reposition(Hold& hold)
    : hold(hold), currentSaveIndex(0) {
    // x=130����x=1409�܂ł�5�������Ay=895?1068�ɔz�u
    int startX = 130;
    int endX = 1409;
    int startY = 895;
    int endY = 1068;
    int width = (endX - startX) / 5;

    for (int i = 0; i < 5; ++i) {
        positions[i] = { startX + i * width, startY, startX + (i + 1) * width, endY };
    }
}

void Reposition::Update(MouseInput& mouseInput) {
    POINT currentMousePos;
    if (mouseInput.IsLeftButtonDown()) {
        GetCursorPos(&currentMousePos);
        ScreenToClient(GetActiveWindow(), &currentMousePos);

        // �N���b�N���ꂽ�ʒu�łǂ̃G���A��I�����邩����
        for (size_t i = 0; i < 5; ++i) {
            if (currentMousePos.x >= positions[i].left && currentMousePos.x <= positions[i].right &&
                currentMousePos.y >= positions[i].top && currentMousePos.y <= positions[i].bottom) {
                // �N���b�N���ꂽ�͈͂�����ꍇ�A���̈ʒu��currentSaveIndex���Z�b�g
                currentSaveIndex = i;
                std::cout << "Selected area " << i + 1 << " for reposition." << std::endl;
                break;
            }
        }
    }
}

void Reposition::Render() {

}


