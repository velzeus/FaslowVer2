#include "Hold.h"

Hold::Hold() {}

Hold::~Hold() {}

void Hold::Update(World1_Stage& stage) {
    mouseInput.Update(); // マウスの状態を更新

    // 左クリックされた場合
    if (mouseInput.IsLeftButtonDown()) {
        POINT clickPos = mouseInput.GetClickPosition();
        POINT releasePos = mouseInput.GetReleasePosition();

        // 範囲を計算
        std::vector<Grid> grids = CalculateGrids(clickPos, releasePos, stage);

        // グリッドを更新
        UpdateSavedGrids(grids);
    }
}




void Hold::Draw() {
    
}

std::vector<Grid> Hold::GetSavedGrids() const {
    return savedGrids;
}

std::vector<Grid> Hold::CalculateGrids(const POINT& start, const POINT& end, World1_Stage& stage) {
    std::vector<Grid> grids;

    // 選択範囲の座標を取得（左上から右下への範囲）
    int startX = start.x / BLOCKSIZE_X;
    int startY = start.y / BLOCKSIZE_Y;
    int endX = end.x / BLOCKSIZE_X;
    int endY = end.y / BLOCKSIZE_Y;

    // 範囲内のグリッドを計算
    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            grids.push_back(Grid{ x, y, static_cast<GridState>(stage.gridData[x][y]) });// stage.gridData[x][y]で状態を取得
        }
    }

    return grids;
}

void Hold::UpdateSavedGrids(const std::vector<Grid>& grids) {
    savedGrids.clear(); // 一度リセット

    // 保存されたグリッドを更新
    for (const auto& grid : grids) {
        GridState gridState = grid.state;

        // NULLBLOCK, STICKY_BLOCK であれば保存
        if (gridState == NULLBLOCK || gridState == STICKY_BLOCK) {
            savedGrids.push_back({ grid.x, grid.y, NULLBLOCK }); // NULLBLOCKに置き換え
        }
        else {
            // GORL, COIN, BALL はそのまま保存
            savedGrids.push_back({ grid.x, grid.y, gridState });
        }
    }
}






