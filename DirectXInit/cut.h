#pragma once
#include"SceneFolder/Scenes/StageScene.h"  
#include"MouseInput.h"
#include<Windows.h>
#include <algorithm>
#include"hold.h"

class CUT 
{
private:
    StageScene*stagescene;  // StageScene クラスのポインタを保持
   
public:
    CUT(StageScene* stagesceneInstance);  // コンストラクタでインスタンスを渡す
    // マウス選択エリアを基にグリッドデータを更新
    void UpdateSelection(const POINT& clickPosition, const POINT& releasePosition);
    void Update();
    // 選択範囲のマスを更新する
    void ClearSelectedArea(int startX, int startY, int endX, int endY);
   
};


