#include "SelectScene.h"
//#include"StageScene.h"

SelectScene::SelectScene() :
	Scene(SCENENAME::SELECT)
{
	stateNum = WORLDSELECTSCENE;
	
}

SelectScene::~SelectScene()
{
}

int SelectScene::Start()
{
	//inputSystem = MouseInput::GetInstance();

	inputSystem = TS::TS_InputSystem::GetInstance();

	//ワールドで、同じ値のもの
	for (int i = 0; i < 6; i++)
	{
		//ワールドセレクトボタン
		selectImage_world[i].Init(L"asset/UI/Flame2.png"/*, 10, 1*/);
		selectImage_world[i].SetSize(622.0f, 120.0f, 0.0f);
		selectImage_world[i].SetAngle(0.0f);
		selectImage_world[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_world[i].numU = i + 1;

		selectImage_world[i].SetPos(550, ((selectImage_world[i].GetSize().y + 10) * -i /*- 216*/) + 300, 0);

		//Worldの文字
		worldNameImage[i].Init(L"asset/UI/WorldSelect.png", 2, 1);
		worldNameImage[i].SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
		worldNameImage[i].SetSize(325, 100, 0);
		worldNameImage[i].SetAngle(0);
		worldNameImage[i].SetColor(1, 1, 1, 1);
		worldNameImage[i].numU = 0;

		//番号
		numberText[i].Init(L"asset/UI/suuji-1.png", 1, 11);
		numberText[i].SetSize(100, 100, 0);
		numberText[i].SetAngle(0);
		numberText[i].SetColor(1, 1, 1, 1);
		numberText[i].numV = i + 1;

		//635
	}

	/*
	メモ欄
	Worldを選んだらステージ1が選ばれている状態のステージセレクトに入る
	ステージを選んだ状態でスタートボタンを押すとステージに入る
	スタートボタンは右下

	UIの中央座標
	ステージ画面　x,-835 y,339
	大きさ　x,880 y,491
	
	戻るボタン　x,-836,y,476
	大きさ 78　四方
	
	メニュー　大きさ　上と同じ
	x,-704 y,476

	ステージの名前　座標　x,-835 y,-178
	大きさ　x,880 y,161

	ステージセレクトボタン　大きさ x,622 y,121
	座標（ステージ1）　x,166 y,339

	ステージ2 x,166 y,2

	差　337

	ステージ5 x," y,-219

	*/
	
	//ステージで、同じ値のもの
	for (int i = 0; i < 5; i++)
	{
		//ステージセレクトボタン
		selectImage_stage[i].Init(L"asset/UI/Flame2.png");
		selectImage_stage[i].SetSize(622.0f, 120.0f, 0.0f);
		selectImage_stage[i].SetAngle(0.0f);
		selectImage_stage[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_stage[i].numU = i + 1;

		//0番を基点として考える
		selectImage_stage[i].SetPos(550, ((selectImage_world[i].GetSize().y + 10) * -i /*- 216*/) + 300, 0);
		/*(166, (selectImage_stage[i].GetSize().y * -i - 216) + 339, 0);*/

		//Stageの文字
		stageNameImage[i].Init(L"asset/UI/StageSelect.png", 2, 1);
		stageNameImage[i].SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
		stageNameImage[i].SetSize(325, 100, 0);
		stageNameImage[i].SetAngle(0);
		stageNameImage[i].SetColor(1, 1, 1, 1);
		stageNameImage[i].numU = 0;
	}

	//戻るボタン
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-836.0f, 476.0f, 0.0f);
	backButton.SetSize(78.0f, 78.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//背景
	backGround.Init(L"asset/background/Background_blue.png");
	//backGround.Init(L"asset/StageSelect/タイトルアニメーション_背景2.gif");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

	//ステージ画面
	stageTexture.Init(L"asset/Background/haikei2.png");
	stageTexture.SetSize(1155,650,0);
	stageTexture.SetPos(-350, (selectImage_stage[0].GetPos().y + selectImage_stage[0].GetSize().y / 2) - stageTexture.GetSize().y / 2 + 20, 0);
	stageTexture.SetAngle(0);
	stageTexture.SetColor(1, 1, 1, 1);

	//ステージ名の枠
	stageNameFlame.Init(L"asset/UI/Flame2.png");
	stageNameFlame.SetPos(-350, -378, 0);
	stageNameFlame.SetSize(1067, 161, 0);
	stageNameFlame.SetAngle(0);
	stageNameFlame.SetColor(1, 1, 1, 1);

	//ステージ名
	stageName.Init(L"asset/UI/StageSelect.png", 2, 1);
	stageName.SetPos(stageNameFlame.GetPos().x, stageNameFlame.GetPos().y, 0);
	stageName.SetSize(488, 150, 0);
	stageName.SetAngle(0);
	stageName.SetColor(1, 1, 1, 1);

	//ステージ名の番号
	stageNameNumber.Init(L"asset/UI/suuji-1.png", 1, 11);
	stageNameNumber.SetSize(150, 150, 0);
	stageNameNumber.SetPos((stageName.GetPos().x + stageName.GetSize().x / 2 + stageNameNumber.GetSize().x / 2), stageName.GetPos().y-3, 0);
	stageNameNumber.SetAngle(0);
	stageNameNumber.SetColor(1, 1, 1, 1);
	stageNameNumber.numV = 1;

	//スタートボタン
	startButton.Init(L"asset/UI/start.png");
	startButton.SetPos(704.0f, -400.0f, 0.0f);
	startButton.SetSize(311.0f, 100.0f, 0.0f);
	startButton.SetAngle(0);
	startButton.SetColor(1, 1, 1, 1);

	//メニューボタン
	menuButton.Init(L"asset/UI/Hamburger_icon_100x100.png");
	menuButton.SetPos(-704.0f, 476.0f, 0.0f);
	menuButton.SetSize(78.0f, 78.0f, 0.0f);
	menuButton.SetAngle(0);
	menuButton.SetColor(1, 1, 1, 1);

	//動かす用の枠
	moveFlame.Init(L"asset/UI/Flame2.png");
	moveFlame.SetAngle(0);
	moveFlame.SetColor(1, 1, 1, 1);

	stageNum = STAGE1;

	stateNum = WORLDSELECTSCENE;

	normalizedDirection = {};
	targetPos = {};
	targetScale = {};

	moveSpeed = 0;

	return 0;
}

int SelectScene::Update()
{
	//ワールド、ステージセレクト
	switch (stateNum)
	{
	case WORLDSELECTSCENE:
		/*メモ書き
		パソコンのディスプレイの拡大・縮小倍率によってマウスカーソルの座標が本来の値と違う値になることがある*/
		
		for (int i = 0; i < 6; i++)
		{
			//番号の座標をセット
			numberText[i].SetPos(worldNameImage[i].GetPos().x + worldNameImage[i].GetSize().x / 2 + numberText[i].GetSize().x / 2,
				worldNameImage[i].GetPos().y - 2, 0);
		}
	
		//クリックされたら
		if (inputSystem->GetTrigger(MK_LEFT))
		{
			for (int i = 0; i < 6; i++)
			{
				//クリックされたx座標が内側にあったら
				if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (selectImage_world[i].GetPos().x - selectImage_world[i].GetSize().x / 2) &&
					inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (selectImage_world[i].GetPos().x + selectImage_world[i].GetSize().x / 2))
				{
					//
					if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (selectImage_world[i].GetPos().y - selectImage_world[i].GetSize().y / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (selectImage_world[i].GetPos().y + selectImage_world[i].GetSize().y / 2))
					{
						switch (i)
						{
						case 0:
							worldNum = WORLD1;
							//stateNum = STAGESELECTSCENE;
							break;
						case 1:
							//制作されていない旨を表示
							MessageBoxA(NULL, "現在制作中", "確認", MB_OK);
							//worldNum = WORLD2;
							break;
						case 2:
							//制作されていない旨を表示
							MessageBoxA(NULL, "現在制作中", "確認", MB_OK);
							//worldNum = WORLD3;
							break;
						case 3:
							//制作されていない旨を表示
							MessageBoxA(NULL, "現在制作中", "確認", MB_OK);
							//worldNum = WORLD4;
							break;
						case 4:
							//制作されていない旨を表示
							MessageBoxA(NULL, "現在制作中", "確認", MB_OK);
							//worldNum = WORLD5;
							break;
						case 5:
							//制作されていない旨を表示
							MessageBoxA(NULL, "現在制作中", "確認", MB_OK);
							//worldNum = WORLD6;
							break;
						}
						
						//stateNum = STAGESELECTSCENE;

						if (i == 0)
						{
							//目標の座標とスケールを取得
							targetPos = { stageNameFlame.GetPos().x ,stageNameFlame.GetPos().y, stageNameFlame.GetPos().z };
							targetScale = { stageNameFlame.GetSize().x,stageNameFlame.GetSize().y, stageNameFlame.GetSize().z };

							//動かす用の枠の座標とサイズの初期値を設定
							moveFlame.SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
							moveFlame.SetSize(selectImage_world[i].GetSize().x, selectImage_world[i].GetSize().y, selectImage_world[i].GetSize().z);

							//座標の方向ベクトル
							DirectX::XMFLOAT3 direction;
							//目標までの方向ベクトルを求める
							direction.x = targetPos.x - moveFlame.GetPos().x;
							direction.y = targetPos.y - moveFlame.GetPos().y;

							//ベクトルの長さを求める
							float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

							//移動速度を求める
							moveSpeed = length / FLAMENUM;

							//正規化した座標用方向ベクトルを求めて代入
							normalizedDirection =
							{
								direction.x / length,
								direction.y / length,
								0
							};

							//--------------------------------------------------------------------------------------------------------

							//大きさの方向ベクトルを求める
							direction.x = targetScale.x - moveFlame.GetSize().x;
							direction.y = targetScale.y - moveFlame.GetSize().y;

							//ベクトルの長さを求める
							length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

							//大きさの変化量
							deltaScale = length / FLAMENUM;

							//正規化した大きさ用方向ベクトルを求めて代入
							normalizedScaleVector =
							{
								direction.x / length,
								direction.y / length,
								0
							};

							stateNum = MOVEFLAME;
						}

					}
				}
			}

		}

		break;
	case STAGESELECTSCENE:
		//クリックされたら
		if (inputSystem->GetTrigger(MK_LEFT))
		{
			//ステージセレクトの枠
			for (int i = 0; i < 5; i++)
			{
				//クリックされたx座標が内側にあったら
				if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (selectImage_stage[i].GetPos().x - selectImage_stage[i].GetSize().x / 2) &&
					inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (selectImage_stage[i].GetPos().x + selectImage_stage[i].GetSize().x / 2))
				{
					//
					if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (selectImage_stage[i].GetPos().y - selectImage_stage[i].GetSize().y / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (selectImage_stage[i].GetPos().y + selectImage_stage[i].GetSize().y / 2))
					{
						switch (i)
						{
						case 0:
							stageNum = STAGE1;
							break;
						case 1:
							stageNum = STAGE2;
							break;
						case 2:
							stageNum = STAGE3;
							break;
						case 3:
							stageNum = STAGE4;
							break;
						case 4:
							stageNum = STAGE5;
							break;
						}

						//番号をセット
						stageNameNumber.numV = i + 1;

					}
				}

			}

			//スタートボタン
			//クリックされたx座標が内側にあったら
			if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (startButton.GetPos().x - startButton.GetSize().x / 2) &&
				inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (startButton.GetPos().x + startButton.GetSize().x / 2))
			{
				//
				if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (startButton.GetPos().y - startButton.GetSize().y / 2) &&
					(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (startButton.GetPos().y + startButton.GetSize().y / 2))
				{
					//状態を変える
					stateNum = SETSTAGE;
				}
			}

		}
		
		break;
	case SETSTAGE:

		//ワールド番号とステージ番号をセット
		//SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetStageNumber(stageNum);

		//SceneManager::GetInstance()->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		SceneManager::GetInstance()->ChangeScene(STAGE);

		break;
	case MOVEFLAME:

		bool arrivedPosFlg= MoveFlame();

		//到着していたら(World->Stageの場合)
		if (arrivedPosFlg == true && worldNum != NOTDONE_WORLD)
		{
			stateNum = STAGESELECTSCENE;
		}
		//(Stage->Worldの場合)
		else if (arrivedPosFlg == true && worldNum == NOTDONE_WORLD)
		{
			stateNum = WORLDSELECTSCENE;
		}
		

		break;
	}

	//戻るボタン
	if (inputSystem->GetTrigger(MK_LEFT))
	{
		//クリックされたx座標が内側にあったら
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (backButton.GetPos().x - backButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (backButton.GetPos().x + backButton.GetSize().x / 2))
		{
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (backButton.GetPos().y - backButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (backButton.GetPos().y + backButton.GetSize().y / 2))
			{
				switch (stateNum)
				{
				case WORLDSELECTSCENE://タイトルシーンに戻る
					SceneManager::GetInstance()->ChangeScene(TITLE);
					break;
				case STAGESELECTSCENE: //ワールドセレクトに戻る

					//目標の座標とスケールを取得
					targetPos = { selectImage_world[worldNum - 1].GetPos().x, selectImage_world[worldNum - 1].GetPos().y, selectImage_world[worldNum - 1].GetPos().z };
					targetScale = { selectImage_world[worldNum - 1].GetSize().x, selectImage_world[worldNum - 1].GetSize().y, selectImage_world[worldNum - 1].GetSize().z };

					//動かす用の枠の座標とサイズの初期値を設定
					moveFlame.SetPos(stageNameFlame.GetPos().x, stageNameFlame.GetPos().y, stageNameFlame.GetPos().z);
					moveFlame.SetSize(stageNameFlame.GetSize().x, stageNameFlame.GetSize().y, stageNameFlame.GetSize().z);

					//座標の方向ベクトル
					DirectX::XMFLOAT3 direction;
					//目標までの方向ベクトルを求める
					direction.x = targetPos.x - moveFlame.GetPos().x;
					direction.y = targetPos.y - moveFlame.GetPos().y;

					//ベクトルの長さを求める
					float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

					//移動速度を求める
					moveSpeed = length / FLAMENUM;

					//正規化した座標用方向ベクトルを求めて代入
					normalizedDirection =
					{
						direction.x / length,
						direction.y / length,
						0
					};

					//--------------------------------------------------------------------------------------------------------

					//大きさの方向ベクトルを求める
					direction.x = targetScale.x - moveFlame.GetSize().x;
					direction.y = targetScale.y - moveFlame.GetSize().y;

					//ベクトルの長さを求める
					length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

					//大きさの変化量
					deltaScale = length / FLAMENUM;

					//正規化した大きさ用方向ベクトルを求めて代入
					normalizedScaleVector =
					{
						direction.x / length,
						direction.y / length,
						0
					};

					stateNum = MOVEFLAME;

					//stateNum = WORLDSELECTSCENE;
					worldNum = NOTDONE_WORLD;//選択の状態をリセット
					break;
				}
			}

		}

	}

	return 0;
}

