#include "Scene.h"


DirectX::XMFLOAT3 Scene::RotateVector(DirectX::XMFLOAT3 _target, DirectX::XMFLOAT3 _base)
{
	//�����x�N�g��
	DirectX::XMFLOAT3 direction;

	//�ڕW-��ł̃x�N�g��
	direction.x = _target.x - _base.x;
	direction.y = _target.y - _base.y;

	return direction;
}

float Scene::VectorLength(DirectX::XMFLOAT3 _direction)
{
	float length = std::sqrt((_direction.x * _direction.x) + (_direction.y * _direction.y));
	return length;
}

DirectX::XMFLOAT3 Scene::NormalizedRotateVector(DirectX::XMFLOAT3 _direction)
{
	DirectX::XMFLOAT3 normalizedDirection
	{
		_direction.x / VectorLength(_direction),
		_direction.y / VectorLength(_direction),
		0
	};

	return normalizedDirection;
}

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
