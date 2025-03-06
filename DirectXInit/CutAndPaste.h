#pragma once
#include "Object.h"
#include"BlockBace.h"
#include"Area.h"

#define IDX_X (0)
#define IDX_Y (1)

class CutAndPaste :
    public Object
{
private:
   // std::vector<std::vector<int>> read_gridStateList;

    std::vector<std::vector<int>> gridStateList;

    int clickIndex[2];
    int releaseIndex[2];

    bool cutModeFlg;
public:

    CutAndPaste();

    void CutBlocks(std::vector<std::vector<int>>& _gridStateList);


    void SetClickIndex(int _indexX, int _indexY);
    int GetClickIndex(int _num);
    void SetReleaseIndex(int _indexX, int _indexY);
    int GetReleaseIndex(int _num);

    void SetCutModeFlg(bool _cutModeFlg);
    bool GetCutModeFlg();

    std::vector<std::vector<int>> GetGridStateList();

    void MoveArea();
};

