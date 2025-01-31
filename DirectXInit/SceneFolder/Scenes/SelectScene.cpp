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


	//�߂�{�^��
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-860.0f, 440.0f, 0.0f);
	backButton.SetSize(50.0f, 50.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i
	backGround.Init(L"asset/Background/�ǎ�_01.png");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

	stateNum = WOELDSELECTSCENE;

	return 0;
}

int SelectScene::Update()
{
	//���[���h�A�X�e�[�W�Z���N�g
	switch (stateNum)
	{
	case WOELDSELECTSCENE:
		/*��������
		�p�\�R���̃f�B�X�v���C�̊g��E�k���{���ɂ���ă}�E�X�J�[�\���̍��W���{���̒l�ƈႤ�l�ɂȂ邱�Ƃ�����*/
		
		//�N���b�N���ꂽ��
		if (inputSystem->GetTrigger(MK_LEFT))
		{
			for (int i = 0; i < 6; i++)
			{
				//�N���b�N���ꂽx���W�������ɂ�������
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
							//���삳��Ă��Ȃ��|��\��
							MessageBoxA(NULL, "���ݐ��쒆", "�m�F", MB_OK);
							//worldNum = WORLD2;
							break;
						case 2:
							//���삳��Ă��Ȃ��|��\��
							MessageBoxA(NULL, "���ݐ��쒆", "�m�F", MB_OK);
							//worldNum = WORLD3;
							break;
						case 3:
							//���삳��Ă��Ȃ��|��\��
							MessageBoxA(NULL, "���ݐ��쒆", "�m�F", MB_OK);
							//worldNum = WORLD4;
							break;
						case 4:
							//���삳��Ă��Ȃ��|��\��
							MessageBoxA(NULL, "���ݐ��쒆", "�m�F", MB_OK);
							//worldNum = WORLD5;
							break;
						case 5:
							//���삳��Ă��Ȃ��|��\��
							MessageBoxA(NULL, "���ݐ��쒆", "�m�F", MB_OK);
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
		//�N���b�N���ꂽ��
		if (inputSystem->GetTrigger(MK_LEFT))
		{
			for (int i = 0; i < 5; i++)
			{
				//�N���b�N���ꂽx���W�������ɂ�������
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

		//���[���h�ԍ��ƃX�e�[�W�ԍ����Z�b�g
		//SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetWorldNumber(WORLD2);
		SceneManager::GetInstance()->SetStageNumber(stageNum);

		//SceneManager::GetInstance()->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		SceneManager::GetInstance()->ChangeScene(STAGE);

		break;
	}

	//�߂�{�^��
	if (inputSystem->GetTrigger(MK_LEFT))
	{
		//�N���b�N���ꂽx���W�������ɂ�������
		if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (backButton.GetPos().x - backButton.GetSize().x / 2) &&
			inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (backButton.GetPos().x + backButton.GetSize().x / 2))
		{
			//
			if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (backButton.GetPos().y - backButton.GetSize().y / 2) &&
				(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (backButton.GetPos().y + backButton.GetSize().y / 2))
			{
				switch (stateNum)
				{
				case WOELDSELECTSCENE://�^�C�g���V�[���ɖ߂�
					SceneManager::GetInstance()->ChangeScene(TITLE);
					break;
				case STAGESELECTSCENE: //���[���h�Z���N�g�ɖ߂�
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
	//D3D_StartRender();   //�`��J�n

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
