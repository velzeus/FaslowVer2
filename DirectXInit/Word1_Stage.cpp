#include"Word1_Stage.h"
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

		/*vector<vector<VECTOR2>>*/ read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();


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


}

void World1_Stage::Update(void)
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
			}
		}
	}
}

void World1_Stage::Draw()
{
	D3D_StartRender();   //�`��J�n
	
	//�Q�[���{��
	background.Draw();  //�w�i��`��

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
