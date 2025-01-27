#pragma once
#include <array>
#include "Hold.h"
#include "MouseInput.h"

class Reposition {
private:
    Hold& hold;  // Holdのインスタンス
    std::array<RECT, 5> positions; // 5つの配置位置
    size_t currentSaveIndex; // 現在選択するインデックス

public:
    Reposition(Hold& hold);

    void Update(MouseInput& mouseInput); // マウス入力を処理
    void Render(); // 再配置エリアを描画するための関数
};

                                        
