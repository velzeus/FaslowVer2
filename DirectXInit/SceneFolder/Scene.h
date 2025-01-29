#pragma once
#include"SceneManager.h"

//�O���錾
enum SCENENAME;

enum WORLDNUMBER;
enum STAGENUMBER;

class SceneManager;

class TitleScene;
class SelectScene;
class ClassA;

class Scene
{
protected:
	const SCENENAME sceneName;

public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Scene(SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	SCENENAME GetSceneName();
};


