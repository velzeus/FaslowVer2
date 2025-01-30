#pragma once
#include "Word1_Stage.h"  
#include"MouseInput.h"
#include<Windows.h>
#include <algorithm>// std::min, std::max を使うために必要

class CUT {
private:
    World1_Stage* world;  // World1_Stage クラスのポインタを保持

public:
    CUT(World1_Stage* worldInstance);  // コンストラクタでインスタンスを渡す

    // マウス選択エリアを基にグリッドデータを更新
    void UpdateSelection(const POINT& clickPosition, const POINT& releasePosition);

    // 選択範囲のマスを更新する
    void ClearSelectedArea(int startX, int startY, int endX, int endY);
};


