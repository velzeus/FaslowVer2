#include "BlockBace.h"

BlockBace::BlockBace()
{

}

BlockBace::BlockBace(int _index, BLOCKTYPE _blocktype) :index(_index), blocktype(_blocktype)
{

}

BLOCKTYPE BlockBace::GetBlockType()
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
