#pragma once
#include <vector>
#include "MouseInput.h"
#include "Word1_Stage.h"

// Grid�\���̂̒�`
struct Grid {
    int x, y;
    GridState state;
};

class Hold {
private:
    MouseInput mouseInput; // �}�E�X���̓I�u�W�F�N�g
    std::vector<Grid> savedGrids; // �ۑ����ꂽ�O���b�h�̏��
    std::vector<std::vector<GridState>> originalGridStates; // �ۑ����̏��

    // �}�E�X�̃N���b�N�͈͂���O���b�h���v�Z
    std::vector<Grid> CalculateGrids(const POINT& start, const POINT& end, World1_Stage& stage);

    // �I�����ꂽ�͈͂̃O���b�h��NULLBLOCK, STICKY_BLOCK�ɒu��������
    void UpdateSavedGrids(const std::vector<Grid>& grids);

public:
    Hold(); // �R���X�g���N�^
    ~Hold(); // �f�X�g���N�^

    void Update(World1_Stage& stage); // �X�V
    void Draw(); // �I��͈͂�`��
    std::vector<Grid> GetSavedGrids() const; // �ۑ����ꂽ�O���b�h�����擾


};





