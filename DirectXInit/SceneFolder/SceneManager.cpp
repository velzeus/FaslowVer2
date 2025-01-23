#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

bool SceneManager::endFlg = false;


//�R���X�g���N�^
SceneManager::SceneManager()//:sound(nullptr)
{
	//vector�^�̃T�C�Y�����炩���ߒ�`���Ascenes�̒��g��S��nullptr�ɂ���
	scenes.resize(SCENENAME_MAX,nullptr);

	currentScene = nullptr;
	nextScene = nullptr;
	
	//currentScene��NextScene
	
}

//�C���X�^���X���擾
SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager;//�쐬
	}
	return instance;
}

//�V�[����ǉ�
void SceneManager::AddScene(Scene* _scene)
{
	//scenes.push_back(_scene);
}

//�J�n����
int SceneManager::Start()
{
	//scene->Start();
	
	//Scene�ǉ�
	//AddScene(scene);

	//instance->scene = new Scene;//�������m��

	//�ǂݍ��ރV�[������
	instance->currentScene = instance->nextScene;

	//nextScene��nullptr�ɂ���
	instance->nextScene = nullptr;

	//�K�؂ɐ����ł��Ă�����
	if (instance->currentScene != nullptr)
	{
		instance->currentScene->Start();
	}
	

	return 0;
}

//�X�V����
int SceneManager::Update()
{
	static bool isChangingScene = false;

	//���̃V�[���ƌ��݂̃V�[�����������
	if (isChangingScene ==false && instance->currentScene != instance->nextScene)
	{
		isChangingScene = true;
		End();
		Start();
		isChangingScene = false;
	}

	//�V�[���X�V
	if (instance->currentScene != nullptr)
	//currentScene��nullptr����Ȃ��Ƃ���Update���s
	{
		instance->currentScene->Update();
	}

	
	
	//nextScene = scene;
	
	return 0;
}

//�`�揈��
int SceneManager::Draw()
{
	//�V�[���`��
	if (instance->currentScene != nullptr)
		//currentScene��nullptr����Ȃ��Ƃ���Update���s
	{
		instance->currentScene->Draw();
	}
	
		//currentScene->Draw();
	
	return 0;
}

//�I������
int SceneManager::End()
{
	//���ɓǂݍ��ݍς݂̃V�[��������ꍇ
	if (instance->currentScene != nullptr)
	{
		//�V�[���̏I������
		instance->currentScene->End();

		//�V�[�������
		delete instance->currentScene;
		instance->currentScene = nullptr;

	}

	return 0;
}

void SceneManager::ChangeScene(SCENENAME _sceneName)
{
	//nextScene���������
	if (instance->nextScene != nullptr)
	{
		delete instance->nextScene;
	}

	switch (_sceneName)
	{
	case TITLE:
		instance->nextScene = new Scene;//�������m��
		break;

		/*�X�e�[�W�V�[��*/

	case RESULT:
		instance->nextScene = new Scene;//�������m��
		break;
	}	
}
