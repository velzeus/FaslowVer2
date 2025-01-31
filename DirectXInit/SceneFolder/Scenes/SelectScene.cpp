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
		world_image[i].Init(L"asset/number.png", 10, 1);
		world_image[i].SetSize(100.0f, 100.0f, 0.0f);
		world_image[i].SetAngle(0.0f);
		world_image[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		world_image[i].numU = i + 1;
	}

	//ワールドごとに違うもの
	//ワールド1
	world_image[0].SetPos(-150, 100, 0.0f);
	
	//ワールド2
	world_image[1].SetPos(0, 100, 0.0f);

	//ワールド3
	world_image[2].SetPos(150, 100, 0.0f);

	//ワールド4
	world_image[3].SetPos(-150, -100, 0.0f);
	
	//ワールド5
	world_image[4].SetPos(0, -100, 0.0f);

	//ワールド6
	world_image[5].SetPos(150, -100, 0.0f);
	
	//ステージで、同じ値のもの
	for (int i = 0; i < 5; i++)
	{
		stage_image[i].Init(L"asset/number.png", 10, 1);
		stage_image[i].SetSize(100.0f, 100.0f, 0.0f);
		stage_image[i].SetAngle(0.0f);
		stage_image[i].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		stage_image[i].numU = i + 1;
	}

	//ステージごとに違うもの
	//ステージ1
	stage_image[0].SetPos(-150, 100, 0.0f);

	//ステージ2
	stage_image[1].SetPos(0, 100, 0.0f);

	//ステージ3
	stage_image[2].SetPos(150, 100, 0.0f);

	//ステージ4
	stage_image[3].SetPos(-75, -100, 0.0f);

	//ステージ5
	stage_image[4].SetPos(75, -100, 0.0f);


	//戻るボタン
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-860.0f, 440.0f, 0.0f);
	backButton.SetSize(50.0f, 50.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//背景
	backGround.Init(L"asset/Background/壁紙_01.png");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

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
				if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (world_image[i].GetPos().x - world_image[i].GetSize().x / 2) &&
					inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (world_image[i].GetPos().x + world_image[i].GetSize().x / 2))
				{
					//
					if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (world_image[i].GetPos().y - world_image[i].GetSize().y / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (world_image[i].GetPos().y + world_image[i].GetSize().y / 2))
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
				if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (stage_image[i].GetPos().x - stage_image[i].GetSize().x / 2) &&
					inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (stage_image[i].GetPos().x + stage_image[i].GetSize().x / 2))
				{
					//
					if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (stage_image[i].GetPos().y - stage_image[i].GetSize().y / 2) &&
						(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (stage_image[i].GetPos().y + stage_image[i].GetSize().y / 2))
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
			world_image[i].Draw();
		}

		break;
	case STAGESELECTSCENE:

		for (int i = 0; i < 5; i++)
		{
			stage_image[i].Draw();
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
	//world_image[0].Uninit();
	return 0;
}
