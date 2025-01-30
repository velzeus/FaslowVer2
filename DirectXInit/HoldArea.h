#pragma once
#include "Object.h"  

class HoldArea
{
private:
    // 19×3のブロック配列
    Object blocks[23][3];

public:
    // コンストラクタ・デストラクタ
    HoldArea() = default;
    ~HoldArea() = default;

    // 初期化メソッド
    void Init(HWND hWnd);

    // 描画メソッド
    void Draw();

    // 各種設定関数
    void SetPos(float x, float y, float z);  // 座標設定
    void SetSize(float width, float height, float depth); // サイズ設定
};

