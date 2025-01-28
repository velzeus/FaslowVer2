#include "Scene.h"


//コンストラクタ
Scene::Scene(SCENENAME _sceneName):sceneName(_sceneName){
	//初期化
	//Start();
	std::cout << SceneManager::GetInstance()->SceneNameToString(_sceneName)
		<< ": Sceneコンストラクタ" << std::endl;

}

Scene::~Scene()
{
	//終了
	//End();


}

//開始処理
int Scene::Start()
{
	//シーン開始時の処理
	std::cout << "error is Scene::Strt" << std::endl;

	return 0;
}

//更新処理
int Scene::Update()
{
	//シーン更新時の処理

	//シーンを変更
	if (0)
	{
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}
	
	return 0;
}

//描画処理
int Scene::Draw()
{
	//シーン描画時の処理

	return 0;
}

//終了処理
int Scene::End()
{
	//シーン終了時の処理

	return 0;
}

SCENENAME Scene::GetSceneName()
{
	std::cout << "GetSceneNameが読み出されました:sceneName(" 
		<< sceneName << ")" << std::endl;
	return sceneName;
}
