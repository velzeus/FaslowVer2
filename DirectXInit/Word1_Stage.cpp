#include"Word1_Stage.h"
using namespace std;

using json = nlohmann::json;

////json�ɕϊ����邽�߂̊֐�
//void to_json(json& j, const VECTOR2& v)
//{
//	j = json{ {"x",v.x},{"y",v.y} };
//}
//
////json����ϊ����邽�߂̊֐�
//void from_json(const json& j, VECTOR2& v)
//{
//	j.at("x").get_to(v.x);
//	j.at("y").get_to(v.y);
//}

World1_Stage::World1_Stage()
{

}

void World1_Stage::ReadFile(int _stageNumber)
{
	//�ǂݍ��ރt�@�C���̖��O���쐬
	string fileName;
	switch (_stageNumber)
	{
	case STAGE1:
		fileName = "StageFolder/Stage1-1.json";
		break;
	case STAGE2:
		fileName = "StageFolder/Stage1-2.json";
		break;
	case STAGE3:
		fileName = "StageFolder/Stage1-3.json";
		break;
	case STAGE4:
		fileName = "StageFolder/Stage1-4.json";
		break;
	case STAGE5:
		fileName = "StageFolder/Stage1-5.json";
		break;
	case 6:
		fileName = "StageFolder/StageInit.json";
		break;
	}

	ifstream fin(fileName.c_str());
	//�ǂݍ��݂Ɏ��s������G���[����\��
	if (fin.good())
	{
		//�t�@�C����ǂݍ���œ��e����ʂɕ\��
		json read_json;

		fin >> read_json;

		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		string stageName = read_json["stage_name"];


		/*vector<vector<int>>*/ read_gridStateList = read_json["blockState"].get<vector<vector<int>>>();

		///*vector<vector<VECTOR2>>*/ read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();


		//cout << "\n" << "�ǂݍ���" << endl;

		//for (int y = 0; y < STAGE_Y; y++)
		//{
		//	for (int x = 0; x < STAGE_X; x++)
		//	{
		//		//cout << read_blockPositionList[y][x].x<<","<< read_blockPositionList[y][x].y <<endl;
		//		
		//	}
		//	//cout << endl;
		//}

	}
	else
	{
		//cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << endl;
		//�ǂݍ��߂Ȃ������ꍇ�A�E�B���h�E��\��
		MessageBoxA(NULL, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�m�F", MB_OK);
	}
}

void World1_Stage::Init(HWND hWnd)
{
	//srand((unsigned)time(NULL));
	D3D_Create(hWnd);                //DirectX��������

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
			grids[x][y].Init(L"asset/block.png");//�u���b�N��������
			grids[x][y].SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);//�ʒu��ݒ�
			grids[x][y].SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);//�傫����ݒ�

			//�}�X�̏�Ԃ���
			gridData[x][y] = read_gridStateList[y][x];
		}
	}

	scoreboard.Init(L"asset/number.png", 10, 1);//���_�\����������
	scoreboard.SetPos(-145.0f, 200.0f, 0.0f);//�ʒu��ݒ�
	scoreboard.SetSize(40.0f, 40.0f, 0.0f);//�傫����ݒ�

	score = 0;//���_��������

	center = ball.GetPos();//�{�[���̈ʒu

	CheckSurroundingCollisions();//�{�[���̎��͂W�}�X�ƃu���b�N�̂����蔻��
	UpdateMoveDir();//�{�[���̌����ύX
}

void World1_Stage::Update(void)
{
	ball.Move();//�ړ�
	center = ball.GetPos();//�{�[���̈ʒu���擾

	// **�{�[�����u���b�N�̋��E����ɂ��邩�`�F�b�N**
	onGridX = (static_cast<int>(center.x) % BLOCKSIZE_X == 0);
	onGridY = (static_cast<int>(center.y) % BLOCKSIZE_Y == 0);

	// **�{�[�����u���b�N�̋�؂�ɂ���Ƃ����������蔻������s**
	if (onGridX && onGridY)
	{
		CheckSurroundingCollisions();//�����蔻��
		UpdateMoveDir();//�{�[���̕�����ς���
		ball.Setborder();//�[�ɍs������

	}
	//�F������
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			switch (gridData[x][y])
			{
			case NULLBLOCK://��
				grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 0.0f);
				break;
			case BOLL://�{�[��
				grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case GORL://�S�[��
				grids[x][y].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case COIN://�R�C��
				grids[x][y].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
				break;
			case STICKY_BLOCK://�S���u���b�N
				grids[x][y].SetColor(0.0f, 1.0f, 0.0f, 1.0f);
				break;
			}
		}
	}
}

