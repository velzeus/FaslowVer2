#include "StageScene.h"

using namespace std;

using json = nlohmann::json;

//json�ɕϊ����邽�߂̊֐�
void to_json(json& j, const VECTOR2& v)
{
	j = json{ {"x",v.x},{"y",v.y} };
}

//json����ϊ����邽�߂̊֐�
void from_json(const json& j, VECTOR2& v)
{
	j.at("x").get_to(v.x);
	j.at("y").get_to(v.y);
}


StageScene::StageScene()
	:Scene(SCENENAME::STAGE), manager(SceneManager::GetInstance())
{

}

StageScene::~StageScene()
{
}

int StageScene::Start()
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

			//�u���b�N
			for (int n = 0; n < blocks.size(); n++)
			{
				int idxBase = blocks[n]->GetIndex();
				int idx1 = idxBase / STAGE_X;	//Y
				int idx2 = idxBase % STAGE_X;	//X

				if (idx1 == y && idx2 == x)
				{
					//���W����
					blocks[n]->SetPos(read_blockPositionList[idx1][idx2].x, read_blockPositionList[idx1][idx2].y, 0.0f);
					
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

int StageScene::Update()
{
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
			case SLIP_BLOCK://����u���b�N
				grids[x][y].SetColor(0.0f, 1.0f, 1.0f, 1.0f);
				break;
			case UNBREAK_BLOCK://�j��s�u���b�N
				grids[x][y].SetColor(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			}
		}
	}

	//�߂�{�^��
	if (inputSystem->GetTrigger(MK_LEFT))
	{
		//�N���b�N���ꂽx���W�������ɂ�������
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (optionButton.GetPos().x - optionButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (optionButton.GetPos().x + optionButton.GetSize().x / 2))
		{
			//�}�E�X�J�[�\���̍��W�Ƃ̌덷�𖄂߂邽��10���炷
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2+10) * -1 > (optionButton.GetPos().y - optionButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2+10) * -1 < (optionButton.GetPos().y + optionButton.GetSize().y / 2))
			{
				//���肳��ĂȂ���Ԃɖ߂�
				SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//�Z���N�g�V�[���ɖ߂�
				SceneManager::GetInstance()->ChangeScene(SELECT);
			}

		}


		//�S�[����������(����m�F�p)

		//�N���b�N���ꂽx���W�������ɂ�������
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (gorl.GetPos().x - gorl.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (gorl.GetPos().x + gorl.GetSize().x / 2))
		{
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (gorl.GetPos().y - gorl.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (gorl.GetPos().y + gorl.GetSize().y / 2))
			{
				//���肳��ĂȂ���Ԃɖ߂�
				//SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				//SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//�Z���N�g�V�[���ɖ߂�
				SceneManager::GetInstance()->ChangeScene(RESULT);
			}

		}


		//���g���C�{�^��
		//�N���b�N���ꂽx���W�������ɂ�������
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (retryButton.GetPos().x - retryButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (retryButton.GetPos().x + retryButton.GetSize().x / 2))
		{
			//�^�X�N�o�[�����Ă���-��������40��ɂ��炵�čl����
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 + 40) * -1 > (retryButton.GetPos().y - retryButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 + 40) * -1 < (retryButton.GetPos().y + retryButton.GetSize().y / 2))
			{
				//���肳��ĂȂ���Ԃɖ߂�
				//SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				//SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//�X�e�[�W�V�[�����Ăђ���
				//SceneManager::GetInstance()->ChangeScene(STAGE);
				End();//vector�^�z������Z�b�g������
				Start();
			}

		}


	}

	return 0;
}

int StageScene::Draw()
{
	//�u���b�N��\��
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Draw();
		}
	}

	/*for (int i = 0; i < blocks.size(); i++)
	{
		
		blocks[i]->Draw();
	}*/

	optionButton.Draw();

	gorl.Draw();

	retryButton.Draw();

	return 0;
}

int StageScene::End()
{
	//vector�^�̔z������
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
	}

	blocks.clear();
	return 0;
}

void StageScene::ReadFile()
{
	//���[���h�ԍ��ƃX�e�[�W�ԍ��𕶎���^�ɕϊ�
	string number_world = to_string(manager->GetWorldNumber());
	string number_stage = to_string(manager->GetStageNumber());

	//�ǂݍ��ރt�@�C���̖��O���쐬
	string fileName = "StageFolder/New_Stage" + number_world + "-" + number_stage + ".json";
	//"StageFolder/New_Stage"

	ifstream fin(fileName.c_str());
	//�ǂݍ��݂Ɏ��s������G���[����\��
	if (fin.good())
	{
		//�t�@�C����ǂݍ���œ��e����ʂɕ\��
		json read_json;

		fin >> read_json;

		//�ǂݍ��񂾃f�[�^�����ꂼ��̕ϐ��ɑ������
		string stageName = read_json["stage_name"];

		read_gridStateList = read_json["blockState"].get<vector<vector<int>>>();

		read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();

	}
	else
	{
		//cout << "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���" << endl;
		//�ǂݍ��߂Ȃ������ꍇ�A�E�B���h�E��\��
		MessageBoxA(NULL, "�t�@�C���̓ǂݍ��݂Ɏ��s���܂���", "�m�F", MB_OK);
	}

	//BlockBase�ɑΉ�����`�ɕϊ�

	for (int i = 0; i < read_gridStateList.size(); i++)//�c����
	{
		for (int j = 0; j < read_gridStateList[i].size(); j++)//������
		{
			switch (read_gridStateList[i][j])
			{
			case STICKY_BLOCK: //�S���u���b�N

				blocks.emplace_back(new BlockBace((STAGE_X * i + j), STICKY_BLOCK));

				break;
			case SLIP_BLOCK: //����u���b�N
				blocks.emplace_back(new BlockBace((STAGE_X * i + j), SLIP_BLOCK));
				break;
			//case UNBREAK_BLOCK: //�j��s�u���b�N
			//	blocks[j][i] = new BlockBace((STAGE_X * i + j), UNBREAK);
			//	break;
			defalt:  //���̑��̏��

				//blocks[j][i] = new BlockBace((STAGE_X * i + j), EMPTY);
				break;
			}
		}
	}






}

