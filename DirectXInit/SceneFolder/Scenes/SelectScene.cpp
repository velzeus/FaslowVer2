#include "SelectScene.h"
//#include"StageScene.h"

SelectScene::SelectScene() :
	Scene(SCENENAME::SELECT)
{
	stateNum = WOELDSELECTSCENE;
	
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
		selectImage_world[i].Init(L"asset/UI/Flame2.png"/*, 10, 1*/);
		selectImage_world[i].SetSize(400.0f, 100.0f, 0.0f);
		selectImage_world[i].SetAngle(0.0f);
		selectImage_world[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_world[i].numU = i + 1;

		selectImage_world[i].SetPos(635, (selectImage_world[i].GetSize().y + 20) * (2 - i), 0);

	}

	//ワールドごとに違うもの
	////ワールド1
	//selectImage_world[0].SetPos(-635, 50, 0.0f);
	//
	////ワールド2
	//selectImage_world[1].SetPos(0, 50, 0.0f);

	////ワールド3
	//selectImage_world[2].SetPos(635, 50, 0.0f);

	////ワールド4
	//selectImage_world[3].SetPos(-650, -400, 0.0f);
	//
	////ワールド5
	//selectImage_world[4].SetPos(0, -400, 0.0f);

	////ワールド6
	//selectImage_world[5].SetPos(650, -400, 0.0f);

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
	x,704 y,476

	ステージの名前　座標　x,-835 y,-178
	大きさ　x,880 y,161

	ステージセレクトボタン　大きさ x,622 y,121
	座標（ステージ1）　x,166 y,339

	ステージ2 x,166 y,2

	ステージ5 x," y,219

	*/
	
	//ステージで、同じ値のもの
	for (int i = 0; i < 5; i++)
	{
		selectImage_stage[i].Init(L"asset/number.png", 10, 1);
		selectImage_stage[i].SetSize(100.0f, 100.0f, 0.0f);
		selectImage_stage[i].SetAngle(0.0f);
		selectImage_stage[i].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		selectImage_stage[i].numU = i + 1;

		selectImage_stage[i].SetPos(635, (selectImage_stage[i].GetSize().y + 20) * (2 - i), 0);
	}

	//ステージごとに違うもの
	////ステージ1
	//selectImage_stage[0].SetPos(-150, 100, 0.0f);

	////ステージ2
	//selectImage_stage[1].SetPos(0, 100, 0.0f);

	////ステージ3
	//selectImage_stage[2].SetPos(150, 100, 0.0f);

	////ステージ4
	//selectImage_stage[3].SetPos(-75, -100, 0.0f);

	////ステージ5
	//selectImage_stage[4].SetPos(75, -100, 0.0f);


	//戻るボタン
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-860.0f, 440.0f, 0.0f);
	backButton.SetSize(50.0f, 50.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//背景
	backGround.Init(L"asset/Background/壁紙_01.png");
	//backGround.Init(L"asset/StageSelect/タイトルアニメーション_背景2.gif");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

	//ステージ画面

	//ステージ名

	//スタートボタン

	stateNum = WOELDSELECTSCENE;

	return 0;

	
}

int SelectScene::Update()
{
	//ワールド、ステージセレクト
	switch (stateNum)
	{
	case WOELDSELECTSCENE:
		/*メモ書き
		パソコンのディスプレイの拡大・縮小倍率によってマウスカーソルの座標が本来の値と違う値になることがある*/
		
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
							stateNum = STAGESELECTSCENE;
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

					}
				}
				
			}

		}

		break;
	case STAGESELECTSCENE:
		//クリックされたら
		if (inputSystem->GetTrigger(MK_LEFT))
		{
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

						stateNum = SETSTAGE;

					}
				}

			}

		}
		
		break;
	case SETSTAGE:

		//ワールド番号とステージ番号をセット
		//SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetWorldNumber(WORLD2);
		SceneManager::GetInstance()->SetStageNumber(stageNum);

		//SceneManager::GetInstance()->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		SceneManager::GetInstance()->ChangeScene(STAGE);

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
				case WOELDSELECTSCENE://タイトルシーンに戻る
					SceneManager::GetInstance()->ChangeScene(TITLE);
					break;
				case STAGESELECTSCENE: //ワールドセレクトに戻る
					stateNum = WOELDSELECTSCENE;
					worldNum = NOTDONE_WORLD;
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
	case WOELDSELECTSCENE:
		for (int i = 0; i < 6; i++)
		{
			selectImage_world[i].Draw();
		}

		break;
	case STAGESELECTSCENE:

		for (int i = 0; i < 5; i++)
		{
			selectImage_stage[i].Draw();
		}
		break;
	case SETSTAGE:
		break;
	}

	backButton.Draw();

	return 0;
}

int SelectScene::End()
{
	//selectImage_world[0].Uninit();
	return 0;
}
