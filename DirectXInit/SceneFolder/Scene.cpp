#include "Scene.h"


//�R���X�g���N�^
Scene::Scene():drawManager(nullptr),nodeManager(nullptr),sound(nullptr)
{
	//������
	//Start();

	sound->GetInstance();
}

Scene::~Scene()
{
	//�I��
	//End();


}

//�J�n����
int Scene::Start()
{
	//�V�[���J�n���̏���

	return 0;
}

//�X�V����
int Scene::Update()
{
	//�V�[���X�V���̏���

	//�V�[����ύX
	if (0)
	{
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}
	
	return 0;
}

//�`�揈��
int Scene::Draw()
{
	//�V�[���`�掞�̏���

	return 0;
}

//�I������
int Scene::End()
{
	//�V�[���I�����̏���

	return 0;
}
