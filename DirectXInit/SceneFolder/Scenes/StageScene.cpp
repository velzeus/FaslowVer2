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
	//inputSystem = MouseInput::GetInstance();

	inputSystem = TS::TS_InputSystem::GetInstance();

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

	//オプションボタン　　440
	optionButton.Init(L"asset/UI/back.png");
	optionButton.SetPos(-860.0f, 440.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

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
	if (inputSystem->GetTrigger(MK_LEFT))
	{
		//クリックされたx座標が内側にあったら
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (optionButton.GetPos().x - optionButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (optionButton.GetPos().x + optionButton.GetSize().x / 2))
		{
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (optionButton.GetPos().y - optionButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (optionButton.GetPos().y + optionButton.GetSize().y / 2))
			{
				//決定されてない状態に戻す
				SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//セレクトシーンに戻る
				SceneManager::GetInstance()->ChangeScene(SELECT);
			}

		}


		//ゴールした判定

		//クリックされたx座標が内側にあったら
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (gorl.GetPos().x - gorl.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (gorl.GetPos().x + gorl.GetSize().x / 2))
		{
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (gorl.GetPos().y - gorl.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (gorl.GetPos().y + gorl.GetSize().y / 2))
			{
				//決定されてない状態に戻す
				//SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				//SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//セレクトシーンに戻る
				SceneManager::GetInstance()->ChangeScene(RESULT);
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

	gorl.Draw();

	return 0;
}

int StageScene::End()
{
	//for (size_t i = 0; i < read_gridStateList.size(); i++)//縦方向
	//{
	//	for (size_t j = 0; j < read_gridStateList[i].size(); j++)//横方向
	//	{
	//		delete blocks[j][i];
	//	}
	//}

	return 0;
}

void StageScene::ReadFile()
{
	//ワールド番号とステージ番号を文字列型に変換
	string number_world = to_string(manager->GetWorldNumber());
	string number_stage = to_string(manager->GetStageNumber());

	//読み込むファイルの名前を作成
	string fileName = "StageFolder/New_Stage" + number_world + "-" + number_stage + ".json";
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

	//BlockBaseに対応する形に変換

	//for (size_t i = 0; i < read_gridStateList.size(); i++)//縦方向
	//{
	//	for (size_t j = 0; j < read_gridStateList[i].size(); j++)//横方向
	//	{
	//		switch (read_gridStateList[i][j])
	//		{
	//		case STICKY_BLOCK: //粘着ブロック

	//			blocks[j][i] = new BlockBace((STAGE_X * i + j), SLIME);

	//			break;
	//		case SLIP_BLOCK: //滑るブロック
	//			blocks[j][i] = new BlockBace((STAGE_X * i + j), SLIDE);
	//			break;
	//		//case UNBREAK_BLOCK: //破壊不可ブロック
	//		//	blocks[j][i] = new BlockBace((STAGE_X * i + j), UNBREAK);
	//		//	break;
	//		defalt:  //その他の状態

	//			//blocks[j][i] = new BlockBace((STAGE_X * i + j), EMPTY);
	//			break;
	//		}
	//	}
	//}






}
