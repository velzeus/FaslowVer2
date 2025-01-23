#pragma once
#include"SceneManager.h"
#include"sound.h"

//�O���錾
//class SceneManager;

class DrawManager;
class NodeManager;

class Scene
{
public:
	DrawManager* drawManager;
	NodeManager* nodeManager;
	Sound* sound;

public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Scene();
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();
};

