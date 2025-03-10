#include "StageScene.h"

using namespace std;

using json = nlohmann::json;

struct  TS_Float4
{
public:
	float x, y, z, a;
	TS_Float4(float _x, float _y, float _z, float _a) :x(_x), y(_y), z(_z), a(_a) {};
};

//右クリック
//glay<->blueへじわじわと変化できるように(20フレームで)
const TS_Float4 StageBG_Glay(1.0f, 1.0f, 1.0f, 1);
const TS_Float4 StageBG_Blue(0.0f, 0.6f, 1.0f, 1);

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
			//grids[x][y].Init(L"asset/block.png");//ブロックを初期化
			//grids[x][y].SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);//位置を設定
			//grids[x][y].SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);//大きさを設定

			//マスの状態を代入
			gridData[x][y] = read_gridStateList[y][x];

			////ゴールを別個に作る
			//if (gridData[x][y] == GORL)
			//{
			//	gorl.Init(L"asset/Goll/TeamName/Team_Name.png");
			//	gorl.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
			//	gorl.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
			//	gorl.SetAngle(0.0f);
			//	gorl.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
			//}
			//else if (gridData[x][y] == BOLL) {
			//	ball.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0);
			//	gridData[x][y] = NULLBLOCK;
			//}
			
			//表示させるだけ
			switch (gridData[x][y])
			{
			case GORL:
				gorl.Init(L"asset/Goll/TeamName/Team_Name.png");
				gorl.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
				gorl.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
				gorl.SetAngle(0.0f);
				gorl.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				gridData[x][y] = NULLBLOCK;
				break;
			case BOLL:
				ball.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0);
				gridData[x][y] = NULLBLOCK;
				break;
			case COIN:
				coin.Init(L"asset/Coin/1coin.png");
				coin.SetPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
				coin.SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
				coin.SetAngle(0.0f);
				coin.SetColor(1.0f, 1.0f, 1.0f, 1.0f);
				gridData[x][y] = NULLBLOCK;
				break;
			case CANNON:
				for (auto& o : cannons)
				{
					//座標がセットされていない
					if (o->GetPosFlg() == false&&o->GetIndex()==(STAGE_X * y + x))
					{
						//向いている方向に向かって1マス分ずらす
						DirectX::XMFLOAT3 deltaPos = {};
						switch (o->GetRotateCannon())
						{
						case TOWARD_UP:
							deltaPos = { 0,BLOCKSIZE_Y,0 };
							break;
						case TOWARD_RIGHTUP:
							deltaPos = { BLOCKSIZE_X,BLOCKSIZE_Y,0 };
							break;
						case TOWARD_RIGHT:
							deltaPos = { BLOCKSIZE_X,0,0 };
							break;
						case TOWARD_RIGHTDOWN:
							deltaPos = { BLOCKSIZE_X,-BLOCKSIZE_Y,0 };
							break;
						case TOWARD_DOWN:
							deltaPos = { 0,-BLOCKSIZE_Y,0 };
							break;
						case TOWARD_LEFTDOWN:
							deltaPos = { -BLOCKSIZE_X,-BLOCKSIZE_Y,0 };
							break;
						case TOWARD_LEFT:
							deltaPos = { -BLOCKSIZE_X,0,0 };
							break;
						case TOWARD_LEFTUP:
							deltaPos = { -BLOCKSIZE_X,BLOCKSIZE_Y,0 };
							break;
						}

						//初期化
						o->Init(L"asset/Sprite/CannonAndEffect.png", 5, 4);
						
						//描画用の座標情報
						o->SetPos(read_blockPositionList[y][x].x + deltaPos.x, read_blockPositionList[y][x].y + deltaPos.y, 0.0f);
						o->SetSize(BLOCKSIZE_X * 2, BLOCKSIZE_Y * 4, 0);
						
						//当たり判定用の座標情報
						o->SetCollisionPos(read_blockPositionList[y][x].x, read_blockPositionList[y][x].y, 0.0f);
						o->SetCollisionScale(BLOCKSIZE_X, BLOCKSIZE_Y, 0);
						o->SetAngle(-45 * o->GetRotateCannon());
						o->SetColor(1, 1, 1, 1);
						o->numU = 0; o->numV = 0;

						//セット完了
						o->SetPosFlg(true);

						//単位ベクトルを求める
						//目標地点の座標(基準から10マスぐらい先にする)
						DirectX::XMFLOAT3 target = { o->GetCollisionPos().x + deltaPos.x * 10,o->GetCollisionPos().y + deltaPos.y * 10,0 };

						//単位ベクトルを求めてセット
						//o->SetNormalizedDirection();
						o->SetNormalizedDirection(NormalizedRotateVector(RotateVector(target, o->GetPos())));
						break;
					}
				}
				break;
			}

			//ブロック
			for (int n = 0; n < blocks.size(); n++)
			{
				int idxBase = blocks[n]->GetIndex();
				int idx1 = idxBase / STAGE_X;	//Y
				int idx2 = idxBase % STAGE_X;	//X


				//まだ値がセットされていないかつ、indexがマスの場所と同じなら
				if ((idx1 == y && idx2 == x) && blocks[n]->GetFlg()==false)

				{
					//ブロックの状態ごとにテクスチャをあてがう
					switch (blocks[n]->GetBlockType())
					{
					case STICKY_BLOCK:
						blocks[n]->Init(L"asset/Blocks/STICKY_BLOCK_GREEN.png");
						break;
					case SLIP_BLOCK:
						blocks[n]->Init(L"asset/Blocks/ice.png");
						break;
					case UNBREAK_BLOCK:
						blocks[n]->Init(L"asset/Blocks/STICKY_BLOCK_GREEN.png");
						blocks[n]->SetColor(0, 0, 0, 1);
						break;
					}

					//座標等を代入
					blocks[n]->SetPos(read_blockPositionList[idx1][idx2].x, read_blockPositionList[idx1][idx2].y, 0.0f);
					blocks[n]->SetSize(BLOCKSIZE_X, BLOCKSIZE_Y, 0.0f);
					blocks[n]->SetIndex(n);

					blocks[n]->SetFlg(true);

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
	prvpos = ball.GetPos();
	CheckSurroundingCollisions();
	UpdateMoveDir();

	//オプションボタン　　440
	optionButton.Init(L"asset/UI/back.png");
	optionButton.SetPos(-900.0f, 470.0f, 0.0f);
	optionButton.SetSize(50.0f, 50.0f, 0.0f);
	optionButton.SetAngle(0.0f);
	optionButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//リトライボタン
	retryButton.Init(L"asset/UI/Hamburger_icon_100x100.png");
	//retryButton.Init(L"asset/block.png");
	retryButton.SetPos(-800.0f, 470.0f, 0.0f);
	retryButton.SetSize(50.0f, 50.0f, 0);
	retryButton.SetAngle(0);
	retryButton.SetColor(1, 1, 1, 1);

	//背景
	background.Init(L"asset/background/Background_glay.png");
	background.SetPos(-190, 50, 0);
	background.SetSize(1280, 720, 0);
	background.SetAngle(0);
	background.SetColor(StageBG_Glay.x, StageBG_Glay.y, StageBG_Glay.z, StageBG_Glay.a);

	//切り取りの枠
	cutAndPaste.Init(L"asset/UI/orange_flame.png");
	cutAndPaste.SetPos(0, 0, 0);
	cutAndPaste.SetSize(BLOCKSIZE_X*3, BLOCKSIZE_Y*3, 0);
	cutAndPaste.SetAngle(0);
	cutAndPaste.SetColor(1, 1, 1, 0);

	//切り取りボタン
	cutButton.Init(L"asset/UI/Flame2.png");
	cutButton.SetPos(-700, 470, 0);
	cutButton.SetSize(50, 50, 0);
	cutButton.SetAngle(0);
	cutButton.SetColor(1, 1, 1, 1);

	//保存する場所の枠
	holdAreaFlame.Init(L"asset/UI/Folder.png");
	holdAreaFlame.SetPos(-190, -310 - BLOCKSIZE_Y * 3, 0);
	holdAreaFlame.SetSize(1280, BLOCKSIZE_Y * 4, 0);
	holdAreaFlame.SetAngle(0);
	holdAreaFlame.SetColor(1, 1, 1, 1);


	//保存する用の場所
	for (int i = 0; i < 5; i++)
	{
		holdAreas.emplace_back(new Area());
		holdAreas[i]->Init(L"asset/UI/orange_flame.png");
		holdAreas[i]->SetPos(-700+ (BLOCKSIZE_X * 6+15)*i, -310 - BLOCKSIZE_Y * 3, 0);
		holdAreas[i]->SetSize(BLOCKSIZE_X * 3, BLOCKSIZE_Y * 3, 0);
		holdAreas[i]->SetAngle(0);
		holdAreas[i]->SetColor(1, 1, 1, 1);
		holdAreas[i]->SetIndex(i);

		
	}
	
	accelerationFlg = false;

	triggerFlg_N = false;
	triggerFlg_O = false;
	triggerFlg_T = false;

	cannonIndex = -1;

	cannonFlg = false;
	rpid = false;

	cutAndPaste.SetCutModeFlg(false);
	animCount = 0;
	addFlg = false;

	return 0;
}

int StageScene::Update()
{
	//ゴールの判定
	if (center.x == gorl.GetPos().x &&
		center.y == gorl.GetPos().y)
	{
		//リザルトシーンに
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}

	
	ball.Setborder();//端に行った時
	//大砲と当たっている判定があったら　
	for (auto& o : cannons)
	{
		//ボールと大砲が重なったら
		if (center.x == o->GetCollisionPos().x &&
			center.y == o->GetCollisionPos().y)
		{
			//o->SetCannnonModeFlg(true);
			cannonIndex = o->GetCannonNum();
			cannonFlg = true;
			o->SetAnimationCount(0);

			//当たっている大砲の単位ベクトルを渡してボールの移動をする
			ball.Move_Cannon(cannons[cannonIndex]->GetNormalizedDirection());
		}
		//else
		//{
		//	//o->SetCannnonModeFlg(false);
		//}

		//if (o->GetCannonModeFlg() == false&&cannonFlg==true)
		//{
		//	//当たっている大砲の番号を渡す
		//	cannonIndex = o->GetCannonNum();
		//	break;
		//}
	}

	ball.Setborder();//端に行った時

	//大砲と当たっている
	if (cannonFlg == true)
	{
		/*if (cannons[cannonIndex]->GetAnimationCount() >= 30)
		{
			cannons[cannonIndex]->SetCannnonModeFlg(true);
		}*/

		//発射する条件を満たしている
		if (cannons[cannonIndex]->GetCannonModeFlg() == true)
		{
			//当たっている大砲の単位ベクトルを渡してボールの移動をする
			ball.Move_Cannon(cannons[cannonIndex]->GetNormalizedDirection());
			ball.SetColor(1, 1, 1, 1);
			

		}
		else
		{
			ball.SetColor(1, 1, 1, 0);
		}

		
		//アニメーションカウントが24で割り切れるときかつ、アニメーションカウントがゼロより大きいとき
		if (cannons[cannonIndex]->GetAnimationCount() % 24 == 0&& cannons[cannonIndex]->GetAnimationCount() > 0)
		{
			//縦方向のUVを更新
			cannons[cannonIndex]->numV++;
			cannons[cannonIndex]->numU=0;
			cannons[cannonIndex]->SetAnimationCount(cannons[cannonIndex]->GetAnimationCount() + 1);

			cannons[cannonIndex]->SetCannnonModeFlg(true);
		}
		else 
		{
			//表示している画像番号が17番より下かつ、アニメーションカウントが全部回った後の値より少ないとき
			if (5 * cannons[cannonIndex]->numV + cannons[cannonIndex]->numU < 17 && cannons[cannonIndex]->GetAnimationCount() < 17 * 5)
			{
				//カウントを上げる
				cannons[cannonIndex]->SetAnimationCount(cannons[cannonIndex]->GetAnimationCount() + 1);

				//アニメーションカウント%5が4のときかつ、numUが4未満のとき
				if (cannons[cannonIndex]->GetAnimationCount() % 5 == 4&& cannons[cannonIndex]->numU<4)
				{
					cannons[cannonIndex]->numU++;
				}
			}
			else
			{
				//UVの値を0に戻す
				cannons[cannonIndex]->numV = 0;
				cannons[cannonIndex]->numU = 0;
			}
			
		}
		
	}
	else
	{
		ball.Move();//移動
	}

	center = ball.GetPos();//ボールの位置を取得

	if (inputSystem->GetTrigger(MK_RIGHT))
	{
		if (rpid == true) { rpid = false; }
		else { rpid = true; }

	}

	if (abs(center.x - prvpos.x) == 40 || abs(center.y - prvpos.y) == 40)
	{
		if(rpid)
		{
			ball.vel_x = 20.0f;
			ball.vel_y = 20.0f;
		}
		else 
		{
			ball.vel_x = 1.0f;
			ball.vel_y = 1.0f;
		}

		prvpos = center;
		CheckSurroundingCollisions();//あたり判定
		UpdateMoveDir();//ボールの方向を変える

	}


	//大砲による移動をしている場合での当たり判定
	if (cannonFlg == true)
	{
		if (cannons[cannonIndex]->GetCannonModeFlg() == true)
		{
			//進む方向のブロックの座標を代入(斜めは上下の判定が先に入る)
			std::vector<DirectX::XMFLOAT3> forwardCenter;
			DirectX::XMFLOAT3 tmp = {};
			switch (cannons[cannonIndex]->GetRotateCannon())
			{
			case TOWARD_UP:
				//y軸
				tmp = { center.x, center.y + BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_RIGHTUP:
				//y軸
				tmp = { center.x, center.y + BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);

				//x軸
				tmp = { center.x + BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_RIGHT:
				//x軸
				tmp = { center.x + BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_RIGHTDOWN:
				//y軸
				tmp = { center.x, center.y - BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);

				//x軸
				tmp = { center.x + BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_DOWN:
				//y軸
				tmp = { center.x, center.y - BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_LEFTDOWN:
				//y軸
				tmp = { center.x, center.y - BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);

				//x軸
				tmp = { center.x - BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_LEFT:
				//x軸
				tmp = { center.x - BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			case TOWARD_LEFTUP:
				//y軸
				tmp = { center.x, center.y + BLOCKSIZE_Y, center.z };
				forwardCenter.emplace_back(tmp);

				//x軸
				tmp = { center.x - BLOCKSIZE_X, center.y, center.z };
				forwardCenter.emplace_back(tmp);
				break;
			}

			//進行方向のブロック座標にブロックがあるかを確認する
			for (auto& v : forwardCenter)
			{
				for (auto& o : blocks)
				{
					//判定を取っている場所に粘着ブロックがあったら
					if (v.x >= o->GetPos().x - o->GetSize().x / 4 &&
						v.x <= o->GetPos().x + o->GetSize().x / 4 &&
						v.y >= o->GetPos().y - o->GetSize().y / 4 &&
						v.y <= o->GetPos().y + o->GetSize().y / 4)
					{
						if (o->GetBlockType() == STICKY_BLOCK)
						{
							ball.SetPos(o->GetPos().x + (center.x - v.x), o->GetPos().y + (center.y - v.y), ball.GetPos().z);
							cannons[cannonIndex]->SetCannnonModeFlg(false);
							cannonFlg = false;
						}
					}
				}
			}


		}
		CheckSurroundingCollisions();//あたり判定
	}

	
  	

	if (ball.boder)
	{
		prvpos = ball.GetPos();
		ball.boder = false;
	}
  	


	////色をつける
	//for (int x = 0; x < STAGE_X; x++)
	//{
	//	for (int y = 0; y < STAGE_Y; y++)
	//	{
	//		switch (gridData[x][y])
	//		{
	//		case NULLBLOCK://空白
	//			grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 0.0f);
	//			break;
	//		case BOLL://ボール
	//			grids[x][y].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
	//			break;
	//		case GORL://ゴール
	//			grids[x][y].SetColor(1.0f, 0.0f, 0.0f, 1.0f);
	//			break;
	//		case COIN://コイン
	//			grids[x][y].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
	//			break;
	//		case STICKY_BLOCK://粘着ブロック
	//			grids[x][y].SetColor(0.0f, 1.0f, 0.0f, 1.0f);
	//			break;
	//		case SLIP_BLOCK://滑るブロック
	//			grids[x][y].SetColor(0.0f, 1.0f, 1.0f, 1.0f);
	//			break;
	//		case UNBREAK_BLOCK://破壊不可ブロック
	//			grids[x][y].SetColor(0.0f, 0.0f, 0.0f, 1.0f);
	//			break;
	//		}
	//	}
	//}

	
	////ゴールの判定
	//bool tmpGorlFlg=false;
	if ((hitBlockType[0] == GORL))//ボールの前にゴールブロックがあれば
	{
		//リザルトシーンに
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}


	


	//左クリック
	if (inputSystem->GetTrigger(MK_LEFT))
	{
		//戻るボタン
		//クリックされたx座標が内側にあったら
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (optionButton.GetPos().x - optionButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (optionButton.GetPos().x + optionButton.GetSize().x / 2))
		{
			//マウスカーソルの座標との誤差を埋めるため10ずらす
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2+10) * -1 > (optionButton.GetPos().y - optionButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2+10) * -1 < (optionButton.GetPos().y + optionButton.GetSize().y / 2))
			{
				//決定されてない状態に戻す
				SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//セレクトシーンに戻る
				SceneManager::GetInstance()->ChangeScene(SELECT);
			}

		}


		//ゴールした判定(動作確認用)
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


				//リザルトシーンに
				SceneManager::GetInstance()->ChangeScene(RESULT);
			}

		}


		//リトライボタン
		//クリックされたx座標が内側にあったら
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (retryButton.GetPos().x - retryButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (retryButton.GetPos().x + retryButton.GetSize().x / 2))
		{
			//タスクバーを勘案して-部分だけ40上にずらして考える
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (retryButton.GetPos().y - retryButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (retryButton.GetPos().y + retryButton.GetSize().y / 2))
			{
				//決定されてない状態に戻す
				//SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
				//SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);


				//ステージシーンを呼び直す
				//SceneManager::GetInstance()->ChangeScene(STAGE);
				End();//vector型配列をリセットさせる
				Start();
				return 0;
			}

		}



		//切り取り
		//------------------------------------------------------------
		//どのブロックの内側にあるかを判定する
		/*int clickBlockIndex_X = 0;
		int clickBlockIndex_Y = 0;*/
		bool cutFlg[2] = { false,false };
		if (cutAndPaste.GetCutModeFlg() == false)
		{
			for (int i = 0; i < read_blockPositionList[0].size(); i++)
			{
				//x軸で内側にあったら
				if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (read_blockPositionList[0][i].x - BLOCKSIZE_X / 2) &&
					inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (read_blockPositionList[0][i].x + BLOCKSIZE_X / 2))
				{
					gridIndex_X[0] = i;
					cutFlg[0] = true;
					break;
				}
			}

			for (int i = 0; i < read_blockPositionList.size(); i++)
			{
				//y軸で内側にあったら
				if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 + BLOCKSIZE_X / 2) * -1 > (read_blockPositionList[i][0].y - BLOCKSIZE_Y / 2) &&
					(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 + BLOCKSIZE_Y / 2) * -1 < (read_blockPositionList[i][0].y + BLOCKSIZE_Y / 2))
				{
					gridIndex_Y[0] = i;
					cutFlg[1] = true;
					break;
				}
			}
		}

		//カットモードがtrueなら
		if ((cutFlg[0] == true && cutFlg[1] == true)&&cutAndPaste.GetCutModeFlg()==false)
		{
			//配列の位置を渡す
			cutAndPaste.SetClickIndex(gridIndex_X[0], gridIndex_Y[0]);

			cutAndPaste.SetCutModeFlg(true);

			//座標と透明度を再設定
			cutAndPaste.SetPos(
				read_blockPositionList[gridIndex_Y[0]][gridIndex_X[0]].x, 
				read_blockPositionList[gridIndex_Y[0]][gridIndex_X[0]].y, 0);

			cutAndPaste.SetColor(1, 1, 1, 1);
		}
		else
		{
			//切り取りボタンの内側
			if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (cutButton.GetPos().x - cutButton.GetSize().x / 2) &&
				inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (cutButton.GetPos().x + cutButton.GetSize().x / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 ) * -1 > (cutButton.GetPos().y - cutButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2 ) * -1 < (cutButton.GetPos().y + cutButton.GetSize().y / 2))
			{
				//切り取り処理
				cutAndPaste.CutBlocks(read_gridStateList);

				int changeCount = 0;
				int setAreaCount = -1;
				int indexX = 0;
				int indexY=0;
				std::vector<std::vector<int>> tmpBlockIndex;

				tmpBlockIndex.emplace_back();
				tmpBlockIndex.emplace_back();
				tmpBlockIndex.emplace_back();

				tmpBlockIndex[0].resize(3, 9999);
				tmpBlockIndex[1].resize(3, 9999);
				tmpBlockIndex[2].resize(3, 9999);

				//ブロックの座標の設定
				for (auto& o : blocks)
				{
					if (o->GetBlockType() == STICKY_BLOCK ||
						o->GetBlockType() == SLIP_BLOCK)
					{
						//y座標
						for (int n_y = cutAndPaste.GetClickIndex(1) - 1; n_y <= cutAndPaste.GetClickIndex(1) + 1; n_y++)
						{
							//ループを抜けるフラグ
							bool flg_break = false;

							//x座標
							for (int n_x = cutAndPaste.GetClickIndex(0) - 1; n_x <= cutAndPaste.GetClickIndex(0) + 1; n_x++)
							{
								//選択中のブロックが要素番号が示している配列の場所の値と同じか
								if (o->GetPos().x == read_blockPositionList[n_y][n_x].x &&
									o->GetPos().y == read_blockPositionList[n_y][n_x].y)
								{
									//状態を空に置き換える
									//o->SetBlockType(NULLBLOCK);
									//o->SetColor(1, 1, 1, 0);

									for (int i = 0; i < holdAreas.size(); i++)
									{
										if (holdAreas[i]->GetSetBlockFlg() == false)
										{
											setAreaCount = i;
											//切り取ったブロックを移動させる
											//holdAreas[i]->SetSetBlockFlg(true);
											o->SetPos(
												holdAreas[i]->GetPos().x - (cutAndPaste.GetClickIndex(0) - n_x) * BLOCKSIZE_X,
												holdAreas[i]->GetPos().y - (cutAndPaste.GetClickIndex(1) - n_y) * BLOCKSIZE_Y, 0);

											//配列の中の値が3個になったら
											/*if (tmpBlockIndex[indexY].size() == 3||indexY-1)
											{
												indexY++;
											}*/

											indexX = -(cutAndPaste.GetClickIndex(0) - n_x) + 1;
											indexY = -(cutAndPaste.GetClickIndex(1) - n_y) + 1;

											//移動させたブロックの番号を格納
											tmpBlockIndex[indexY][indexX]=(o->GetIndex());
											
											changeCount++;
											//flg_break = true;
											break;
										}
									}

									if (flg_break == true)
									{
										break;
									}
									
								}
								else
								{
									/*indexY = -(cutAndPaste.GetClickIndex(1) - n_y) + 1;
									if (tmpBlockIndex[indexY].size() < 3)
									{
										
										tmpBlockIndex[indexY].emplace_back();
									}*/
								}
							}

							if (flg_break == true)
							{
								break;
							}
						}

					}

					//変更された個数が9個以上ならループを抜ける
					if (changeCount >= 9)
					{
						break;
					}

				}

				//ブロックが格納されたなら（要素番号が0以上なら格納された）
				if (setAreaCount >= 0)
				{
					//格納されている状態と格納されたブロックの番号を渡す
					holdAreas[setAreaCount]->SetSetBlockFlg(true);
					holdAreas[setAreaCount]->SetBlockIndex(tmpBlockIndex);
				}
				

				//カットの状態を戻して枠を非表示にする
				cutAndPaste.SetCutModeFlg(false);
				cutAndPaste.SetColor(1, 1, 1, 0);

			}
			else
			{
				//保存されているブロックの場所
				for (auto& o : holdAreas)
				{
					//ブロックが入っている枠を選んでいるとき
					if (o->GetSetBlockFlg() == true && cutAndPaste.GetCutModeFlg() == true &&
						inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (o->GetPos().x - o->GetSize().x / 2) &&
						inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (o->GetPos().x + o->GetSize().x / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (o->GetPos().y - o->GetSize().y / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (o->GetPos().y + o->GetSize().y / 2))
					{
						std::vector<std::vector<int>> tmpBlockIndex=o->GetBlockIndex();

						bool changeFlg = true;
						
						//y座標
						for (int n_y = cutAndPaste.GetClickIndex(1) - 1; n_y <= cutAndPaste.GetClickIndex(1) + 1; n_y++)
						{
							//x座標
							for (int n_x = cutAndPaste.GetClickIndex(0) - 1; n_x <= cutAndPaste.GetClickIndex(0) + 1; n_x++)
							{
								//保存されている場所の要素があるとき
								if (tmpBlockIndex[-(cutAndPaste.GetClickIndex(1) - n_y) + 1].size() > 0)
								{
									//枠の中が全て空だったら
									if (read_gridStateList[n_y][n_x] != NULLBLOCK)
									{
										changeFlg = false;
									}
								}
								
							}
						}
						
						if (changeFlg == true)
						{
							//カットの枠に保存されたブロックを置く
						//y座標
							for (int n_y = cutAndPaste.GetClickIndex(1) - 1; n_y <= cutAndPaste.GetClickIndex(1) + 1; n_y++)
							{
								bool flg_break = false;
								//x座標
								for (int n_x = cutAndPaste.GetClickIndex(0) - 1; n_x <= cutAndPaste.GetClickIndex(0) + 1; n_x++)
								{
									//vectorの要素数内かつ、値が入っている段か
									if (tmpBlockIndex[-(cutAndPaste.GetClickIndex(1) - n_y) + 1][-(cutAndPaste.GetClickIndex(0) - n_x)+1]!=9999)
									{
										//座標の再設定
										blocks[tmpBlockIndex[-(cutAndPaste.GetClickIndex(1) - n_y) + 1][-(cutAndPaste.GetClickIndex(0) - n_x) + 1]]->
											SetPos(
												cutAndPaste.GetPos().x + BLOCKSIZE_X * (-(cutAndPaste.GetClickIndex(0) - n_x)),
												cutAndPaste.GetPos().y + BLOCKSIZE_X * (-(cutAndPaste.GetClickIndex(1) - n_y)), 0);

										read_gridStateList[n_y][n_x] =
											blocks[tmpBlockIndex[-(cutAndPaste.GetClickIndex(1) - n_y) + 1][-(cutAndPaste.GetClickIndex(0) - n_x) + 1]]->GetBlockType();

									}
									else
									{
										read_gridStateList[n_y][n_x] = NULLBLOCK;
									}


								}

							}

							//格納されていない状態にする
							o->SetSetBlockFlg(false);
							tmpBlockIndex.clear();
							o->SetBlockIndex(tmpBlockIndex);
						}
						
						
						
					}
					


				}

				cutAndPaste.SetCutModeFlg(false);
				cutAndPaste.SetColor(1, 1, 1, 0);
			}
		}

		//------------------------------------------------------------


	}

	for (auto& o : holdAreas)
	{
		if (o->GetSetBlockFlg() == true)
		{
			o->SetColor(1, 1, 1, ((float)animCount / 60.0f));
		}
		else
		{
			o->SetColor(1, 1, 1, 0);
		}
	}
	
	if (animCount >= 60 && addFlg == true)
	{
		addFlg = false;
	}
	else if (animCount <= 0 && addFlg == false)
	{
		addFlg = true;
	}

	if (addFlg == true)
	{
		animCount++;
	}
	else
	{
		animCount--;
	}


	//クリックが離されたらの処理
	//-----------------------------------------
	//カットモードがture
	if (cutAndPaste.GetCutModeFlg() == true)
	{
		//for (int i = 0; i < read_blockPositionList[0].size(); i++)
		//{
		//	//x軸で内側にあったら
		//	if (inputSystem->GetReleasePosition().x - SCREEN_WIDTH / 2 > (read_blockPositionList[0][i].x - BLOCKSIZE_X / 2) &&
		//		inputSystem->GetReleasePosition().x - SCREEN_WIDTH / 2 < (read_blockPositionList[0][i].x + BLOCKSIZE_X / 2))
		//	{
		//		gridIndex_X[1] = i;
		//		break;
		//	}
		//}

		//for (int i = 0; i < read_blockPositionList.size(); i++)
		//{
		//	//y軸で内側にあったら
		//	if ((inputSystem->GetReleasePosition().y - SCREEN_HEIGHT / 2) * -1 > (read_blockPositionList[i][0].y - BLOCKSIZE_Y / 2) &&
		//		(inputSystem->GetReleasePosition().y - SCREEN_HEIGHT / 2) * -1 < (read_blockPositionList[i][0].y + BLOCKSIZE_Y / 2))
		//	{
		//		gridIndex_Y[1] = i;
		//		break;
		//	}
		//}

		//cutAndPaste.SetPos(
		//	read_blockPositionList[gridIndex_Y[1]][gridIndex_X[1]].x,
		//	read_blockPositionList[gridIndex_Y[1]][gridIndex_X[1]].y, 0);




		if (inputSystem->GetRelease(MK_LEFT))
		{
			/*int clickBlockIndex_X[2] = 0;
			int clickBlockIndex_Y[2] = 0;*/

			



			////範囲を3*3で納める
			////x軸
			//if (std::abs(gridIndex_X[0] - gridIndex_X[1]) > 3)
			//{
			//	if (gridIndex_X[0] - gridIndex_X[1] > 0)
			//	{
			//		gridIndex_X[1] = gridIndex_X[0] + 3;
			//	}
			//	else
			//	{
			//		gridIndex_X[1] = gridIndex_X[0] - 3;
			//	}

			//}

			////y軸
			//if (std::abs(gridIndex_Y[0] - gridIndex_Y[1]) > 3)
			//{
			//	if (gridIndex_Y[0] - gridIndex_Y[1] > 0)
			//	{
			//		gridIndex_Y[1] = gridIndex_Y[0] + 3;
			//	}
			//	else
			//	{
			//		gridIndex_Y[1] = gridIndex_Y[0] - 3;
			//	}

			//}

			//cutAndPaste.SetReleaseIndex(gridIndex_X[1], gridIndex_Y[1]);

			


			

		}

		
	}

	//------------------------------------------


	//トリガー更新
	triggerFlg_O = triggerFlg_N;

	//右クリック(トリガー方式の切り替え)
	if (inputSystem->GetTrigger(MK_RIGHT))
	{
		triggerFlg_N = true;
	}
	else
	{
		triggerFlg_N = false;
	}

	//トリガー発生
	if (triggerFlg_O == false && triggerFlg_N == true)
	{
		triggerFlg_T = true;
	}
	else
	{
		triggerFlg_T = false;
	}

	//トリガーが立っていたら
	if (triggerFlg_T == true)
	{
		//加速フラグの状態に合わせて状態を入れ替える
		if (accelerationFlg == true)		//加速状態
		{
			accelerationFlg = false;
			//background.SetColor(StageBG_Glay.x, StageBG_Glay.y, StageBG_Glay.z, StageBG_Glay.a);
		}
		else if (accelerationFlg == false)	//通常状態
		{
			accelerationFlg = true;
			//background.SetColor(StageBG_Blue.x, StageBG_Blue.y, StageBG_Blue.z, StageBG_Blue.a);
		}

	}

	DirectX::XMFLOAT4 color = background.GetColor();

	//通常->加速状態
	if (accelerationFlg == true)
	{
		//色が変更後の状態よりも大きい値なら
		if (color.x > StageBG_Blue.x ||
			color.y > StageBG_Blue.y ||
			color.z > StageBG_Blue.z ||
			color.w > StageBG_Blue.a)
		{
			//(変更前-変更後)の差の絶対値 / 変化に要するフレーム数
			color.x -= std::abs((StageBG_Glay.x - StageBG_Blue.x)) / 20;
			color.y -= std::abs((StageBG_Glay.y - StageBG_Blue.y)) / 20;
			color.z -= std::abs((StageBG_Glay.z - StageBG_Blue.z)) / 20;
			color.w -= std::abs((StageBG_Glay.a - StageBG_Blue.a)) / 20;
		}
		else//変更後の値以下になったら
		{
			color.x = StageBG_Blue.x;
			color.y = StageBG_Blue.y;
			color.z = StageBG_Blue.z;
			color.w = StageBG_Blue.a;
		}
	}
	//加速状態->通常
	else if (accelerationFlg == false)
	{
		//色が変更後の状態よりも小さい値なら
		if (color.x < StageBG_Glay.x ||
			color.y < StageBG_Glay.y ||
			color.z < StageBG_Glay.z ||
			color.w < StageBG_Glay.a)
		{
			//(変更前-変更後)の差の絶対値 / 変化に要するフレーム数
			color.x += std::abs((StageBG_Blue.x - StageBG_Glay.x)) / 20;
			color.y += std::abs((StageBG_Blue.y - StageBG_Glay.y)) / 20;
			color.z += std::abs((StageBG_Blue.z - StageBG_Glay.z)) / 20;
			color.w += std::abs((StageBG_Blue.a - StageBG_Glay.a)) / 20;
		}
		else//変更後の値以上になったら
		{
			color.x = StageBG_Glay.x;
			color.y = StageBG_Glay.y;
			color.z = StageBG_Glay.z;
			color.w = StageBG_Glay.a;
		}
	}



	background.SetColor(color.x, color.y, color.z, color.w);

	return 0;
}

int StageScene::Draw()
{
	background.Draw();
	////ブロックを表示
	//for (int x = 0; x < STAGE_X; x++)
	//{
	//	for (int y = 0; y < STAGE_Y; y++)
	//	{
	//		grids[x][y].Draw();
	//	}
	//}

	holdAreaFlame.Draw();

	for (int i = 0; i < blocks.size(); i++)
	{
		
		blocks[i]->Draw();
	}
	coin.Draw();
	ball.Draw();

	for (auto& o : cannons)
	{
		o->Draw();
	}

	optionButton.Draw();

	gorl.Draw();

	if (cutAndPaste.GetCutModeFlg() == true)
	{
		cutAndPaste.Draw();
		cutButton.Draw();
	}

	retryButton.Draw();

	for (auto& o : holdAreas)
	{
		o->Draw();
	}

	return 0;
}

int StageScene::End()
{
	//vector型の配列を解放
	for (int i = 0; i < blocks.size(); i++)
	{
		delete blocks[i];
	}

	for (auto& o : cannons)
	{
		delete o;
	}

	for (auto& o : holdAreas)
	{
		delete o;
	}

	blocks.clear();

	cannons.clear();

	holdAreas.clear();
	//holdAreas.resize(5,nullptr);
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
		//左上から右下へ見ている

		read_blockPositionList = read_json["blockPosition"].get<vector<vector<VECTOR2>>>();
		//左下から右上へ見ている

		//read_blockPositionListの並び順（左下から右上へ）に合わせる
		std::reverse(read_gridStateList.begin(), read_gridStateList.end());
	}
	else
	{
		//cout << "ファイルの読み込みに失敗しました" << endl;
		//読み込めなかった場合、ウィンドウを表示
		//MessageBoxA(NULL, "ファイルの読み込みに失敗しました", "確認", MB_OK);
		//MessageBoxA(NULL, "現在制作中", "確認", MB_OK);

	}

	int cannonNum = 0;

	//BlockBaseに対応する形に変換
	for (int i = 0; i < read_gridStateList.size(); i++)//縦方向
	{
		for (int j = 0; j < read_gridStateList[i].size(); j++)//横方向
		{
			//index番号を求めてBlockBaceに代入
			switch (read_gridStateList[i][j])
			{
			case STICKY_BLOCK: //粘着ブロック

				blocks.emplace_back(new BlockBace((STAGE_X * i + j), STICKY_BLOCK));

				break;
			case SLIP_BLOCK: //滑るブロック
				blocks.emplace_back(new BlockBace((STAGE_X * i + j), SLIP_BLOCK));
				break;
			case UNBREAK_BLOCK: //破壊不可ブロック
				blocks.emplace_back(new BlockBace((STAGE_X * i + j), UNBREAK_BLOCK));
				break;
			case CANNON:
				cannons.emplace_back(new Cannon(manager->GetWorldNumber(), manager->GetStageNumber(), (STAGE_X * i + j), cannonNum));
				cannonNum++;
				break;
			defalt:  //その他の状態

				//blocks[j][i] = new BlockBace((STAGE_X * i + j), EMPTY);
				break;
			}
		}
	}

}

//移動方向の変更
void StageScene::UpdateMoveDir()
{

	if (hitBlockType[0] == GORL)//ボールの前にゴールブロックがあれば
	{
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}
	//最後に触れたブロックを保存　前＞右＞左
	if (hitBlockType[3] == STICKY_BLOCK)
	{
		prv_index = hitSafe[3];
	}
	else if (hitBlockType[2] == STICKY_BLOCK)
	{
		prv_index = hitSafe[2];
	}

	if (hitBlockType[0] == STICKY_BLOCK)
	{
		prv_index = hitSafe[0];
	}



	if (hitBlockType[0] != NULLBLOCK && hitBlockType[1] != NULLBLOCK && hitBlockType[2] != NULLBLOCK && hitBlockType[3] != NULLBLOCK) {//四方にブロックがあれば
		// すべて true の場合の処理
		ball.SetMoveDir(STOP);
	}
	else
	{
		//跳ね返り
		if (hitBlockType[0] == SLIP_BLOCK || hitBlockType[0] == UNBREAK_BLOCK)
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


		if (hitBlockType[3] != NULLBLOCK)//右にブロックがある
		{
			if (hitBlockType[3] == SLIP_BLOCK || hitBlockType[2] == SLIP_BLOCK)//右にスライドブロックがあれば
			{
				if (hitBlockType[0] == NULLBLOCK)//前にブロックがなければ
				{
					prv_index = -1;
					ball.Move();
				}
			}

			if (hitBlockType[3] == STICKY_BLOCK)//右にスライドブロックがあれば
			{

				if (hitBlockType[0] != NULLBLOCK)//前にブロックがある
				{
					if (hitBlockType[2] != NULLBLOCK)//左にブロックがある
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
						ball.SetMoveDir((center.y > blocks[hitSafe[3]]->GetPos().y) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.x > blocks[hitSafe[3]]->GetPos().x) ? RIGHT : LEFT);
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
				if (prv_index >= 0 && hitBlockType[2] == NULLBLOCK)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index]->GetPos().x) ? DOWN : UP);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index]->GetPos().y) ? RIGHT : LEFT);
					}
				}
			}
			else//ボールが左回りなら
			{
				if (prv_index >= 0 && hitBlockType[2] != NULLBLOCK && hitBlockType[0] != NULLBLOCK)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index]->GetPos().x) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index]->GetPos().y) ? LEFT : RIGHT);
					}
				}
				else if (prv_index >= 0 && hitBlockType[2] == NULLBLOCK)
				{
					if (_moveDir == RIGHT || _moveDir == LEFT) {
						ball.SetMoveDir((center.x > blocks[prv_index]->GetPos().x) ? UP : DOWN);
					}
					else {
						ball.SetMoveDir((center.y > blocks[prv_index]->GetPos().y) ? LEFT : RIGHT);
					}
				}
			}
		}
	}
}

