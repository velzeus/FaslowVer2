#include "Game.h"
#include<time.h>

void Game::Init(HWND hWnd)
{
	srand((unsigned)time(NULL));
	D3D_Create(hWnd);                //DirectXを初期化

	sound.Init();//サウンドを初期化
	sound.Play(SOUND_LABEL_BGM000);//BGMを再生
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
			blocks[x][y].Init(L"asset/block.png");//ブロックを初期化
			blocks[x][y].SetPos(BLOCK_SIZE * (x - STAGE_X / 2), BLOCK_SIZE * (y - STAGE_Y / 2), 0.0f);//位置を設定
			blocks[x][y].SetSize(BLOCK_SIZE, BLOCK_SIZE, 0.0f);//大きさを設定
		}
	}

	scoreboard.Init(L"asset/number.png", 10, 1);//得点表示を初期化
	scoreboard.SetPos(-145.0f, 200.0f, 0.0f);//位置を設定
	scoreboard.SetSize(40.0f, 40.0f, 0.0f);//大きさを設定

	score = 0;//得点を初期化

	title.Init(L"asset/apple.jpg", 10, 1);//得点表示を初期化
	title.SetPos(0.0f, 0.0f, 0.0f);//位置を設定
	title.SetSize(640.0f, 480.0f, 0.0f);//大きさを設定

	gametitle.Init(L"asset/title.png");//タイトル画面描画
	gametitle.SetPos(0.0f, 0.0f, 0.0f);       //位置を設定
	gametitle.SetSize(640.0f, 480.0f, 0.0f);  //大きさを設定
	gametitle.SetAngle(0.0f);                 //角度を設定

	scene = 0;
}

