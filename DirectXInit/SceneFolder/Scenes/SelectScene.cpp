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

	//���[���h�ŁA�����l�̂���
	for (int i = 0; i < 6; i++)
	{
		//���[���h�Z���N�g�{�^��
		selectImage_world[i].Init(L"asset/UI/Flame2.png"/*, 10, 1*/);
		selectImage_world[i].SetSize(622.0f, 120.0f, 0.0f);
		selectImage_world[i].SetAngle(0.0f);
		selectImage_world[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_world[i].numU = i + 1;

		selectImage_world[i].SetPos(550, ((selectImage_world[i].GetSize().y + 10) * -i /*- 216*/) + 300, 0);

		//World�̕���
		worldNameImage[i].Init(L"asset/UI/WorldSelect.png", 2, 1);
		worldNameImage[i].SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
		worldNameImage[i].SetSize(325, 100, 0);
		worldNameImage[i].SetAngle(0);
		worldNameImage[i].SetColor(1, 1, 1, 1);
		worldNameImage[i].numU = 0;

		//�ԍ�
		numberText[i].Init(L"asset/UI/suuji-1.png", 1, 11);
		numberText[i].SetSize(100, 100, 0);
		numberText[i].SetAngle(0);
		numberText[i].SetColor(1, 1, 1, 1);
		numberText[i].numV = i + 1;

		//635
	}

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
	x,-704 y,476

	�X�e�[�W�̖��O�@���W�@x,-835 y,-178
	�傫���@x,880 y,161

	�X�e�[�W�Z���N�g�{�^���@�傫�� x,622 y,121
	���W�i�X�e�[�W1�j�@x,166 y,339

	�X�e�[�W2 x,166 y,2

	���@337

	�X�e�[�W5 x," y,-219

	*/
	
	//�X�e�[�W�ŁA�����l�̂���
	for (int i = 0; i < 5; i++)
	{
		//�X�e�[�W�Z���N�g�{�^��
		selectImage_stage[i].Init(L"asset/UI/Flame2.png");
		selectImage_stage[i].SetSize(622.0f, 120.0f, 0.0f);
		selectImage_stage[i].SetAngle(0.0f);
		selectImage_stage[i].SetColor(1.0f, 1.0f, 1.0f, 1.0f);
		//selectImage_stage[i].numU = i + 1;

		//0�Ԃ���_�Ƃ��čl����
		selectImage_stage[i].SetPos(550, ((selectImage_world[i].GetSize().y + 10) * -i /*- 216*/) + 300, 0);
		/*(166, (selectImage_stage[i].GetSize().y * -i - 216) + 339, 0);*/

		//Stage�̕���
		stageNameImage[i].Init(L"asset/UI/StageSelect.png", 2, 1);
		stageNameImage[i].SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
		stageNameImage[i].SetSize(325, 100, 0);
		stageNameImage[i].SetAngle(0);
		stageNameImage[i].SetColor(1, 1, 1, 1);
		stageNameImage[i].numU = 0;
	}

	//�߂�{�^��
	backButton.Init(L"asset/UI/back.png");
	backButton.SetPos(-836.0f, 476.0f, 0.0f);
	backButton.SetSize(78.0f, 78.0f, 0.0f);
	backButton.SetAngle(0.0f);
	backButton.SetColor(1.0f, 1.0f, 1.0f, 1.0f);

	//�w�i
	backGround.Init(L"asset/background/Background_blue.png");
	//backGround.Init(L"asset/StageSelect/�^�C�g���A�j���[�V����_�w�i2.gif");
	backGround.SetPos(0.0f, 0.0f, 0.0f);
	backGround.SetSize(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f);
	backGround.SetAngle(0);
	backGround.SetColor(1, 1, 1, 1);

	//�X�e�[�W���
	stageTexture.Init(L"asset/Background/haikei2.png");
	stageTexture.SetSize(1155,650,0);
	stageTexture.SetPos(-350, (selectImage_stage[0].GetPos().y + selectImage_stage[0].GetSize().y / 2) - stageTexture.GetSize().y / 2 + 20, 0);
	stageTexture.SetAngle(0);
	stageTexture.SetColor(1, 1, 1, 1);

	//�X�e�[�W���̘g
	stageNameFlame.Init(L"asset/UI/Flame2.png");
	stageNameFlame.SetPos(-350, -378, 0);
	stageNameFlame.SetSize(1067, 161, 0);
	stageNameFlame.SetAngle(0);
	stageNameFlame.SetColor(1, 1, 1, 1);

	//�X�e�[�W��
	stageName.Init(L"asset/UI/StageSelect.png", 2, 1);
	stageName.SetPos(stageNameFlame.GetPos().x, stageNameFlame.GetPos().y, 0);
	stageName.SetSize(488, 150, 0);
	stageName.SetAngle(0);
	stageName.SetColor(1, 1, 1, 1);

	//�X�e�[�W���̔ԍ�
	stageNameNumber.Init(L"asset/UI/suuji-1.png", 1, 11);
	stageNameNumber.SetSize(150, 150, 0);
	stageNameNumber.SetPos((stageName.GetPos().x + stageName.GetSize().x / 2 + stageNameNumber.GetSize().x / 2), stageName.GetPos().y-3, 0);
	stageNameNumber.SetAngle(0);
	stageNameNumber.SetColor(1, 1, 1, 1);
	stageNameNumber.numV = 1;

	//�X�^�[�g�{�^��
	startButton.Init(L"asset/UI/start.png");
	startButton.SetPos(704.0f, -400.0f, 0.0f);
	startButton.SetSize(311.0f, 100.0f, 0.0f);
	startButton.SetAngle(0);
	startButton.SetColor(1, 1, 1, 1);

	//���j���[�{�^��
	menuButton.Init(L"asset/UI/Hamburger_icon_100x100.png");
	menuButton.SetPos(-704.0f, 476.0f, 0.0f);
	menuButton.SetSize(78.0f, 78.0f, 0.0f);
	menuButton.SetAngle(0);
	menuButton.SetColor(1, 1, 1, 1);

	//�������p�̘g
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
	//���[���h�A�X�e�[�W�Z���N�g
	switch (stateNum)
	{
	case WORLDSELECTSCENE:
		/*��������
		�p�\�R���̃f�B�X�v���C�̊g��E�k���{���ɂ���ă}�E�X�J�[�\���̍��W���{���̒l�ƈႤ�l�ɂȂ邱�Ƃ�����*/
		
		for (int i = 0; i < 6; i++)
		{
			//�ԍ��̍��W���Z�b�g
			numberText[i].SetPos(worldNameImage[i].GetPos().x + worldNameImage[i].GetSize().x / 2 + numberText[i].GetSize().x / 2,
				worldNameImage[i].GetPos().y - 2, 0);
		}
	
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
							//stateNum = STAGESELECTSCENE;
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

						if (i == 0)
						{
							//�ڕW�̍��W�ƃX�P�[�����擾
							targetPos = { stageNameFlame.GetPos().x ,stageNameFlame.GetPos().y, stageNameFlame.GetPos().z };
							targetScale = { stageNameFlame.GetSize().x,stageNameFlame.GetSize().y, stageNameFlame.GetSize().z };

							//�������p�̘g�̍��W�ƃT�C�Y�̏����l��ݒ�
							moveFlame.SetPos(selectImage_world[i].GetPos().x, selectImage_world[i].GetPos().y, selectImage_world[i].GetPos().z);
							moveFlame.SetSize(selectImage_world[i].GetSize().x, selectImage_world[i].GetSize().y, selectImage_world[i].GetSize().z);

							//���W�̕����x�N�g��
							DirectX::XMFLOAT3 direction;
							//�ڕW�܂ł̕����x�N�g�������߂�
							direction.x = targetPos.x - moveFlame.GetPos().x;
							direction.y = targetPos.y - moveFlame.GetPos().y;

							//�x�N�g���̒��������߂�
							float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

							//�ړ����x�����߂�
							moveSpeed = length / FLAMENUM;

							//���K���������W�p�����x�N�g�������߂đ��
							normalizedDirection =
							{
								direction.x / length,
								direction.y / length,
								0
							};

							//--------------------------------------------------------------------------------------------------------

							//�傫���̕����x�N�g�������߂�
							direction.x = targetScale.x - moveFlame.GetSize().x;
							direction.y = targetScale.y - moveFlame.GetSize().y;

							//�x�N�g���̒��������߂�
							length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

							//�傫���̕ω���
							deltaScale = length / FLAMENUM;

							//���K�������傫���p�����x�N�g�������߂đ��
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
		//�N���b�N���ꂽ��
		if (inputSystem->GetTrigger(MK_LEFT))
		{
			//�X�e�[�W�Z���N�g�̘g
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

						//�ԍ����Z�b�g
						stageNameNumber.numV = i + 1;

					}
				}

			}

			//�X�^�[�g�{�^��
			//�N���b�N���ꂽx���W�������ɂ�������
			if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (startButton.GetPos().x - startButton.GetSize().x / 2) &&
				inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (startButton.GetPos().x + startButton.GetSize().x / 2))
			{
				//
				if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (startButton.GetPos().y - startButton.GetSize().y / 2) &&
					(inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (startButton.GetPos().y + startButton.GetSize().y / 2))
				{
					//��Ԃ�ς���
					stateNum = SETSTAGE;
				}
			}

		}
		
		break;
	case SETSTAGE:

		//���[���h�ԍ��ƃX�e�[�W�ԍ����Z�b�g
		//SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetWorldNumber(worldNum);
		SceneManager::GetInstance()->SetStageNumber(stageNum);

		//SceneManager::GetInstance()->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		SceneManager::GetInstance()->ChangeScene(STAGE);

		break;
	case MOVEFLAME:

		bool arrivedPosFlg= MoveFlame();

		//�������Ă�����(World->Stage�̏ꍇ)
		if (arrivedPosFlg == true && worldNum != NOTDONE_WORLD)
		{
			stateNum = STAGESELECTSCENE;
		}
		//(Stage->World�̏ꍇ)
		else if (arrivedPosFlg == true && worldNum == NOTDONE_WORLD)
		{
			stateNum = WORLDSELECTSCENE;
		}
		

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
				case WORLDSELECTSCENE://�^�C�g���V�[���ɖ߂�
					SceneManager::GetInstance()->ChangeScene(TITLE);
					break;
				case STAGESELECTSCENE: //���[���h�Z���N�g�ɖ߂�

					//�ڕW�̍��W�ƃX�P�[�����擾
					targetPos = { selectImage_world[worldNum - 1].GetPos().x, selectImage_world[worldNum - 1].GetPos().y, selectImage_world[worldNum - 1].GetPos().z };
					targetScale = { selectImage_world[worldNum - 1].GetSize().x, selectImage_world[worldNum - 1].GetSize().y, selectImage_world[worldNum - 1].GetSize().z };

					//�������p�̘g�̍��W�ƃT�C�Y�̏����l��ݒ�
					moveFlame.SetPos(stageNameFlame.GetPos().x, stageNameFlame.GetPos().y, stageNameFlame.GetPos().z);
					moveFlame.SetSize(stageNameFlame.GetSize().x, stageNameFlame.GetSize().y, stageNameFlame.GetSize().z);

					//���W�̕����x�N�g��
					DirectX::XMFLOAT3 direction;
					//�ڕW�܂ł̕����x�N�g�������߂�
					direction.x = targetPos.x - moveFlame.GetPos().x;
					direction.y = targetPos.y - moveFlame.GetPos().y;

					//�x�N�g���̒��������߂�
					float length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

					//�ړ����x�����߂�
					moveSpeed = length / FLAMENUM;

					//���K���������W�p�����x�N�g�������߂đ��
					normalizedDirection =
					{
						direction.x / length,
						direction.y / length,
						0
					};

					//--------------------------------------------------------------------------------------------------------

					//�傫���̕����x�N�g�������߂�
					direction.x = targetScale.x - moveFlame.GetSize().x;
					direction.y = targetScale.y - moveFlame.GetSize().y;

					//�x�N�g���̒��������߂�
					length = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));

					//�傫���̕ω���
					deltaScale = length / FLAMENUM;

					//���K�������傫���p�����x�N�g�������߂đ��
					normalizedScaleVector =
					{
						direction.x / length,
						direction.y / length,
						0
					};

					stateNum = MOVEFLAME;

					//stateNum = WORLDSELECTSCENE;
					worldNum = NOTDONE_WORLD;//�I���̏�Ԃ����Z�b�g
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

	//�ڕW�n�_�֌������Ĉړ�
	pos.x += normalizedDirection.x * moveSpeed;
	pos.y += normalizedDirection.y * moveSpeed;

	//�ڕW�̑傫���Ɍ������ĕω�
	scale.x += normalizedScaleVector.x * deltaScale;
	scale.y += normalizedScaleVector.y * deltaScale;

	moveFlame.SetPos(pos.x, pos.y, pos.z);
	moveFlame.SetSize(scale.x, scale.y, scale.z);

	//�ڕW�n�_�ɋ߂Â�����
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
