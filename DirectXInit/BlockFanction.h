#pragma once
#include"../../BlockBace.h"
#include"../../Ball.h"
struct HitColBlock
{
	int hitIndex = -1;//���������u���b�N�̓Y����
	int hitSafe = -1;//���������u���b�N���Z�[�u����
	bool hitFlgs = false;//�����蔻��
	GridState hitBlockType = NULLBLOCK;//���������u���b�N�̎��

	HitColBlock();
};

