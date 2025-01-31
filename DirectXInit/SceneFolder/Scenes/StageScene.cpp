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

			if (gridData[x][y] == GORL)
			{
				gorl.Init(L"asset/Goll/TeamName/Team_Name.png");
				gorl.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
				gorl.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
				gorl.SetAngle(0.0f);
				gorl.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
		}
	}

	//�I�v�V�����{�^���@�@440
	optionButton.Init(L"asset/UI/back.png");
	optionButton.SetPos(-860.0f, 440.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

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
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (optionButton.GetPos().y - optionButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (optionButton.GetPos().y + optionButton.GetSize().y / 2))
			{
				//���肳��ĂȂ���Ԃɖ߂�
				SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//�Z���N�g�V�[���ɖ߂�
				SceneManager::GetInstance()->ChangeScene(SELECT);
			}

		}


		//�S�[����������

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

	optionButton.Draw();

	gorl.Draw();

	return 0;
}

int StageScene::End()
{
	//for (size_t i = 0; i < read_gridStateList.size(); i++)//�c����
	//{
	//	for (size_t j = 0; j < read_gridStateList[i].size(); j++)//������
	//	{
	//		delete blocks[j][i];
	//	}
	//}

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

	//for (size_t i = 0; i < read_gridStateList.size(); i++)//�c����
	//{
	//	for (size_t j = 0; j < read_gridStateList[i].size(); j++)//������
	//	{
	//		switch (read_gridStateList[i][j])
	//		{
	//		case STICKY_BLOCK: //�S���u���b�N

	//			blocks[j][i] = new BlockBace((STAGE_X * i + j), SLIME);

	//			break;
	//		case SLIP_BLOCK: //����u���b�N
	//			blocks[j][i] = new BlockBace((STAGE_X * i + j), SLIDE);
	//			break;
	//		//case UNBREAK_BLOCK: //�j��s�u���b�N
	//		//	blocks[j][i] = new BlockBace((STAGE_X * i + j), UNBREAK);
	//		//	break;
	//		defalt:  //���̑��̏��

	//			//blocks[j][i] = new BlockBace((STAGE_X * i + j), EMPTY);
	//			break;
	//		}
	//	}
	//}






}
