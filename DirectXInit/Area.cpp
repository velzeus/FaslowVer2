#include "Area.h"

Area::Area()
{
	setBlockFlg = false;
}

void Area::SetBlockIndex(std::vector<std::vector<int>> _blockIndex)
{
	blockIndex = _blockIndex;
}

std::vector<std::vector<int>> Area::GetBlockIndex()
{
	return blockIndex;
}

void Area::SetIndex(int _index)
{
	index = _index;
}

int Area::GetIndex()
{
	return index;
}

void Area::SetSetBlockFlg(bool _setBlockFlg)
{
	setBlockFlg = _setBlockFlg;
}

bool Area::GetSetBlockFlg()
{
	return setBlockFlg;
}
