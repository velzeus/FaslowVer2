#include "CutAndPaste.h"
CutAndPaste::CutAndPaste()
{
	gridStateList.resize(3);
	for (int i = 0; i < gridStateList.size(); i++)
	{
		gridStateList[i].resize(3, NULLBLOCK);
	}

	
}
void CutAndPaste::CutBlocks(std::vector<std::vector<int>>& _gridStateList)
{
	//std::vector<std::vector<int>> gridStateList;

	////切り取った長さを求める
	//int length_X = std::abs(clickIndex[IDX_X] - releaseIndex[IDX_X]) + 1;
	//int length_Y = std::abs(clickIndex[IDX_Y] - releaseIndex[IDX_Y]) + 1;

	//if (length_X > 3)
	//{
	//	length_X = 3;
	//}
	//if (length_Y > 3)
	//{
	//	length_Y = 3;
	//}

	////基点（値が小さい方）を左下にする処理
	//if (clickIndex[IDX_X] > releaseIndex[IDX_X])
	//{
	//	int work=clickIndex[IDX_X];
	//	clickIndex[IDX_X] = releaseIndex[IDX_X];
	//	releaseIndex[IDX_X] = work;
	//}

	//if (clickIndex[IDX_Y] > releaseIndex[IDX_Y])
	//{
	//	int work = clickIndex[IDX_Y];
	//	clickIndex[IDX_Y] = releaseIndex[IDX_Y];
	//	releaseIndex[IDX_Y] = work;
	//}

	for (int i = 0; i < 3; i++)
	{
		for (int j = -0; j < 3; j++)
		{
			//切り取れるブロックのとき
			if (_gridStateList[clickIndex[IDX_Y] + i - 1][clickIndex[IDX_X] + j - 1] == STICKY_BLOCK ||
				_gridStateList[clickIndex[IDX_Y] + i - 1][clickIndex[IDX_X] + j - 1] == SLIP_BLOCK)
			{
				//切り取った場所にあるマスの状態を格納
				gridStateList[i][j] = _gridStateList[clickIndex[IDX_Y] + i - 1][clickIndex[IDX_X] + j - 1];
				_gridStateList[clickIndex[IDX_Y] + i - 1][clickIndex[IDX_X] + j - 1] = NULLBLOCK;
			}

		}
	}



	return ;
}

void CutAndPaste::SetClickIndex(int _indexX, int _indexY)
{
	clickIndex[0] = _indexX;
	clickIndex[1] = _indexY;
}

int CutAndPaste::GetClickIndex(int _num)
{
	return clickIndex[_num];
}

void CutAndPaste::SetReleaseIndex(int _indexX, int _indexY)
{
	releaseIndex[0] = _indexX;
	releaseIndex[1] = _indexY;
}

int CutAndPaste::GetReleaseIndex(int _num)
{
	return releaseIndex[_num];
}

void CutAndPaste::SetCutModeFlg(bool _cutModeFlg)
{
	cutModeFlg = _cutModeFlg;
}

bool CutAndPaste::GetCutModeFlg()
{
	return cutModeFlg;
}

std::vector<std::vector<int>> CutAndPaste::GetGridStateList()
{
	return gridStateList;
}
