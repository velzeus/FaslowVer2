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
	//world1�̉摜
	//imagePos = { ,-100 };

	//���[���h�ŁA�����l�̂���
	for (int i = 0; i < 6; i++)
	{
		world_image[i].Init(L"asset/number.png", 10, 1);
		world_image[i].SetSize(100.0f, 100.0f, 0.0f);
		world_image[i].SetAngle(0.0f);
		world_image[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		world_image[i].numU = i + 1;
	}

	//���[���h���ƂɈႤ����
	//���[���h1
	world_image[0].SetPos(-150, 100, 0.0f);
	
	//���[���h2
	world_image[1].SetPos(0, 100, 0.0f);

	//���[���h3
	world_image[2].SetPos(150, 100, 0.0f);

	//���[���h4
	world_image[3].SetPos(-150, -100, 0.0f);
	
	//���[���h5
	world_image[4].SetPos(0, -100, 0.0f);

	//���[���h6
	world_image[5].SetPos(150, -100, 0.0f);
	

	//�X�e�[�W�ŁA�����l�̂���
	for (int i = 0; i < 5; i++)
	{
		stage_image[i].Init(L"asset/number.png", 10, 1);
		stage_image[i].SetSize(100.0f, 100.0f, 0.0f);
		stage_image[i].SetAngle(0.0f);
		stage_image[i].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		stage_image[i].numU = i + 1;
	}

	//�X�e�[�W���ƂɈႤ����
	//�X�e�[�W1
	stage_image[0].SetPos(-150, 100, 0.0f);

	//�X�e�[�W2
	stage_image[1].SetPos(0, 100, 0.0f);

	//�X�e�[�W3
	stage_image[2].SetPos(150, 100, 0.0f);

	//�X�e�[�W4
	stage_image[3].SetPos(-75, -100, 0.0f);

	//�X�e�[�W5
	stage_image[4].SetPos(75, -100, 0.0f);


	return 0;
}

int SelectScene::Update()
{
	mouseInput.Update();

	switch (stateNum)
	{
	case WOELDSELECTSCENE:
		
		//�N���b�N���ꂽ��
		if (mouseInput.IsLeftButtonDown())
		{
			for (int i = 0; i < 6; i++)
			{
				//�N���b�N���ꂽx���W�������ɂ�������
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
		//�N���b�N���ꂽ��
		if (mouseInput.IsLeftButtonDown())
		{
			for (int i = 0; i < 5; i++)
			{
				//�N���b�N���ꂽx���W�������ɂ�������
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

		//���[���h�ԍ��ƃX�e�[�W�ԍ����Z�b�g
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
	//D3D_StartRender();   //�`��J�n

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
	

	

	//D3D_FinishRender();  //�`��I��

	return 0;
}

int SelectScene::End()
{
	world_image[0].Uninit();
	//D3D_Release();   //DirectX���I��
	return 0;
}
