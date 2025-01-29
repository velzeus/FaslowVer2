#include "ClassA.h"
#include"SceneFolder/Scenes/TitleScene.h"
#include"SceneFolder/Scenes/WorldSelectScene.h"

using namespace std;

using json = nlohmann::json;

//jsonに変換するための関数
void to_json(json& j, const VECTOR2& v)
{
	j = json{ {"x",v.x},{"y",v.y} };
}

//jsonから変換するための関数
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
	//ファイル読み込み
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
	//ワールド番号とステージ番号を文字列型に変換
	string number_world = to_string(manager->GetWorldNumber());
	string number_stage = to_string(manager->GetStageNumber());

	//読み込むファイルの名前を作成
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
	//読み込みに失敗したらエラー文を表示
	if (fin.good())
	{
		//ファイルを読み込んで内容を画面に表示
		json read_json;

		fin >> read_json;

		//読み込んだデータをそれぞれの変数に代入する
		string stageName = read_json["stage_name"];

		read_gridStateList = read_json["blockState"].get<vector<vector<int>>>();

		read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();

	}
	else
	{
		//cout << "ファイルの読み込みに失敗しました" << endl;
		//読み込めなかった場合、ウィンドウを表示
		MessageBoxA(NULL, "ファイルの読み込みに失敗しました", "確認", MB_OK);
	}
}