//�ړ������̕ύX
void StageScene::UpdateMoveDir()
{

	if (hitBlockType[0] == GORL)
	{
		cout << "go-ru" << endl;
	}
	//�Ō�ɐG�ꂽ�u���b�N��ۑ��@�O���E����
	if (hitBlockType[3] == STICKY_BLOCK)
	{
		prv_index = hitSafe[3];
	}
	else if (hitBlockType[2] == STICKY_BLOCK)
	{
		prv_index = hitSafe[2];
	}

	if (hitBlockType[0] == STICKY_BLOCK)
	{
		prv_index = hitSafe[0];
	}



	if (hitBlockType[0] != NULLBLOCK && hitBlockType[1] != NULLBLOCK && hitBlockType[2] != NULLBLOCK && hitBlockType[3] != NULLBLOCK) {//�l���Ƀu���b�N�������
		// ���ׂ� true �̏ꍇ�̏���
		ball.SetMoveDir(STOP);
	}
	else
	{
		//���˕Ԃ�
		if (hitBlockType[0] == SLIP_BLOCK || hitBlockType[0] == UNBREAK_BLOCK)
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


		if (hitBlockType[3] != NULLBLOCK)//�E�Ƀu���b�N������
		{
			if (hitBlockType[3] == SLIP_BLOCK || hitBlockType[2] == SLIP_BLOCK)//�E�ɃX���C�h�u���b�N�������
			{
				if (hitBlockType[0] == NULLBLOCK)//�O�Ƀu���b�N���Ȃ����
				{
					prv_index = -1;
					ball.Move();
				}
			}

			if (hitBlockType[3] == STICKY_BLOCK)//�E�ɃX���C�h�u���b�N�������
			{

				if (hitBlockType[0] != NULLBLOCK)//�O�Ƀu���b�N������
				{
					if (hitBlockType[2] != NULLBLOCK)//���Ƀu���b�N������
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
						ball.SetMoveDir((center.y > blocks[hitSafe[3]]->GetPos().y) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.x > blocks[hitSafe[3]]->GetPos().x) ? RIGHT : LEFT);
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
				if (prv_index >= 0 && hitBlockType[2] == NULLBLOCK)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index]->GetPos().x) ? DOWN : UP);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index]->GetPos().y) ? RIGHT : LEFT);
					}
				}
			}
			else//�{�[���������Ȃ�
			{
				if (prv_index >= 0 && hitBlockType[2] == NULLBLOCK)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index]->GetPos().x) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index]->GetPos().y) ? LEFT : RIGHT);
					}
				}
			}
		}
	}
}

//����8�}�X�̂����蔻������
void StageScene::CheckSurroundingCollisions()
{
	// ���͂�8�}�X�̂����蔻����X�V
	surroundingBlocks.clear();
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//����
	surroundingBlocks.emplace_back(center.x, center.y + BLOCKSIZE_Y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//�E��
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y);          //�E
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//����
	surroundingBlocks.emplace_back(center.x, center.y - BLOCKSIZE_Y);          //��
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//�E��

	for (int i = 0; i < 4; i++)
	{
		hitIndex[i] = -1;
		hitFlgs[i] = false;
		hitSafe[i] = -1;
		hitBlockType[i] = NULLBLOCK;
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
bool StageScene::Collision(BlockBace* obj1/*�X�e�[�W�̃u���b�N*/, const std::pair<float, float>& obj2)
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
std::vector<BlockBace*> StageScene::GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks)
{
	std::vector<BlockBace*> result;
	for (size_t i = 0; i < blocks.size(); i++) {
		DirectX::XMFLOAT3 blockPos = blocks[i]->GetPos();
		for (size_t j = 0; j < surroundingBlocks.size(); j++) { // `surroundingBlocks` �̃T�C�Y�Ɋ�Â��ă��[�v
			if (std::abs(blockPos.x - surroundingBlocks[j].first) < 0.1f && // `.first` �ɕύX
				std::abs(blockPos.y - surroundingBlocks[j].second) < 0.1f) { // `.second` �ɕύX
				result.push_back(blocks[i]);
				break;
			}
		}
	}
	return result;
}
