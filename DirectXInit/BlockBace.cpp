#include "BlockBace.h"

BlockBace::BlockBace()
{

}

BlockBace::BlockBace(int _index, GridState _blocktype) :index(_index), blocktype(_blocktype)
{

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
