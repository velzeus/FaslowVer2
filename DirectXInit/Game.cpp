#include "Game.h"
#include<time.h>

void Game::Init(HWND hWnd)
{
	srand((unsigned)time(NULL));
	D3D_Create(hWnd);                //DirectX��������

	sound.Init();//�T�E���h��������
	sound.Play(SOUND_LABEL_BGM000);//BGM���Đ�
	player.Init(L"asset/char01.png", 3, 4);     //�v���C���[��������
	player.SetPos(0.0f, 0.0f, 0.0f);   //�ʒu��ݒ�
	player.SetSize(200.0f, 200.0f, 0.0f);//�傫����ݒ�
	player.SetAngle(0.0f);               //�p�x��ݒ�
	player.SetColor(1.0f, 1.0f, 1.0f, 1.0f);//�F��ݒ�

	background.Init(L"asset/back_img_01.png"); //�w�i��������
	background.SetPos(0.0f, 0.0f, 0.0f);       //�ʒu��ݒ�
	background.SetSize(640.0f, 480.0f, 0.0f);  //�傫����ݒ�
	background.SetAngle(0.0f);                 //�p�x��ݒ�

	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			blocks[x][y].Init(L"asset/block.png");//�u���b�N��������
			blocks[x][y].SetPos(BLOCK_SIZE * (x - STAGE_X / 2), BLOCK_SIZE * (y - STAGE_Y / 2), 0.0f);//�ʒu��ݒ�
			blocks[x][y].SetSize(BLOCK_SIZE, BLOCK_SIZE, 0.0f);//�傫����ݒ�
		}
	}

	scoreboard.Init(L"asset/number.png", 10, 1);//���_�\����������
	scoreboard.SetPos(-145.0f, 200.0f, 0.0f);//�ʒu��ݒ�
	scoreboard.SetSize(40.0f, 40.0f, 0.0f);//�傫����ݒ�

	score = 0;//���_��������

	title.Init(L"asset/apple.jpg", 10, 1);//���_�\����������
	title.SetPos(0.0f, 0.0f, 0.0f);//�ʒu��ݒ�
	title.SetSize(640.0f, 480.0f, 0.0f);//�傫����ݒ�

	gametitle.Init(L"asset/title.png");//�^�C�g����ʕ`��
	gametitle.SetPos(0.0f, 0.0f, 0.0f);       //�ʒu��ݒ�
	gametitle.SetSize(640.0f, 480.0f, 0.0f);  //�傫����ݒ�
	gametitle.SetAngle(0.0f);                 //�p�x��ݒ�

	scene = 0;
}

