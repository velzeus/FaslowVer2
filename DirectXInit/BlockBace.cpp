#include "BlockBace.h"

BlockBace::BlockBace()
{

}

BlockBace::BlockBace(int _index, GridState _blocktype) :index(_index), blocktype(_blocktype)
{

}

void BlockBace::SetBlockType(GridState _blockType)
{
    blocktype = _blockType;
}

GridState BlockBace::GetBlockType()
{
    return blocktype;
}

int BlockBace::GetIndex()
{
    return index;
}

void BlockBace::SetIndex(int _index)
{
    index = _index;
}

bool BlockBace::GetFlg()
{
    return setFlg;
}

void BlockBace::SetFlg(bool _setFlg)
{
    setFlg = _setFlg;
}
