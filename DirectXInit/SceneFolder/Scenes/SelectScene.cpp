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
		selectImage_world[i].Init(L"asset/UI/Flame2.png"/*, 10, 1*/);
		selectImage_world[i].SetSize(400.0f, 100.0f, 0.0f);
		selectImage_world[i].SetAngle(0.0f);
		selectImage_world[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_world[i].numU = i + 1;

		selectImage_world[i].SetPos(635, (selectImage_world[i].GetSize().y + 20) * (2 - i), 0);

	}

	//���[���h���ƂɈႤ����
	////���[���h1
	//selectImage_world[0].SetPos(-635, 50, 0.0f);
	//
	////���[���h2
	//selectImage_world[1].SetPos(0, 50, 0.0f);

	////���[���h3
	//selectImage_world[2].SetPos(635, 50, 0.0f);

	////���[���h4
	//selectImage_world[3].SetPos(-650, -400, 0.0f);
	//
	////���[���h5
	//selectImage_world[4].SetPos(0, -400, 0.0f);

	////���[���h6
	//selectImage_world[5].SetPos(650, -400, 0.0f);

	/*
	������
	World��I�񂾂�X�e�[�W1���I�΂�Ă����Ԃ̃X�e�[�W�Z���N�g�ɓ���
	�X�e�[�W��I�񂾏�ԂŃX�^�[�g�{�^���������ƃX�e�[�W�ɓ���
	�X�^�[�g�{�^���͉E��

	UI�̒������W
	�X�e�[�W��ʁ@x,-835 y,339
	�傫���@x,880 y,491
	
	�߂�{�^���@x,-836,y,476
	�傫�� 78�@�l��
	
	���j���[�@�傫���@��Ɠ���
	x,704 y,476

	�X�e�[�W�̖��O�@���W�@x,-835 y,-178
	�傫���@x,880 y,161

	�X�e�[�W�Z���N�g�{�^���@�傫�� x,622 y,121
	���W�i�X�e�[�W1�j�@x,166 y,339

	�X�e�[�W2 x,166 y,2

	�X�e�[�W5 x," y,219

	*/
	
	//�X�e�[�W�ŁA�����l�̂���
	for (int i = 0; i < 5; i++)
	{
		selectImage_stage[i].Init(L"asset/number.png", 10, 1);
		selectImage_stage[i].SetSize(100.0f, 100.0f, 0.0f);
		selectImage_stage[i].SetAngle(0.0f);
		selectImage_stage[i].SetColor(1.0f, 1.0f, 0.0f, 1.0f);
		selectImage_stage[i].numU = i + 1;

		selectImage_stage[i].SetPos(635, (selectImage_stage[i].GetSize().y + 20) * (2 - i), 0);
	}

	//�X�e�[�W���ƂɈႤ����
	////�X�e�[�W1
	//selectImage_stage[0].SetPos(-150, 100, 0.0f);

	////�X�e�[�W2
	//selectImage_stage[1].SetPos(0, 100, 0.0f);

	////�X�e�[�W3
	//selectImage_stage[2].SetPos(150, 100, 0.0f);

	////�X�e�[�W4
	//selectImage_stage[3].SetPos(-75, -100, 0.0f);

	////�X�e�[�W5
	//selectImage_stage[4].SetPos(75, -100, 0.0f);


	//�߂�{�^��
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-860.0f, 440.0f, 0.0f);
	backButton.SetSize(50.0f, 50.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i
	backGround.Init(L"asset/Background/�ǎ�_01.png");
	//backGround.Init(L"asset/StageSelect/�^�C�g���A�j���[�V����_�w�i2.gif");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

	//�X�e�[�W���

	//�X�e�[�W��

	//�X�^�[�g�{�^��

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