void Game::Update(void)
{
	input.Update();

	switch (scene)
	{
	case 0://�^�C�g�����
		//�L�[���͂Ŗ{�҂�
		if (input.GetKeyTrigger(VK_A))
		{
			scene = 1;

			//data�z���������
			for (int x = 0; x < STAGE_X; x ++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					data[x][y] = 0;
				}
			}
			state = 0;//�Q�[���̏�Ԃ�������
			score = 0;//���_��������
		}
		break;

	case 1://�Q�[���{��
		//�Q�[���I�[�o�[�Ȃ�Q�[���̐i�s���~�߂�
		if (state == 3) { scene = 0; }

		//�V���Ƀe�g���~�m���o��������
		if (state == 0)
		{
			//�Q�[���̏�Ԃ��u�P�F�������v�ɕύX
			state = 1;


			TetrominoType = rand() % 7;//�O�`�U�������_���Ŏ擾

			switch (TetrominoType)
			{
			case 0://����
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[7][19] = 2;
				break;

			case 1://�l�p
				data[5][20] = 2;
				data[6][20] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 2://S��
				data[4][19] = 2;
				data[5][19] = 2;
				data[5][20] = 2;
				data[6][20] = 2;
				break;

			case 3://�tS��
				data[4][20] = 2;
				data[5][20] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 4://�tL�p
				data[4][20] = 2;
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 5://L��
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[6][20] = 2;
				break;

			case 6://T��
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[5][20] = 2;
				break;
			}
			count = 0;

			TetrominoDirection = 0;//���������Z�b�g


		}

		//��]
		if (input.GetKeyTrigger(VK_W))
		{
			//������ύX����
			int newDirection = TetrominoDirection + 1;
			if (newDirection > 3) { newDirection = 0; }

			//��_�𒲂ׂ�
			int baseX = -1, baseY = -1;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y; y++)
				{
					if (data[x][y] == 2)
					{
						for (int tx = 0; tx < 4; tx++)
						{
							for (int ty = 0; ty < 4; ty++)
							{
								if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2)
								{
									baseX = x - tx;
									baseY = y - ty;
									break;
								}
							}
							if (baseX >= 0) { break; }
						}
						break;
					}
				}
				if (baseX >= 0) { break; }
			}

			//��]���\�����ׂ�
			bool ngFg = false;
			for (int tx = 0; tx < 4; tx++)
			{
				for (int ty = 0; ty < 4; ty++)
				{
					if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2 &&
						(data[baseX + tx][baseY + ty] == 1 || baseX + tx > STAGE_X - 1 || baseY + ty > STAGE_Y - 1 || baseX + tx < 0 || baseY + ty < 0))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//��]���\�Ȃ�
			if (ngFg == false)
			{
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2) { data[x][y] = 0; }
					}
				}
				for (int tx = 0; tx < 4; tx++)
				{
					for (int ty = 0; ty < 4; ty++)
					{
						if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2)
						{
							data[baseX + tx][baseY + ty] = 2;
						}
					}
				}
				TetrominoDirection = newDirection;//�������X�V
			}
		}

		//���ړ�
		if (input.GetKeyTrigger(VK_A))
		{
			//���ړ����\�����ׂ�
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++) {
				for (int y = 0; y < STAGE_Y + 3; y++) {
					if (data[x][y] == 2 && (x == 0 || data[x - 1][y] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//���ړ����\�Ȃ�
			if (ngFg == false)
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x - 1][y] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		//�E�ړ�
		if (input.GetKeyTrigger(VK_D))
		{
			//�E�����\�����ׂ�
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[x][y] == 2 && (x == STAGE_X - 1 || data[x + 1][y] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//�E�ړ����\�Ȃ�
			if (ngFg == false)
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x + 1][y] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		if (input.GetKeyPress(VK_S))
		{
			count = 31;
		}

		count++;
		//��������
		if (count > 30)
		{
			count = 0;

			//�����Ă���΁A���̍s����̍s���P�s���Â��炷
			if (state == 2)
			{
				//�P�s�������s���Ȃ����`�F�b�N����
				int cnt = 0;//�������񐔂��J�E���g����ϐ�
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[0][y] == 3)
					{
						for (int ty = y + 1; ty < STAGE_Y + 3; ty++)
						{
							for (int tx = 0; tx < STAGE_X; tx++)
							{
								data[tx][ty - 1] = data[tx][ty];
							}
						}
						y--;
						cnt++;
					}
				}

				//���_�����Z����
				switch (cnt)
				{
				case 1:score += 100; break;//�V���O��(�P������j
				case 2:score += 300; break;//�_�u���i�Q������j
				case 3:score += 500; break;//�g���v���i�R������j
				case 4:score += 800; break;//�e�g���X�i�S������j
				}
				//�Q�[���̏�Ԃ��u�O�F����������̂��Ȃ���ԁv�ɕύX
				state = 0;
			}

			//���Ƃ����Ƃ��\�����ׂ�
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[x][y] == 2 && (y == 0 || data[x][y - 1] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true)
				{
					break;
				}
			}

			//���Ƃ����Ƃ��s�\�Ȃ�
			if (ngFg == true)
			{
				//���n
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							data[x][y] = 1;//�Q(������)�@����@�P(���n��)�@�ɕύX
						}
					}
				}

				//�Q�[���̏�Ԃ��u�O�F����������̂��Ȃ���ԁv�ɕύX
				state = 0;


				//�P�s�������s���Ȃ����`�F�b�N����
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					bool completeFg = true;
					for (int x = 0; x < STAGE_X; x++)
					{
						if (data[x][y] == 0)
						{
							completeFg = false;
							break;
						}
					}

					//�����Ă���ΐF�𒅂���
					if (completeFg == true)
					{
						for (int x = 0; x < STAGE_X; x++)
						{
							data[x][y] = 3;
						}

						//�Q�[���̏�Ԃ��u�Q�F��������ԁv�ɕύX
						state = 2;
					}
				}

				//�Q�[���I�[�o�[�ɂȂ��Ă��Ȃ����`�F�b�N����
				for (int x = 0; x < STAGE_X; x++)//��ԏ�̗���`�F�b�N
				{
					if (data[x][STAGE_Y - 1] == 1)
					{

						//�e�g���~�m�̐F��ς���
						for (int tx = 0; tx < STAGE_X; tx++)
						{
							for (int ty = 0; ty < STAGE_Y + 3; ty++)
							{
								if (data[tx][ty] == 1)
								{
									data[tx][ty] = 4;
								}
							}
						}

						//�Q�[���̏�Ԃ��u�R�F�Q�[���I�[�o�[�v�ɕύX
						state = 3;
						break;
					}
				}
			}
			//���Ƃ����Ƃ��\�Ȃ�
			else
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x][y - 1] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}

				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		

		//����
		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (data[x][y] == 2)
				{
					check++;
				}
				else
				{
					break;
				}
				if (check == STAGE_X)
				{

				}
			}
		}

		//�F������
		for (int x = 0; x < STAGE_X; x++)
		{
			for (int y = 0; y < STAGE_Y; y++)
			{
				switch (data[x][y])
				{
				case 0://��
					blocks[x][y].SetColor(1.0f, 1.0f, 1.0f, 0.2f);
					break;
				case 1://���n���Ă���e�g���~�m
					blocks[x][y].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case 2://�����Ă��Ă���e�g���~�m
					blocks[x][y].SetColor(1.0f, 0.8f, 0.8f, 1.0f);
					break;
				case 3://�������e�g���~�m
					blocks[x][y].SetColor(0.4f, 0.4f, 1.0f, 1.0f);
					break;
				case 4://�Q�[���I�[�o�[��
					blocks[x][y].SetColor(1.0f, 0.2f, 0.2f, 1.0f);
					break;
				}
			}
		}

		break;
	}

	
}

