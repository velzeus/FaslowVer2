#pragma once
#include"../../BlockBace.h"
#include"../../Ball.h"
struct HitColBlock
{
	int hitIndex = -1;//あたったブロックの添え字
	int hitSafe = -1;//あたったブロックをセーブする
	bool hitFlgs = false;//あたり判定
	GridState hitBlockType = NULLBLOCK;//当たったブロックの種類

	HitColBlock();
};