int SelectScene::Draw()
{
	//D3D_StartRender();   //描画開始

	backGround.Draw();

	switch (stateNum)
	{
	case WORLDSELECTSCENE:
		for (int i = 0; i < 6; i++)
		{
			selectImage_world[i].Draw();
			worldNameImage[i].Draw();
			numberText[i].Draw();
		}

		break;
	case STAGESELECTSCENE:

		for (int i = 0; i < 5; i++)
		{
			selectImage_stage[i].Draw();
			stageNameImage[i].Draw();
			numberText[i].Draw();

		}

		stageTexture.Draw();

		startButton.Draw();

		stageNameFlame.Draw();

		stageName.Draw();
		stageNameNumber.Draw();

		break;
	case SETSTAGE:
		break;
	case MOVEFLAME:
		moveFlame.Draw();
		break;
	}

	

	backButton.Draw();

	menuButton.Draw();

	

	return 0;
}

int SelectScene::End()
{
	//selectImage_world[0].Uninit();
	return 0;
}

bool SelectScene::MoveFlame()
{
	DirectX::XMFLOAT3 pos = moveFlame.GetPos();
	DirectX::XMFLOAT3 scale = moveFlame.GetSize();

	//目標地点へ向かって移動
	pos.x += normalizedDirection.x * moveSpeed;
	pos.y += normalizedDirection.y * moveSpeed;

	//目標の大きさに向かって変化
	scale.x += normalizedScaleVector.x * deltaScale;
	scale.y += normalizedScaleVector.y * deltaScale;

	moveFlame.SetPos(pos.x, pos.y, pos.z);
	moveFlame.SetSize(scale.x, scale.y, scale.z);

	//目標地点に近づいたら
	if (pos.x <= targetPos.x + moveSpeed &&
		pos.x >= targetPos.x - moveSpeed &&
		pos.y <= targetPos.y + moveSpeed &&
		pos.y >= targetPos.y - moveSpeed)
	{
		return true;
	}
	else
	{
		return false;
	}
}
