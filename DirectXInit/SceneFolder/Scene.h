#pragma once
#include"SceneManager.h"

//前方宣言
//class SceneManager;

class DrawManager;
class NodeManager;

class Scene
{
private:
	const SCENENAME sceneName;
public:
	//コンストラクタ、デストラクタ
	Scene(const SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	
};

