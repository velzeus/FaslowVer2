#pragma once
#include <vector>
#include "CUT.h"
#include"SceneFolder/Scenes/StageScene.h"  
class Hold
{
public:
    // 1つの選択エリアを保持する構造体
    struct Area
    {
        int startX, startY, endX, endY; // 選択範囲の開始・終了座標
        std::vector<std::vector<int>> gridData;
    };

    Hold();  // コンストラクタ

    // エリアを保存する関数（最大5つ）
    void SaveArea(const int startX, const int startY, const int endX, const int endY);

    // 保存したエリアを描画する関数
   // void DrawSavedAreas();
    const std::vector<Area>& GetHoldData() const { return savedAreas; }
    // 指定したインデックスのエリアを取得する関数
    Area GetSavedArea(int index) const;
   

private:
    std::vector<Area> savedAreas;  // 保存されたエリアのリスト
    static const int maxSavedAreas = 5;  // 保存する最大数
    StageScene* stagescene;
};


