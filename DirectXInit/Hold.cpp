#include "Hold.h"

// コンストラクタ
Hold::Hold()
{
    // 初期化：保存されたエリアがない状態
    savedAreas.clear();
}

// エリアを保存する
void Hold::SaveArea(int startX, int startY, int endX, int endY) {
    if (savedAreas.size() >= maxSavedAreas) {
        savedAreas.erase(savedAreas.begin());  // 古いデータを削除
    }

    Area newArea;
    newArea.startX = startX;
    newArea.startY = startY;
    newArea.endX = endX;
    newArea.endY = endY;

    // 3x3 のブロック情報を保存
    newArea.gridData.resize(3, std::vector<int>(3, NULLBLOCK));

    // 現在のグリッド状態を取得
    std::vector<std::vector<int>> gridStateList = stagescene->GetGridStateList();

    // 3x3 のブロック情報を格納
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            newArea.gridData[x][y] = gridStateList[startY + y][startX + x];
        }
    }

    savedAreas.push_back(newArea);
}



// 指定したインデックスのエリアを取得する関数
Hold::Area Hold::GetSavedArea(int index) const
{
    if (index >= 0 && index < savedAreas.size()) {
        return savedAreas[index];
    }
    return { 0, 0, 0, 0 };
}