void Game::Update(void)
{
	input.Update();

	switch (scene)
	{
	case 0://タイトル画面
		//キー入力で本編へ
		if (input.GetKeyTrigger(VK_A))
		{
			scene = 1;

			//data配列を初期化
			for (int x = 0; x < STAGE_X; x ++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					data[x][y] = 0;
				}
			}
			state = 0;//ゲームの状態を初期化
			score = 0;//得点を初期化
		}
		break;

	case 1://ゲーム本編
		//ゲームオーバーならゲームの進行を止める
		if (state == 3) { scene = 0; }

		//新たにテトリミノを出現させる
		if (state == 0)
		{
			//ゲームの状態を「１：落下中」に変更
			state = 1;


			TetrominoType = rand() % 7;//０～６をランダムで取得

			switch (TetrominoType)
			{
			case 0://直線
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[7][19] = 2;
				break;

			case 1://四角
				data[5][20] = 2;
				data[6][20] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 2://S字
				data[4][19] = 2;
				data[5][19] = 2;
				data[5][20] = 2;
				data[6][20] = 2;
				break;

			case 3://逆S字
				data[4][20] = 2;
				data[5][20] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 4://逆L角
				data[4][20] = 2;
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				break;

			case 5://L字
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[6][20] = 2;
				break;

			case 6://T字
				data[4][19] = 2;
				data[5][19] = 2;
				data[6][19] = 2;
				data[5][20] = 2;
				break;
			}
			count = 0;

			TetrominoDirection = 0;//向きをリセット


		}

		//回転
		if (input.GetKeyTrigger(VK_W))
		{
			//向きを変更する
			int newDirection = TetrominoDirection + 1;
			if (newDirection > 3) { newDirection = 0; }

			//基準点を調べる
			int baseX = -1, baseY = -1;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y; y++)
				{
					if (data[x][y] == 2)
					{
						for (int tx = 0; tx < 4; tx++)
						{
							for (int ty = 0; ty < 4; ty++)
							{
								if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2)
								{
									baseX = x - tx;
									baseY = y - ty;
									break;
								}
							}
							if (baseX >= 0) { break; }
						}
						break;
					}
				}
				if (baseX >= 0) { break; }
			}

			//回転が可能か調べる
			bool ngFg = false;
			for (int tx = 0; tx < 4; tx++)
			{
				for (int ty = 0; ty < 4; ty++)
				{
					if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2 &&
						(data[baseX + tx][baseY + ty] == 1 || baseX + tx > STAGE_X - 1 || baseY + ty > STAGE_Y - 1 || baseX + tx < 0 || baseY + ty < 0))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//回転が可能なら
			if (ngFg == false)
			{
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2) { data[x][y] = 0; }
					}
				}
				for (int tx = 0; tx < 4; tx++)
				{
					for (int ty = 0; ty < 4; ty++)
					{
						if (TetrominoData[TetrominoType][TetrominoDirection][ty][tx] == 2)
						{
							data[baseX + tx][baseY + ty] = 2;
						}
					}
				}
				TetrominoDirection = newDirection;//方向を更新
			}
		}

		//左移動
		if (input.GetKeyTrigger(VK_A))
		{
			//左移動が可能か調べる
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++) {
				for (int y = 0; y < STAGE_Y + 3; y++) {
					if (data[x][y] == 2 && (x == 0 || data[x - 1][y] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//左移動が可能なら
			if (ngFg == false)
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x - 1][y] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		//右移動
		if (input.GetKeyTrigger(VK_D))
		{
			//右動が可能か調べる
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[x][y] == 2 && (x == STAGE_X - 1 || data[x + 1][y] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true) { break; }
			}

			//右移動が可能なら
			if (ngFg == false)
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x + 1][y] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		if (input.GetKeyPress(VK_S))
		{
			count = 31;
		}

		count++;
		//落下処理
		if (count > 30)
		{
			count = 0;

			//揃っていれば、その行より上の行を１行ずづつずらす
			if (state == 2)
			{
				//１行揃った行がないかチェックする
				int cnt = 0;//消した列数をカウントする変数
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[0][y] == 3)
					{
						for (int ty = y + 1; ty < STAGE_Y + 3; ty++)
						{
							for (int tx = 0; tx < STAGE_X; tx++)
							{
								data[tx][ty - 1] = data[tx][ty];
							}
						}
						y--;
						cnt++;
					}
				}

				//得点を加算する
				switch (cnt)
				{
				case 1:score += 100; break;//シングル(１列消し）
				case 2:score += 300; break;//ダブル（２列消し）
				case 3:score += 500; break;//トリプル（３列消し）
				case 4:score += 800; break;//テトリス（４列消し）
				}
				//ゲームの状態を「０：落下するものがない状態」に変更
				state = 0;
			}

			//落とすことが可能か調べる
			bool ngFg = false;
			for (int x = 0; x < STAGE_X; x++)
			{
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					if (data[x][y] == 2 && (y == 0 || data[x][y - 1] == 1))
					{
						ngFg = true;
						break;
					}
				}
				if (ngFg == true)
				{
					break;
				}
			}

			//落とすことが不可能なら
			if (ngFg == true)
			{
				//着地
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							data[x][y] = 1;//２(落下中)　から　１(着地後)　に変更
						}
					}
				}

				//ゲームの状態を「０：落下するものがない状態」に変更
				state = 0;


				//１行揃った行がないかチェックする
				for (int y = 0; y < STAGE_Y + 3; y++)
				{
					bool completeFg = true;
					for (int x = 0; x < STAGE_X; x++)
					{
						if (data[x][y] == 0)
						{
							completeFg = false;
							break;
						}
					}

					//揃っていれば色を着ける
					if (completeFg == true)
					{
						for (int x = 0; x < STAGE_X; x++)
						{
							data[x][y] = 3;
						}

						//ゲームの状態を「２：揃った状態」に変更
						state = 2;
					}
				}

				//ゲームオーバーになっていないかチェックする
				for (int x = 0; x < STAGE_X; x++)//一番上の列をチェック
				{
					if (data[x][STAGE_Y - 1] == 1)
					{

						//テトリミノの色を変える
						for (int tx = 0; tx < STAGE_X; tx++)
						{
							for (int ty = 0; ty < STAGE_Y + 3; ty++)
							{
								if (data[tx][ty] == 1)
								{
									data[tx][ty] = 4;
								}
							}
						}

						//ゲームの状態を「３：ゲームオーバー」に変更
						state = 3;
						break;
					}
				}
			}
			//落とすことが可能なら
			else
			{
				int tmp[STAGE_X][STAGE_Y + 3] = {};
				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						if (data[x][y] == 2)
						{
							tmp[x][y - 1] = 2;
						}
						else if (data[x][y] == 1)
						{
							tmp[x][y] = 1;
						}
					}
				}

				for (int x = 0; x < STAGE_X; x++)
				{
					for (int y = 0; y < STAGE_Y + 3; y++)
					{
						data[x][y] = tmp[x][y];
					}
				}
			}
		}

		

		//消滅
		for (int y = 0; y < STAGE_Y; y++)
		{
			for (int x = 0; x < STAGE_X; x++)
			{
				if (data[x][y] == 2)
				{
					check++;
				}
				else
				{
					break;
				}
				if (check == STAGE_X)
				{

				}
			}
		}

		//色をつける
		for (int x = 0; x < STAGE_X; x++)
		{
			for (int y = 0; y < STAGE_Y; y++)
			{
				switch (data[x][y])
				{
				case 0://空白
					blocks[x][y].SetColor(1.0f, 1.0f, 1.0f, 0.2f);
					break;
				case 1://着地しているテトリミノ
					blocks[x][y].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
					break;
				case 2://落ちてきているテトリミノ
					blocks[x][y].SetColor(1.0f, 0.8f, 0.8f, 1.0f);
					break;
				case 3://揃ったテトリミノ
					blocks[x][y].SetColor(0.4f, 0.4f, 1.0f, 1.0f);
					break;
				case 4://ゲームオーバー時
					blocks[x][y].SetColor(1.0f, 0.2f, 0.2f, 1.0f);
					break;
				}
			}
		}

		break;
	}

	
}

void Game::Draw(void)
{
	D3D_StartRender();   //描画開始
	switch (scene)
	{
	case 0://タイトル画面
		gametitle.Draw();//タイトルを描画
		break;

	case 1://ゲーム本編
		background.Draw();  //背景を描画

		//ブロックを表示
		for (int x = 0; x < STAGE_X; x++)
		{
			for (int y = 0; y < STAGE_Y; y++)
			{
				blocks[x][y].Draw();
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
		break;
	}
	
	D3D_FinishRender();  //描画終了
}

void Game::Uninit(void)
{
	player.Uninit(); //プレイヤーを終了
	background.Uninit();//背景を終了

	//ブロックを終了
	for (int x = 0; x < STAGE_X; x++)
	{
		for (int y = 0; y < STAGE_Y; y++)
		{
			blocks[x][y].Uninit();
		}
	}
	scoreboard.Uninit();//スコア終了
	sound.Uninit();//サウンドを終了
	title.Uninit();//タイトルを終了
	gametitle.Uninit();
	D3D_Release();   //DirectXを終了
}