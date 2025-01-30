#pragma once
#include <vector>
#include "MouseInput.h"
#include "Word1_Stage.h"

// Grid構造体の定義
struct Grid {
    int x, y;
    GridState state;
};

class Hold {
private:
    MouseInput mouseInput; // マウス入力オブジェクト
    std::vector<Grid> savedGrids; // 保存されたグリッドの状態
    std::vector<std::vector<GridState>> originalGridStates; // 保存元の状態

    // マウスのクリック範囲からグリッドを計算
    std::vector<Grid> CalculateGrids(const POINT& start, const POINT& end, World1_Stage& stage);

    // 選択された範囲のグリッドをNULLBLOCK, STICKY_BLOCKに置き換える
    void UpdateSavedGrids(const std::vector<Grid>& grids);

public:
    Hold(); // コンストラクタ
    ~Hold(); // デストラクタ

    void Update(World1_Stage& stage); // 更新
    void Draw(); // 選択範囲を描画
    std::vector<Grid> GetSavedGrids() const; // 保存されたグリッド情報を取得


};





