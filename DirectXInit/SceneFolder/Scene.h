#pragma once
#include"SceneManager.h"

//前方宣言
//class SceneManager;

class DrawManager;
class NodeManager;

class Scene
{
public:

public:
	//コンストラクタ、デストラクタ
	Scene();
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();
};

