#pragma once
#include "Scene.h"
#include"../Object.h"
#include"../input.h"
#include"../MouseInput.h"
#include"../Sound.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <functional>
#include<iostream>

// 前方宣言
class Scene;

enum SCENENAME
{
    TITLE = 0,
    RESULT,
    SCENENAME_MAX,
};


class SceneManager {
private:
    static bool endFlg;  // 終了フラグ

    static SceneManager* instance; // シングルトンインスタンス

    // Sceneの
    std::unique_ptr<Scene> currentScene; // 現在のシーン
    std::unique_ptr<Scene> nextScene; // 次のシーン
    std::unordered_map<SCENENAME, std::unique_ptr<Scene>> sceneFactories; // シーン生成ロジック

    SceneManager(); // コンストラクタ

public:
    static SceneManager* GetInstance(); // シングルトンインスタンスを取得
    ~SceneManager(); // デストラクタ

    void AddScene(SCENENAME _sceneName, std::unique_ptr<Scene> _scene);
    void ChangeScene(SCENENAME _sceneName);

    HRESULT Initialize(HWND hWnd);

    int Update();
    int Draw();

    // エラー用
    std::string SceneNameToString( SCENENAME _sceneName);
};