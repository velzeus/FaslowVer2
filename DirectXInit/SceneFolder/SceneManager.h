#pragma once
#include"Scene.h"
#include<vector>
#include<algorithm>

//前方宣言
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
	static SceneManager* instance;// インスタンス

	Scene* currentScene;// 現在のシーン
	Scene* nextScene;//次のシーン

	// サウンド

	std::vector<Scene*> scenes;
	static bool endFlg;

	//コンストラクタ
	SceneManager();

public:
	

	//インスタンスを取得
	static SceneManager* GetInstance();
	~SceneManager();

	//シーンを追加
	void AddScene(Scene* _scene);

	//各シーンに関する処理を呼び出す
	int Start();	//開始処理
	int Update();	//更新処理
	int Draw();		//描画処理
	int End();		//終了処理


	//シーンを切り替える
	void ChangeScene(SCENENAME _sceneName);
};

//静的メンバ変数の定義
// SceneManager* SceneManager::instance = nullptr;
// bool SceneManager::endFlg = false;