//周囲8マスのあたり判定を取る
void StageScene::CheckSurroundingCollisions()
{
	// 周囲の8マスのあたり判定を更新
	surroundingBlocks.clear();
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//左上
	surroundingBlocks.emplace_back(center.x, center.y + BLOCKSIZE_Y);          //上
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y + BLOCKSIZE_Y);//右上
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y);          //左
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y);          //右
	surroundingBlocks.emplace_back(center.x - BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//左下
	surroundingBlocks.emplace_back(center.x, center.y - BLOCKSIZE_Y);          //下
	surroundingBlocks.emplace_back(center.x + BLOCKSIZE_X, center.y - BLOCKSIZE_Y);//右下

	for (int i = 0; i < 4; i++)
	{
		hitIndex[i] = -1;
		hitFlgs[i] = false;
		hitSafe[i] = -1;
		hitBlockType[i] = NULLBLOCK;
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

void StageScene::SetGridStateList(std::vector<std::vector<int>> _gridStateList)
{
	read_gridStateList = _gridStateList;
}

std::vector<std::vector<int>> StageScene::GetGridStateList()
{
	return read_gridStateList;
}

//１対１のあたり判定
bool StageScene::Collision(BlockBace* obj1/*ステージのブロック*/, const std::pair<float, float>& obj2)
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
std::vector<BlockBace*> StageScene::GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks)
{
	std::vector<BlockBace*> result;
	for (size_t i = 0; i < blocks.size(); i++) {
		DirectX::XMFLOAT3 blockPos = blocks[i]->GetPos();
		for (size_t j = 0; j < surroundingBlocks.size(); j++) { // `surroundingBlocks` のサイズに基づいてループ
			if (std::abs(blockPos.x - surroundingBlocks[j].first) < 0.1f && // `.first` に変更
				std::abs(blockPos.y - surroundingBlocks[j].second) < 0.1f) { // `.second` に変更
				result.push_back(blocks[i]);
				break;
			}
		}
	}
	return result;
}
