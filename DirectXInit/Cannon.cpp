#include "Cannon.h"

Cannon::Cannon(int _worldNum, int _stageNum, int _index)
{
	//ワールド、ステージ、大砲の番号ごとに直接処理を行う
	//ない場所は何もしない
	index = _index;
	//大砲があるワールドだけを処理する
	switch (_worldNum)
	{
	case 3:
		//ステージごとに処理をする
		switch (_stageNum)
		{
		case 1:
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
			{
			case 0:
				rotation = TOWARD_RIGHTUP;
				break;
			default:
				break;
			}
			break;
		case 4:
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
		//ステージごとに処理をする
		switch (_stageNum)
		{
		case 1:
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
			{
			case 0:
				rotation = TOWARD_UP;
				break;
			default:
				break;
			}

			break;
		case 2:
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
			{
			default:
				break;
			}
			break;
		case 5:
			//左下から右上方向へ向かって何番目の大砲か
			switch (_index)
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
}

void Cannon::SetCannnonModeFlg(bool _cannnonModeFlg)
{
	cannonModeFlg = _cannnonModeFlg;
}

bool Cannon::GetCannonModeFlg()
{
	return cannonModeFlg;
}

void Cannon::SetNormalizedDirection(DirectX::XMFLOAT3 _normalizedDirection)
{
	normalizedDirection = _normalizedDirection;
}

DirectX::XMFLOAT3 Cannon::GetNormalizedDirection()
{
	return normalizedDirection;
}
