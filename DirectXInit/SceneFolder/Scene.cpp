#include "Scene.h"


//�R���X�g���N�^
Scene::Scene(SCENENAME _sceneName):sceneName(_sceneName){
	//������
	//Start();
	std::cout << SceneManager::GetInstance()->SceneNameToString(_sceneName)
		<< ": Scene�R���X�g���N�^" << std::endl;

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
	std::cout << "error is Scene::Strt" << std::endl;

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

SCENENAME Scene::GetSceneName()
{
	std::cout << "GetSceneName���ǂݏo����܂���:sceneName(" 
		<< sceneName << ")" << std::endl;
	return sceneName;
}
