#include"TS_StageScene.h"
#include<fstream>

int TS_StageScene::Start()
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

			//ゴールを別個に作る
			if (gridData[x][y] == GORL)
			{
				gorl.Init(L"asset/Goll/TeamName/Team_Name.png");
				gorl.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
				gorl.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
				gorl.SetAngle(0.0f);
				gorl.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			}
			else if (gridData[x][y] == BOLL) {
				ball.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0);
				gridData[x][y] = NULLBLOCK;
			}

			//ブロック
			for (int n = 0; n < blocks.size(); n++)
			{
				int idxBase = blocks[n]->GetIndex();
				int idx1 = idxBase / STAGE_X;	//Y
				int idx2 = idxBase % STAGE_X;	//X

				if ((idx1 == y && idx2 == x) && idxBase > blocks.size())
				{
					//座標を代入
					blocks[n]->Init(L"asset/Blocks/STICKY_BLOCK_GREEN.png");
					blocks[n]->SetPos(read_blockPositionList[idx1][idx2].x, read_blockPositionList[idx1][idx2].y, 0.0f);
					blocks[n]->SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
					blocks[n]->SetIndex(n);

					//座標確認用
					/*blocks[n]->Init(L"asset/block.png");
					blocks[n]->SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
					blocks[n]->SetColor(1, 1, 1, 1);*/
					break;
				}
			}






		}
	}

	//ボールの向きを設定
	center = ball.GetPos();
	CheckSurroundingCollisions();
	UpdateMoveDir();
	v = ball.GetPos();

	//オプションボタン　　440
	optionButton.Init(L"asset/UI/back.png");
	optionButton.SetPos(-860.0f, 440.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//リトライボタン
	retryButton.Init(L"asset/UI/ハンバーガーアイコン100x100.png");
	//retryButton.Init(L"asset/block.png");
	retryButton.SetPos(-860.0f, -440.0f, 0.0f);
	retryButton.SetSize(50.0f, 50.0f, 0);
	retryButton.SetAngle(0);
	retryButton.SetColor(1, 1, 1, 1);


	return 0;
}

int TS_StageScene::Update()
{
	return 0;
}

int TS_StageScene::Draw()
{
	return 0;
}

int TS_StageScene::End()
{
	return 0;
}
