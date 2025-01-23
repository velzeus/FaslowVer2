#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;

bool SceneManager::endFlg = false;


//コンストラクタ
SceneManager::SceneManager()//:sound(nullptr)
{
	//vector型のサイズをあらかじめ定義し、scenesの中身を全てnullptrにする
	scenes.resize(SCENENAME_MAX,nullptr);

	currentScene = nullptr;
	nextScene = nullptr;
	
	//currentSceneとNextScene
	
}

//インスタンスを取得
SceneManager* SceneManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new SceneManager;//作成
	}
	return instance;
}

//シーンを追加
void SceneManager::AddScene(Scene* _scene)
{
	//scenes.push_back(_scene);
}

//開始処理
int SceneManager::Start()
{
	//scene->Start();
	
	//Scene追加
	//AddScene(scene);

	//instance->scene = new Scene;//メモリ確保

	//読み込むシーンを代入
	instance->currentScene = instance->nextScene;

	//nextSceneをnullptrにする
	instance->nextScene = nullptr;

	//適切に生成できていたら
	if (instance->currentScene != nullptr)
	{
		instance->currentScene->Start();
	}
	

	return 0;
}

//更新処理
int SceneManager::Update()
{
	static bool isChangingScene = false;

	//次のシーンと現在のシーンが違ったら
	if (isChangingScene ==false && instance->currentScene != instance->nextScene)
	{
		isChangingScene = true;
		End();
		Start();
		isChangingScene = false;
	}

	//シーン更新
	if (instance->currentScene != nullptr)
	//currentSceneがnullptrじゃないときにUpdate実行
	{
		instance->currentScene->Update();
	}

	
	
	//nextScene = scene;
	
	return 0;
}

//描画処理
int SceneManager::Draw()
{
	//シーン描画
	if (instance->currentScene != nullptr)
		//currentSceneがnullptrじゃないときにUpdate実行
	{
		instance->currentScene->Draw();
	}
	
		//currentScene->Draw();
	
	return 0;
}

//終了処理
int SceneManager::End()
{
	//既に読み込み済みのシーンがある場合
	if (instance->currentScene != nullptr)
	{
		//シーンの終了処理
		instance->currentScene->End();

		//シーンを解放
		delete instance->currentScene;
		instance->currentScene = nullptr;

	}

	return 0;
}

void SceneManager::ChangeScene(SCENENAME _sceneName)
{
	//nextSceneを解放する
	if (instance->nextScene != nullptr)
	{
		delete instance->nextScene;
	}

	switch (_sceneName)
	{
	case TITLE:
		instance->nextScene = new Scene;//メモリ確保
		break;

		/*ステージシーン*/

	case RESULT:
		instance->nextScene = new Scene;//メモリ確保
		break;
	}	
}
