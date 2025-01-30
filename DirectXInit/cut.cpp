#include "CUT.h"

CUT::CUT(World1_Stage* worldInstance) {
    world = worldInstance;  // 渡された World1_Stage のインスタンスを保持
}

// マウス選択エリアを基にグリッドデータを更新
void CUT::UpdateSelection(const POINT& clickPosition, const POINT& releasePosition) {
    // クリックされた位置から離された位置をもとに、選択範囲の左上と右下のマスを決定
    int startX = std::min<int>(clickPosition.x, releasePosition.x);
    int startY = std::min<int>(clickPosition.y, releasePosition.y);
    int endX = std::max<int>(clickPosition.x, releasePosition.x);
    int endY = std::max<int>(clickPosition.y, releasePosition.y);

    // 40pxのマスサイズで範囲をマス単位に変換
    startX = (startX - 130) / BLOCKSIZE_X;
    startY = (startY - 130) / BLOCKSIZE_Y;
    endX = (endX - 130) / BLOCKSIZE_X;
    endY = (endY - 130) / BLOCKSIZE_Y;

    // 3x3マス以内の範囲に制限
    endX = std::min<int>(endX, startX + 2);
    endY = std::min<int>(endY, startY + 2);

    // 選択されたエリアをNULLBLOCKに置き換え
    ClearSelectedArea(startX, startY, endX, endY);
}

// 選択範囲のマスを更新する
void CUT::ClearSelectedArea(int startX, int startY, int endX, int endY) {
    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            // STICKY_BLOCK や SLIP_BLOCK を NULLBLOCK に置き換える
            int currentGridData = world->GetGridData(x, y); // GetGridData を使用して取得
            if (currentGridData == STICKY_BLOCK || currentGridData == SLIP_BLOCK) {
                world->SetGridData(x, y, NULLBLOCK);  // SetGridData を使用して更新
            }
        }
    }
}
