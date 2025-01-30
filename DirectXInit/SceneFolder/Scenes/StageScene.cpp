#include "StageScene.h"

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


StageScene::StageScene()
	:Scene(SCENENAME::STAGE), manager(SceneManager::GetInstance())
{

}

StageScene::~StageScene()
{
}

int StageScene::Start()
{
	mouseInput = MouseInput::GetInstance();

	//ファイル読み込み
	ReadFile();

	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Init(L"asset/block.png");//ブロックを初期化
			grids[x][y].SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);//位置を設定
			grids[x][y].SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);//大きさを設定

			//マスの状態を代入
			gridData[x][y] = read_gridStateList[y][x];
		}
	}

	//オプションボタン　　440
	optionButton.Init(L"asset/block.png");
	optionButton.SetPos(-860.0f, 340.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(0.0f, 0.0f, 0.0f, 1.0f);

	return 0;
}

int StageScene::Update()
{
	//色をつける
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			switch (gridData[x][y])
			{
			case NULLBLOCK://空白
				grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 0.0f);
				break;
			case BOLL://ボール
				grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				break;
			case GORL://ゴール
				grids[x][y].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
				break;
			case COIN://コイン
				grids[x][y].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
				break;
			case STICKY_BLOCK://粘着ブロック
				grids[x][y].SetColor(0.0f, 1.0f, 0.0f, 1.0f);
				break;
			case SLIP_BLOCK://滑るブロック
				grids[x][y].SetColor(0.0f, 1.0f, 1.0f, 1.0f);
				break;
			case UNBREAK_BLOCK://破壊不可ブロック
				grids[x][y].SetColor(0.0f, 0.0f, 0.0f, 1.0f);
				break;
			}
		}
	}

	//戻るボタン
	if (mouseInput->IsLeftButtonDown())
	{
		//クリックされたx座標が内側にあったら
		if (mouseInput->GetClickPosition().x - SCREEN_WIDTH / 2 > (optionButton.GetPos().x - optionButton.GetSize().x / 2) &&
			mouseInput->GetClickPosition().x - SCREEN_WIDTH / 2 < (optionButton.GetPos().x + optionButton.GetSize().x / 2))
		{
			//
			if ((mouseInput->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (optionButton.GetPos().y - optionButton.GetSize().y / 2) &&
				(mouseInput->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (optionButton.GetPos().y + optionButton.GetSize().y / 2))
			{
				//決定されてない状態に戻す
				SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//セレクトシーンに戻る
				SceneManager::GetInstance()->ChangeScene(SELECT);
			}

		}

	}

	return 0;
}

int StageScene::Draw()
{
	//ブロックを表示
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Draw();
		}
	}

	optionButton.Draw();

	return 0;
}

int StageScene::End()
{
	return 0;
}

void StageScene::ReadFile()
{
	//ワールド番号とステージ番号を文字列型に変換
	string number_world = to_string(manager->GetWorldNumber());
	string number_stage = to_string(manager->GetStageNumber());

	//読み込むファイルの名前を作成
	string fileName = "StageFolder/Stage" + number_world + "-" + number_stage + ".json";
	//"StageFolder/New_Stage"

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
