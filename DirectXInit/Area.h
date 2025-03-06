#pragma once
#include "Object.h"
#include"BlockBace.h"

class Area :
    public Object
{
private:

    std::vector<std::vector<int>> blockIndex;

    int index;

    bool setBlockFlg;

public:
    Area();

    void SetBlockIndex(std::vector<std::vector<int>> _blockIndex);
    std::vector<std::vector<int>> GetBlockIndex();

    void SetIndex(int _index);
    int GetIndex();

    void SetSetBlockFlg(bool _setBlockFlg);
    bool GetSetBlockFlg();

};