void World1_Stage::Draw()
{
	D3D_StartRender();   //�`��J�n
	
	//�Q�[���{��
	background.Draw();  //�w�i��`��

	ball.Draw();      //�{�[����`��
	//�u���b�N��\��
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Draw();
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



	D3D_FinishRender();  //�`��I��
}

void World1_Stage::Uninit()
{
	player.Uninit(); //�v���C���[���I��
	background.Uninit();//�w�i���I��
	ball.Uninit();  //�{�[�����I��
	//�u���b�N���I��
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Uninit();
		}
	}
	scoreboard.Uninit();//�X�R�A�I��
	D3D_Release();   //DirectX���I��
}

//�ړ������̕ύX
void World1_Stage::UpdateMoveDir()
{
	//�Ō�ɐG�ꂽ�u���b�N��ۑ��@�O���E����
	if (hitBlockType[3] == SLIME)
	{
		prv_index = hitSafe[3];
	}
	else if (hitBlockType[2] == SLIME)
	{
		prv_index = hitSafe[2];
	}

	if (hitBlockType[0] == SLIME)
	{
		prv_index = hitSafe[0];
	}



	if (hitBlockType[0] != EMPTY && hitBlockType[1] != EMPTY && hitBlockType[2] != EMPTY && hitBlockType[3] != EMPTY) {//�l���Ƀu���b�N�������
		// ���ׂ� true �̏ꍇ�̏���
		ball.SetMoveDir(STOP);
	}
	else
	{
		//���˕Ԃ�
		if (hitBlockType[0] == SLIDE || hitBlockType[0] == UNBREAK)
		{
			ball.SetrotDir(ball.GetrotDir() == true ? false : true);
			if (_moveDir == RIGHT) { ball.SetMoveDir(LEFT); }
			else if (_moveDir == LEFT) { ball.SetMoveDir(RIGHT); }
			else if (_moveDir == UP) { ball.SetMoveDir(DOWN); }
			else if (_moveDir == DOWN) { ball.SetMoveDir(UP); }

			for (int i = 0; i < 4; i++)
			{
				hitSafe[i] = -1;
			}
			prv_index = -1;
			CheckSurroundingCollisions();
			UpdateMoveDir();
		}


		if (hitBlockType[3] != EMPTY)//�E�Ƀu���b�N������
		{
			if (hitBlockType[3] == SLIDE || hitBlockType[2] == SLIDE)//�E�ɃX���C�h�u���b�N�������
			{
				if (hitBlockType[0] == EMPTY)//�O�Ƀu���b�N���Ȃ����
				{
					prv_index = -1;
					ball.Move();
				}
			}

			if (hitBlockType[3] == SLIME)//�E�ɃX���C�h�u���b�N�������
			{

				if (hitBlockType[0] != EMPTY)//�O�Ƀu���b�N������
				{
					if (hitBlockType[2] != EMPTY)//���Ƀu���b�N������
					{
						ball.SetrotDir(ball.GetrotDir() == true ? false : true);
						if (_moveDir == RIGHT) { ball.SetMoveDir(LEFT); }
						else if (_moveDir == LEFT) { ball.SetMoveDir(RIGHT); }
						else if (_moveDir == UP) { ball.SetMoveDir(DOWN); }
						else if (_moveDir == DOWN) { ball.SetMoveDir(UP); }

						for (int i = 0; i < 4; i++)
						{
							hitSafe[i] = -1;
						}

						CheckSurroundingCollisions();
						UpdateMoveDir();
					}
					else if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.y > blocks[hitSafe[3]].GetPos().y) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.x > blocks[hitSafe[3]].GetPos().x) ? RIGHT : LEFT);
					}

				}
			}
		}
		else//�E�Ƀu���b�N���Ȃ�
		{

			bool _rotdir = ball.GetrotDir();
			//�{�[�����E���Ȃ�
			if (_rotdir)
			{
				if (prv_index >= 0 && hitBlockType[2] == EMPTY)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index].GetPos().x) ? DOWN : UP);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index].GetPos().y) ? RIGHT : LEFT);
					}
				}
			}
			else//�{�[���������Ȃ�
			{
				if (prv_index >= 0 && hitBlockType[2] == EMPTY)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index].GetPos().x) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index].GetPos().y) ? LEFT : RIGHT);
					}
				}
			}
		}
	}
}

