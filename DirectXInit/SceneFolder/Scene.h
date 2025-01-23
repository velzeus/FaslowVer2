#pragma once
#include"SceneManager.h"

//�O���錾
//class SceneManager;

class DrawManager;
class NodeManager;

class Scene
{
private:
	const SCENENAME sceneName;
public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Scene(const SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	
};

