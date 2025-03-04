#pragma once
#include "Hold.h"
#include "Object.h"
#include"Word1_Stage.h"

class HoldArea 
{
private:
    Hold* hold;
    Object holdBlocks[5][3][3];  // 5つの3×3ブロック
    World1_Stage* world;
    int selectedIndex = -1;  // 選択されたエリアのインデックス
public:
    HoldArea(Hold* holdInstance);

    // 描画用のセットアップ
    void Init();
    void Update();
    // 保存データの表示
    void Draw();
};
