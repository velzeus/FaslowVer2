#include"Word1_Stage.h"
using namespace std;

using json = nlohmann::json;

////jsonに変換するための関数
//void to_json(json& j, const VECTOR2& v)
//{
//	j = json{ {"x",v.x},{"y",v.y} };
//}
//
////jsonから変換するための関数
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

		///*vector<vector<VECTOR2>>*/ read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();


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

	center = ball.GetPos();//ボールの位置

	CheckSurroundingCollisions();//ボールの周囲８マスとブロックのあたり判定
	UpdateMoveDir();//ボールの向き変更
}

void World1_Stage::Update(void)
{
	ball.Move();//移動
	center = ball.GetPos();//ボールの位置を取得

	// **ボールがブロックの境界線上にいるかチェック**
	onGridX = (static_cast<int>(center.x) % BLOCKSIZE_X == 0);
	onGridY = (static_cast<int>(center.y) % BLOCKSIZE_Y == 0);

	// **ボールがブロックの区切りにいるときだけ当たり判定を実行**
	if (onGridX && onGridY)
	{
		CheckSurroundingCollisions();//あたり判定
		UpdateMoveDir();//ボールの方向を変える
		ball.Setborder();//端に行った時

	}
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

	ball.Draw();      //ボールを描画
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
	ball.Uninit();  //ボールを終了
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

//移動方向の変更
void World1_Stage::UpdateMoveDir()
{
	//最後に触れたブロックを保存　前＞右＞左
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



	if (hitBlockType[0] != EMPTY && hitBlockType[1] != EMPTY && hitBlockType[2] != EMPTY && hitBlockType[3] != EMPTY) {//四方にブロックがあれば
		// すべて true の場合の処理
		ball.SetMoveDir(STOP);
	}
	else
	{
		//跳ね返り
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


		if (hitBlockType[3] != EMPTY)//右にブロックがある
		{
			if (hitBlockType[3] == SLIDE || hitBlockType[2] == SLIDE)//右にスライドブロックがあれば
			{
				if (hitBlockType[0] == EMPTY)//前にブロックがなければ
				{
					prv_index = -1;
					ball.Move();
				}
			}

			if (hitBlockType[3] == SLIME)//右にスライドブロックがあれば
			{

				if (hitBlockType[0] != EMPTY)//前にブロックがある
				{
					if (hitBlockType[2] != EMPTY)//左にブロックがある
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
		else//右にブロックがない
		{

			bool _rotdir = ball.GetrotDir();
			//ボールが右回りなら
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
			else//ボールが左回りなら
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

//周囲8マスのあたり判定を取る
void World1_Stage::CheckSurroundingCollisions()
{
	// 周囲の8マスのあたり判定を更新
	surroundingBlocks.clear();
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//左上
	surroundingBlocks.emplace_back(center.x, center.y + BLOCKSIZE_Y);          //上
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y +BLOCKSIZE_Y);//右上
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y);          //左
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y);          //右
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//左下
	surroundingBlocks.emplace_back(center.x, center.y -BLOCKSIZE_Y);          //下
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//右下

	for (int i = 0; i < 4; i++)
	{
		hitIndex[i] = -1;
		hitFlgs[i] = false;
		hitSafe[i] = -1;
		hitBlockType[i] = EMPTY;
	}

	_moveDir = ball.GetMoveDir();

	// あたり判定の上下左右指定
	if (_moveDir == RIGHT) { hitIndex[0] = 4; hitIndex[1] = 3; hitIndex[2] = 1; hitIndex[3] = 6; } // front = 4, back = 3,left = 1,right = 6
	else if (_moveDir == LEFT) { hitIndex[0] = 3; hitIndex[1] = 4; hitIndex[2] = 6; hitIndex[3] = 1; }// front = 3, back = 4,left = 6,right = 1
	else if (_moveDir == UP) { hitIndex[0] = 1; hitIndex[1] = 6; hitIndex[2] = 3; hitIndex[3] = 4; }// front = 1, back = 6,left = 3,right = 4
	else if (_moveDir == DOWN) { hitIndex[0] = 6; hitIndex[1] = 1; hitIndex[2] = 4; hitIndex[3] = 3; }// front = 6, back = 1,left = 4,right = 3

	// **ボールの周囲8マスのブロックのみを探索**
	nearbyBlocks = GetNearbyBlocks(surroundingBlocks);

	//あたり判定　０：front　１：back　２：left　３：right
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

//１対１のあたり判定
bool World1_Stage::Collision(BlockBace* obj1/*ステージのブロック*/, const std::pair<float, float>& obj2)
{
	DirectX::XMFLOAT3 pos = obj1->GetPos();
	DirectX::XMFLOAT3 size = obj1->GetSize();

	float col_x, col_y;

	col_x = obj2.first;
	col_y = obj2.second;

	// 各辺の比較
	float block_left = pos.x - size.x / 2.0f;
	float block_right = pos.x + size.x / 2.0f;
	float block_top = pos.y - size.y / 2.0f;
	float block_bottom = pos.y + size.y / 2.0f;

	float col_left = col_x - BLOCKSIZE_X / 2.0f;
	float col_right = col_x + BLOCKSIZE_X / 2.0f;
	float col_top = col_y - BLOCKSIZE_Y / 2.0f;
	float col_bottom = col_y + BLOCKSIZE_Y / 2.0f;

	// **当たり判定**
	return (block_right > col_left &&
		block_left < col_right &&
		block_bottom > col_top &&
		block_top < col_bottom);
}

// **ボールの周囲 8 マスにあるブロックを取得**
std::vector<BlockBace*> World1_Stage::GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks)
{
	std::vector<BlockBace*> result;
	for (size_t i = 0; i < blocks.size(); i++) {
		DirectX::XMFLOAT3 blockPos = blocks[i].GetPos();
		for (size_t j = 0; j < surroundingBlocks.size(); j++) { // `surroundingBlocks` のサイズに基づいてループ
			if (std::abs(blockPos.x - surroundingBlocks[j].first) < 0.1f && // `.first` に変更
				std::abs(blockPos.y - surroundingBlocks[j].second) < 0.1f) { // `.second` に変更
				result.push_back(&blocks[i]);
				break;
			}
		}
	}
	return result;
}
