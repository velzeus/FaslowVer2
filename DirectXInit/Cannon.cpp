#include "Cannon.h"

Cannon::Cannon(int _worldNum, int _stageNum, int _index, int _cannonNum)
{
	//���[���h�A�X�e�[�W�A��C�̔ԍ����Ƃɒ��ڏ������s��
	//�Ȃ��ꏊ�͉������Ȃ�
	index = _index;
	cannonNum = _cannonNum;
	//��C�����郏�[���h��������������
	switch (_worldNum)
	{
	case 3:
		//�X�e�[�W���Ƃɏ���������
		switch (_stageNum)
		{
		case 1:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_RIGHT;
				break;
			case 1:
				rotation = TOWARD_LEFT;
				break;
			default:
				break;
			}

			break;
		case 2:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_RIGHTUP;
				break;
			case 1:
				rotation = TOWARD_LEFT;
				break;
			case 2:
				rotation = TOWARD_RIGHTDOWN;
				break;
			default:
				break;
			}
			break;
		case 3:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_RIGHTUP;
				break;
			default:
				break;
			}
			break;
		case 4:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_RIGHTDOWN;
				break;
			case 1:
				rotation = TOWARD_RIGHTUP;
				break;
			default:
				break;
			}
			break;
		case 5:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_DOWN;
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}

		break;
	case 6:
		//�X�e�[�W���Ƃɏ���������
		switch (_stageNum)
		{
		case 1:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_UP;
				break;
			default:
				break;
			}

			break;
		case 2:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_RIGHTUP;
				break;
			case 1:
				rotation = TOWARD_RIGHTDOWN;
				break;
			default:
				break;
			}
			break;
		case 3:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			case 0:
				rotation = TOWARD_UP;
				break;
			case 1:
				rotation = TOWARD_LEFT;
				break;
			case 2:
				rotation = TOWARD_RIGHT;
				break;
			case 3:
				rotation = TOWARD_DOWN;
				break;
			case 4:
				rotation = TOWARD_DOWN;
				break;
			case 5:
				rotation = TOWARD_LEFT;
				break;
			default:
				break;
			}
			break;
		case 4:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			default:
				break;
			}
			break;
		case 5:
			//��������E������֌������ĉ��Ԗڂ̑�C��
			switch (_cannonNum)
			{
			default:
				break;
			}
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	cannonModeFlg = false;
	animationCount = 0;
}

void Cannon::SetCannnonModeFlg(bool _cannnonModeFlg)
{
	cannonModeFlg = _cannnonModeFlg;
}

bool Cannon::GetCannonModeFlg()
{
	return cannonModeFlg;
}

void Cannon::SetPosFlg(bool _setPosFlg)
{
	setPosFlg = _setPosFlg;
}

bool Cannon::GetPosFlg()
{
	return setPosFlg;
}

void Cannon::SetNormalizedDirection(DirectX::XMFLOAT3 _normalizedDirection)
{
	normalizedDirection = _normalizedDirection;
}

DirectX::XMFLOAT3 Cannon::GetNormalizedDirection()
{
	return normalizedDirection;
}

int Cannon::GetRotateCannon()
{
	return rotation;
}

int Cannon::GetIndex()
{
	return index;
}

int Cannon::GetCannonNum()
{
	return cannonNum;
}

void Cannon::SetAnimationCount(int _count)
{
	animationCount = _count;
}

int Cannon::GetAnimationCount()
{
	return animationCount;
}

void Cannon::SetCollisionPos(float _x, float _y, float _z)
{
	collisionPos.x = _x;
	collisionPos.y = _y;
	collisionPos.z = _z;
}

DirectX::XMFLOAT3 Cannon::GetCollisionPos()
{
	return collisionPos;
}

void Cannon::SetCollisionScale(float _x, float _y, float _z)
{
	collisionScale.x = _x;
	collisionScale.y = _y;
	collisionScale.z = _z;
}

DirectX::XMFLOAT3 Cannon::GetCollisionScale()
{
	return collisionScale;
}