//����8�}�X�̂����蔻������
void World1_Stage::CheckSurroundingCollisions()
{
	// ���͂�8�}�X�̂����蔻����X�V
	surroundingBlocks.clear();
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//����
	surroundingBlocks.emplace_back(center.x, center.y + BLOCKSIZE_Y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y +BLOCKSIZE_Y);//�E��
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y);          //�E
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//����
	surroundingBlocks.emplace_back(center.x, center.y -BLOCKSIZE_Y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//�E��

	for (int i = 0; i < 4; i++)
	{
		hitIndex[i] = -1;
		hitFlgs[i] = false;
		hitSafe[i] = -1;
		hitBlockType[i] = EMPTY;
	}

	_moveDir = ball.GetMoveDir();

	// �����蔻��̏㉺���E�w��
	if (_moveDir == RIGHT) { hitIndex[0] = 4; hitIndex[1] = 3; hitIndex[2] = 1; hitIndex[3] = 6; } // front = 4, back = 3,left = 1,right = 6
	else if (_moveDir == LEFT) { hitIndex[0] = 3; hitIndex[1] = 4; hitIndex[2] = 6; hitIndex[3] = 1; }// front = 3, back = 4,left = 6,right = 1
	else if (_moveDir == UP) { hitIndex[0] = 1; hitIndex[1] = 6; hitIndex[2] = 3; hitIndex[3] = 4; }// front = 1, back = 6,left = 3,right = 4
	else if (_moveDir == DOWN) { hitIndex[0] = 6; hitIndex[1] = 1; hitIndex[2] = 4; hitIndex[3] = 3; }// front = 6, back = 1,left = 4,right = 3

	// **�{�[���̎���8�}�X�̃u���b�N�݂̂�T��**
	nearbyBlocks = GetNearbyBlocks(surroundingBlocks);

	//�����蔻��@�O�Ffront�@�P�Fback�@�Q�Fleft�@�R�Fright
	for (int i = 0; i < 4; ++i) {
		if (hitIndex[i] != -1) {
			for (BlockBace* blk : nearbyBlocks) {
				if (Collision(blk, surroundingBlocks[hitIndex[i]])) {
					hitFlgs[i] = true;
					hitBlockType[i] = blk->GetBlockType();
					hitSafe[i] = blk->GetIndex();
					break;
				}
			}
		}
	}
}

//�P�΂P�̂����蔻��
bool World1_Stage::Collision(BlockBace* obj1/*�X�e�[�W�̃u���b�N*/, const std::pair<float, float>& obj2)
{
	DirectX::XMFLOAT3 pos = obj1->GetPos();
	DirectX::XMFLOAT3 size = obj1->GetSize();

	float col_x, col_y;

	col_x = obj2.first;
	col_y = obj2.second;

	// �e�ӂ̔�r
	float block_left = pos.x - size.x / 2.0f;
	float block_right = pos.x + size.x / 2.0f;
	float block_top = pos.y - size.y / 2.0f;
	float block_bottom = pos.y + size.y / 2.0f;

	float col_left = col_x - BLOCKSIZE_X / 2.0f;
	float col_right = col_x + BLOCKSIZE_X / 2.0f;
	float col_top = col_y - BLOCKSIZE_Y / 2.0f;
	float col_bottom = col_y + BLOCKSIZE_Y / 2.0f;

	// **�����蔻��**
	return (block_right > col_left &&
		block_left < col_right &&
		block_bottom > col_top &&
		block_top < col_bottom);
}

// **�{�[���̎��� 8 �}�X�ɂ���u���b�N���擾**
std::vector<BlockBace*> World1_Stage::GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks)
{
	std::vector<BlockBace*> result;
	for (size_t i = 0; i < blocks.size(); i++) {
		DirectX::XMFLOAT3 blockPos = blocks[i].GetPos();
		for (size_t j = 0; j < surroundingBlocks.size(); j++) { // `surroundingBlocks` �̃T�C�Y�Ɋ�Â��ă��[�v
			if (std::abs(blockPos.x - surroundingBlocks[j].first) < 0.1f && // `.first` �ɕύX
				std::abs(blockPos.y - surroundingBlocks[j].second) < 0.1f) { // `.second` �ɕύX
				result.push_back(&blocks[i]);
				break;
			}
		}
	}
	return result;
}
