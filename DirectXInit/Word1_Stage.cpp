#include"Word1_Stage.h"
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

World1_Stage::World1_Stage()
{

}

void World1_Stage::ReadFile(int _stageNumber)
{
	//読み込むファイルの名前を作成
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
	//読み込みに失敗したらエラー文を表示
	if (fin.good())
	{
		//ファイルを読み込んで内容を画面に表示
		json read_json;

		fin >> read_json;

		//読み込んだデータをそれぞれの変数に代入する
		string stageName = read_json["stage_name"];


		/*vector<vector<int>>*/ read_gridStateList = read_json["blockState"].get<vector<vector<int>>>();

		/*vector<vector<VECTOR2>>*/ read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();


		//cout << "\n" << "読み込み" << endl;

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
		//cout << "ファイルの読み込みに失敗しました" << endl;
		//読み込めなかった場合、ウィンドウを表示
		MessageBoxA(NULL, "ファイルの読み込みに失敗しました", "確認", MB_OK);
	}
}

void World1_Stage::Init(HWND hWnd)
{
	//srand((unsigned)time(NULL));
	D3D_Create(hWnd);                //DirectXを初期化

	player.Init(L"asset/char01.png", 3, 4);     //プレイヤーを初期化
	player.SetPos(0.0f, 0.0f, 0.0f);   //位置を設定
	player.SetSize(200.0f, 200.0f, 0.0f);//大きさを設定
	player.SetAngle(0.0f);               //角度を設定
	player.SetColor(1.0f, 1.0f, 1.0f, 1.0f);//色を設定

	background.Init(L"asset/back_img_01.png"); //背景を初期化
	background.SetPos(0.0f, 0.0f, 0.0f);       //位置を設定
	background.SetSize(640.0f, 480.0f, 0.0f);  //大きさを設定
	background.SetAngle(0.0f);                 //角度を設定

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

	scoreboard.Init(L"asset/number.png", 10, 1);//得点表示を初期化
	scoreboard.SetPos(-145.0f, 200.0f, 0.0f);//位置を設定
	scoreboard.SetSize(40.0f, 40.0f, 0.0f);//大きさを設定

	score = 0;//得点を初期化


}

void World1_Stage::Update(void)
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
			}
		}
	}
}

void World1_Stage::Draw()
{
	D3D_StartRender();   //描画開始
	
	//ゲーム本編
	background.Draw();  //背景を描画

	//ブロックを表示
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Draw();
		}
	}

	//スコア表示
	DirectX::XMFLOAT3 pos = scoreboard.GetPos();
	DirectX::XMFLOAT3 size = scoreboard.GetSize();
	int keta = 0;
	do
	{
		scoreboard.numU = score % (int)pow(10, keta + 1) / (int)pow(10, keta);//１桁を切り出す
		scoreboard.SetPos(pos.x - size.x * keta, pos.y, pos.z);//位置を設定
		scoreboard.Draw();//スコアを描画
		keta++;
	} while (score >= (int)pow(10, keta));
	scoreboard.SetPos(pos.x, pos.y, pos.z);//位置を元に戻す



	D3D_FinishRender();  //描画終了
}

void World1_Stage::Uninit()
{
	player.Uninit(); //プレイヤーを終了
	background.Uninit();//背景を終了

	//ブロックを終了
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			grids[x][y].Uninit();
		}
	}
	scoreboard.Uninit();//スコア終了
	D3D_Release();   //DirectXを終了
}
