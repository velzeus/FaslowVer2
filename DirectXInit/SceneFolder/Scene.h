#pragma once
#include"SceneManager.h"

//前方宣言
enum SCENENAME;

class SceneManager;



class Scene
{
private:
	const SCENENAME sceneName;

public:
	//コンストラクタ、デストラクタ
	Scene(SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	SCENENAME GetSceneName();
};


