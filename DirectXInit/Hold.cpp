#include "Hold.h"
#include <algorithm> // std::min, std::max

Hold::Hold(RECT selectionArea)
    : isSelecting(false), selectionArea(selectionArea), currentSaveIndex(0) {}

void Hold::Update(MouseInput& mouseInput) {
    POINT currentMousePos;

    if (mouseInput.IsLeftButtonDown()) {
        GetCursorPos(&currentMousePos);
        ScreenToClient(GetActiveWindow(), &currentMousePos);

        // マウスが有効エリア内にあるか確認
        if (currentMousePos.x >= selectionArea.left && currentMousePos.x <= selectionArea.right &&
            currentMousePos.y >= selectionArea.top && currentMousePos.y <= selectionArea.bottom) {
            if (!isSelecting) {
                // 選択の開始
                isSelecting = true;
                startSelection = currentMousePos;
            }
            // 選択中の終点を更新
            endSelection = currentMousePos;
        }
    }
    else {
        if (isSelecting) {
            // 選択終了時にエリアを保存
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
    // インデックスをリセットして再利用できるようにする
    currentSaveIndex = 0;
}


