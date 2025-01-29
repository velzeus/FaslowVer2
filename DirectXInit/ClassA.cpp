#include "ClassA.h"
#include"SceneFolder/Scenes/TitleScene.h"
#include"SceneFolder/Scenes/WorldSelectScene.h"

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

ClassA::ClassA() :Scene(SCENENAME::STAGE),manager(SceneManager::GetInstance())
{
}

ClassA::~ClassA()
{
}

int ClassA::Start()
{
	//�t�@�C���ǂݍ���
	ReadFile();



	return 0;
}

int ClassA::Update()
{
	//manager->AddScene(SCENENAME::TITLE, std::make_unique<TitleScene>());
	//manager->ChangeScene(TITLE);

	return 0;
}

int ClassA::Draw()
{
	return 0;
}

int ClassA::End()
{
	return 0;
}

void ClassA::ReadFile()
{
	//���[���h�ԍ��ƃX�e�[�W�ԍ��𕶎���^�ɕϊ�
	string number_world = to_string(manager->GetWorldNumber());
	string number_stage = to_string(manager->GetStageNumber());

	//�ǂݍ��ރt�@�C���̖��O���쐬
	string fileName = "StageFolder/Stage"+ number_world + "-" + number_stage+".json";

	/*switch (manager->GetStageNumber())
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
	}*/

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
}
