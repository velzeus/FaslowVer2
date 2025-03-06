#include "Ball.h"
#define STAGE_W 1410//���[�i�P�R�O�C�P�R�O�j�@�E���i�P�S�P�O�C�W�T�O�j
#define STAGE_H 720

Ball::Ball() :rotDirection(true)
{
	Init(L"./asset/Ball/Ball_Syan.png", 1, 1);
	SetSize(40, 40, 0);
}

Ball::Ball(bool _rotDir) :rotDirection(_rotDir)
{

}

DIRECTION Ball::GetMoveDir()
{
	return moveDir;
}

void Ball::SetMoveDir(DIRECTION dir)
{
	moveDir = dir;
}

void Ball::Move()
{
	switch (moveDir) {
	case RIGHT: SetPos(GetPos().x + vel_x, GetPos().y, GetPos().z); break;
	case LEFT:  SetPos(GetPos().x - vel_x, GetPos().y, GetPos().z); break;
	case UP:    SetPos(GetPos().x, GetPos().y + vel_y, GetPos().z); break;
	case DOWN:  SetPos(GetPos().x, GetPos().y - vel_y, GetPos().z); break;
	case STOP:;
	}
}

void Ball::Move_Cannon(DirectX::XMFLOAT3 _normalizedDirection)
{
	SetPos(GetPos().x + vel_x * _normalizedDirection.x, GetPos().y + vel_y * _normalizedDirection.y, GetPos().z);

	
}

bool Ball::GetrotDir()
{
	return rotDirection;
}

void Ball::SetrotDir(bool _rotdir)
{
	rotDirection = _rotdir;
}

void Ball::Setborder()
{
	if (pos.x > 430)//�E�[
	{
		pos.x = -810.0f - vel_x;
		boder = true;
	}

	if (pos.x < -850)//���[
	{
		pos.x = 390.0 + vel_x;
		boder = true;
	}

	if (pos.y > 430)//��[
	{
		pos.y = -290 - vel_y;
		boder = true;
	}

	if (pos.y < -330)//���[
	{
		pos.y = 390 + vel_y;
		boder = true;
	}
}