void Game::Draw(void)
{
	D3D_StartRender();   //�`��J�n
	switch (scene)
	{
	case 0://�^�C�g�����
		gametitle.Draw();//�^�C�g����`��
		break;

	case 1://�Q�[���{��
		background.Draw();  //�w�i��`��

		//�u���b�N��\��
		for (int x = 0; x < STAGE_X; x++)
		{
			for (int y = 0; y < STAGE_Y; y++)
			{
				blocks[x][y].Draw();
			}
		}

		//�X�R�A�\��
		DirectX::XMFLOAT3 pos = scoreboard.GetPos();
		DirectX::XMFLOAT3 size = scoreboard.GetSize();
		int keta = 0;
		do
		{
			scoreboard.numU = score % (int)pow(10, keta + 1) / (int)pow(10, keta);//�P����؂�o��
			scoreboard.SetPos(pos.x - size.x * keta, pos.y, pos.z);//�ʒu��ݒ�
			scoreboard.Draw();//�X�R�A��`��
			keta++;
		} while (score >= (int)pow(10, keta));
		scoreboard.SetPos(pos.x, pos.y, pos.z);//�ʒu�����ɖ߂�
		break;
	}
	
	D3D_FinishRender();  //�`��I��
}

void Game::Uninit(void)
{
	player.Uninit(); //�v���C���[���I��
	background.Uninit();//�w�i���I��

	//�u���b�N���I��
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			blocks[x][y].Uninit();
		}
	}
	scoreboard.Uninit();//�X�R�A�I��
	sound.Uninit();//�T�E���h���I��
	title.Uninit();//�^�C�g�����I��
	gametitle.Uninit();
	D3D_Release();   //DirectX���I��
}