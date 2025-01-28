#include "Hold.h"

Hold::Hold() {}

Hold::~Hold() {}

void Hold::Update(World1_Stage& stage) {
    mouseInput.Update(); // �}�E�X�̏�Ԃ��X�V

    // ���N���b�N���ꂽ�ꍇ
    if (mouseInput.IsLeftButtonDown()) {
        POINT clickPos = mouseInput.GetClickPosition();
        POINT releasePos = mouseInput.GetReleasePosition();

        // �͈͂��v�Z
        std::vector<Grid> grids = CalculateGrids(clickPos, releasePos, stage);

        // �O���b�h���X�V
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

    // �I��͈͂̍��W���擾�i���ォ��E���ւ͈̔́j
    int startX = start.x / BLOCKSIZE_X;
    int startY = start.y / BLOCKSIZE_Y;
    int endX = end.x / BLOCKSIZE_X;
    int endY = end.y / BLOCKSIZE_Y;

    // �͈͓��̃O���b�h���v�Z
    for (int x = startX; x <= endX; ++x) {
        for (int y = startY; y <= endY; ++y) {
            grids.push_back(Grid{ x, y, static_cast<GridState>(stage.gridData[x][y]) });// stage.gridData[x][y]�ŏ�Ԃ��擾
        }
    }

    return grids;
}

void Hold::UpdateSavedGrids(const std::vector<Grid>& grids) {
    savedGrids.clear(); // ��x���Z�b�g

    // �ۑ����ꂽ�O���b�h���X�V
    for (const auto& grid : grids) {
        GridState gridState = grid.state;

        // NULLBLOCK, STICKY_BLOCK �ł���Εۑ�
        if (gridState == NULLBLOCK || gridState == STICKY_BLOCK) {
            savedGrids.push_back({ grid.x, grid.y, NULLBLOCK }); // NULLBLOCK�ɒu������
        }
        else {
            // GORL, COIN, BALL �͂��̂܂ܕۑ�
            savedGrids.push_back({ grid.x, grid.y, gridState });
        }
    }
}






