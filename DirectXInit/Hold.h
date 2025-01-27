#pragma once
#include <array>
#include <utility> // std::pair
#include "MouseInput.h"

class Hold {
private:
    POINT startSelection; // 選択の開始点
    POINT endSelection;   // 選択の終了点
    bool isSelecting;     // 選択中かどうか

    // 配列でエリアを保存（最大5回）
    std::array<std::pair<POINT, POINT>, 5> selectedAreas;
    size_t currentSaveIndex; // 現在選択したインデックス

public:
    Hold();

    void Update(MouseInput& mouseInput); // マウス入力に基づいて選択状態を更新
    void Render(); // 保存したエリアを描画する
    const std::array<std::pair<POINT, POINT>, 5>& GetSelectedAreas() const; // 選択されたエリアを取得
    void ResetSelection(); // 選択状態をリセット
    void SelectAreaAtPosition(POINT pos); // クリックした位置でエリア選択
};

