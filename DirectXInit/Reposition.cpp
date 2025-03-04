#include "Reposition.h"

// コンストラクタ
Reposition::Reposition(Hold* holdInstance, StageScene* stagesceneInstance) {
    hold = holdInstance;
    stagescene= stagesceneInstance;
}

void Reposition::PlaceArea(int holdIndex, int targetX, int targetY) {
    Hold::Area area = hold->GetSavedArea(holdIndex);

    // 現在のグリッド状態を取得
    std::vector<std::vector<int>> gridStateList = stagescene->GetGridStateList();

    // 配置するエリアを更新
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            int blockType = area.gridData[x][y];  // 保存されたブロック情報を取得
            if (blockType != NULLBLOCK) {  // NULLBLOCK 以外のブロックを配置
                // 新しい位置にブロックを配置
                gridStateList[targetY + y][targetX + x] = blockType;
            }
        }
    }

    // 更新したグリッド状態をセット
    stagescene->SetGridStateList(gridStateList);
}






