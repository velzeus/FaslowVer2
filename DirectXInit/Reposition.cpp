#include "Reposition.h"

// コンストラクタ
Reposition::Reposition(Hold* holdInstance, World1_Stage* worldInstance) {
    hold = holdInstance;
    world = worldInstance;
}

void Reposition::PlaceArea(int holdIndex, int targetX, int targetY) {
    Hold::Area area = hold->GetSavedArea(holdIndex);

    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int blockType = area.gridData[x][y];  // 保存されたブロック情報を取得
            if (blockType != NULLBLOCK) {  // NULLBLOCK 以外のブロックを配置
                world->SetGridData(targetX + x, targetY + y, blockType);
            }
        }
    }
}




