#include "SelectScene.h"
#include"StageScene.h"

SelectScene::SelectScene() :
	Scene(SCENENAME::SELECT), manager(SceneManager::GetInstance())
{
	stateNum = WOELDSELECTSCENE;
	
}

SelectScene::~SelectScene()
{
}

int SelectScene::Start()
{
	D3D_Create(manager->GetHWND());
	//world1の画像
	//imagePos = { ,-100 };

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


	return 0;
}

int SelectScene::Update()
{
	mouseInput.Update();

	switch (stateNum)
	{
	case WOELDSELECTSCENE:
		
		//クリックされたら
		if (mouseInput.IsLeftButtonDown())
		{
			for (int i = 0; i < 6; i++)
			{
				//クリックされたx座標が内側にあったら
				if (mouseInput.GetClickPosition().x - SCREEN_WIDTH / 2 > (world_image[i].GetPos().x - world_image[i].GetSize().x / 2) &&
					mouseInput.GetClickPosition().x - SCREEN_WIDTH / 2 < (world_image[i].GetPos().x + world_image[i].GetSize().x / 2))
				{
					//
					if ((mouseInput.GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (world_image[i].GetPos().y - world_image[i].GetSize().y / 2) &&
						(mouseInput.GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (world_image[i].GetPos().y + world_image[i].GetSize().y / 2))
					{
						switch (i)
						{
						case 0:
							worldNum = WORLD1;
							break;
						case 1:
							worldNum = WORLD2;
							break;
						case 2:
							worldNum = WORLD3;
							break;
						case 3:
							worldNum = WORLD4;
							break;
						case 4:
							worldNum = WORLD5;
							break;
						case 5:
							worldNum = WORLD6;
							break;
						}
						
						stateNum = STAGESELECTSCENE;

					}
				}
				
			}

		}
		break;
	case STAGESELECTSCENE:
		//クリックされたら
		if (mouseInput.IsLeftButtonDown())
		{
			for (int i = 0; i < 5; i++)
			{
				//クリックされたx座標が内側にあったら
				if (mouseInput.GetClickPosition().x - SCREEN_WIDTH / 2 > (stage_image[i].GetPos().x - stage_image[i].GetSize().x / 2) &&
					mouseInput.GetClickPosition().x - SCREEN_WIDTH / 2 < (stage_image[i].GetPos().x + stage_image[i].GetSize().x / 2))
				{
					//
					if ((mouseInput.GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (stage_image[i].GetPos().y - stage_image[i].GetSize().y / 2) &&
						(mouseInput.GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (stage_image[i].GetPos().y + stage_image[i].GetSize().y / 2))
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
		manager->SetWorldNumber(worldNum);
		manager->SetStageNumber(stageNum);

		manager->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		manager->ChangeScene(STAGE);

		break;
	}


	return 0;
}

int SelectScene::Draw()
{
	//D3D_StartRender();   //描画開始

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
	

	

	//D3D_FinishRender();  //描画終了

	return 0;
}

int SelectScene::End()
{
	world_image[0].Uninit();
	//D3D_Release();   //DirectXを終了
	return 0;
}
