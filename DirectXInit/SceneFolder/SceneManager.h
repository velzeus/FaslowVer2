#pragma once
#include"Scene.h"
#include<vector>
#include<algorithm>

//�O���錾
class Scene;

enum  SCENENAME
{
	TITLE=0,


	RESULT,

	SCENENAME_MAX,
};

class SceneManager
{
private:
	static SceneManager* instance;// �C���X�^���X

	Scene* currentScene;// ���݂̃V�[��
	Scene* nextScene;//���̃V�[��

	// �T�E���h

	std::vector<Scene*> scenes;
	static bool endFlg;

	//�R���X�g���N�^
	SceneManager();

public:
	

	//�C���X�^���X���擾
	static SceneManager* GetInstance();
	~SceneManager();

	//�V�[����ǉ�
	void AddScene(Scene* _scene);

	//�e�V�[���Ɋւ��鏈�����Ăяo��
	int Start();	//�J�n����
	int Update();	//�X�V����
	int Draw();		//�`�揈��
	int End();		//�I������


	//�V�[����؂�ւ���
	void ChangeScene(SCENENAME _sceneName);
};

//�ÓI�����o�ϐ��̒�`
// SceneManager* SceneManager::instance = nullptr;
// bool SceneManager::endFlg = false;

