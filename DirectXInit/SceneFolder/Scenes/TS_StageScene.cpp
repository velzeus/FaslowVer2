#include"TS_StageScene.h"
#include<fstream>

int TS_StageScene::Start()
{
	//inputSystem = MouseInput::GetInstance();

	inputSystem = TS::TS_InputSystem::GetInstance();

	//�t�@�C���ǂݍ���
	ReadFile();

	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Init(L"asset/block.png");//�u���b�N��������
			grids[x][y].SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);//�ʒu��ݒ�
			grids[x][y].SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);//�傫����ݒ�

			//�}�X�̏�Ԃ���
			gridData[x][y] = read_gridStateList[y][x];

			//�S�[����ʌɍ��
			if (gridData[x][y] == GORL)
			{
				gorl.Init(L"asset/Goll/TeamName/Team_Name.png");
				gorl.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
				gorl.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
				gorl.SetAngle(0.0f);
				gorl.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (gridData[x][y] == BOLL) {
				ball.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0);
				gridData[x][y] = NULLBLOCK;
			}

			//�u���b�N
			for (int n = 0; n < blocks.size(); n++)
			{
				int idxBase = blocks[n]->GetIndex();
				int idx1 = idxBase / STAGE_X;	//Y
				int idx2 = idxBase % STAGE_X;	//X

				if ((idx1 == y && idx2 == x) && idxBase > blocks.size())
				{
					//���W����
					blocks[n]->Init(L"asset/Blocks/STICKY_BLOCK_GREEN.png");
					blocks[n]->SetPos(read_blockPositionList[idx1][idx2].x, read_blockPositionList[idx1][idx2].y, 0.0f);
					blocks[n]->SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
					blocks[n]->SetIndex(n);

					//���W�m�F�p
					/*blocks[n]->Init(L"asset/block.png");
					blocks[n]->SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
					blocks[n]->SetColor(1, 1, 1, 1);*/
					break;
				}
			}






		}
	}

	//�{�[���̌�����ݒ�
	center = ball.GetPos();
	CheckSurroundingCollisions();
	UpdateMoveDir();
	v = ball.GetPos();

	//�I�v�V�����{�^���@�@440
	optionButton.Init(L"asset/UI/back.png");
	optionButton.SetPos(-860.0f, 440.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//���g���C�{�^��
	retryButton.Init(L"asset/UI/�n���o�[�K�[�A�C�R��100x100.png");
	//retryButton.Init(L"asset/block.png");
	retryButton.SetPos(-860.0f, -440.0f, 0.0f);
	retryButton.SetSize(50.0f, 50.0f, 0);
	retryButton.SetAngle(0);
	retryButton.SetColor(1, 1, 1, 1);


	return 0;
}

int TS_StageScene::Update()
{
	return 0;
}

int TS_StageScene::Draw()
{
	return 0;
}

int TS_StageScene::End()
{
	return 0;
}
