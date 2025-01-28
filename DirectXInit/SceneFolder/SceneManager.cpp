#include "SceneManager.h"
#include "../input.h"
#include "../Sound.h"
#include "../Object.h"
#include <iostream>

using namespace std;

// 静的メンバ変数の初期化
SceneManager* SceneManager::instance = nullptr;
bool SceneManager::endFlg = false;

// コンストラクタ
SceneManager::SceneManager()
    : currentScene(nullptr), nextScene(nullptr)
{
    // 特別な初期化は不要
}

// デストラクタ
SceneManager::~SceneManager() = default;  // unique_ptrが自動的にリソースを解放

// インスタンスを取得（シングルトンパターン）
SceneManager* SceneManager::GetInstance()
{
    if (instance==nullptr)
    {
        instance = new SceneManager;  // インスタンスを作成
    }
    return instance;
}

// 更新処理
int SceneManager::Update()
{
    if (nextScene != nullptr)  // 次のシーンに切り替える場合
    {
        // 現在のシーンが存在している場合
        if (currentScene != nullptr) {
            currentScene->End();  // 現在のシーンを終了

            // sceneFactoriesに現在のシーンを格納
            SCENENAME currentSceneName = currentScene->GetSceneName();  // 現在のシーン名を取得
            sceneFactories[currentSceneName] = std::move(currentScene);  // 現在のシーンを格納
        }

        currentScene = std::move(nextScene);  // nextSceneの所有権をcurrentSceneに移動
        nextScene = nullptr;  // 次のシーンはクリア

        SCENENAME currentSceneName = currentScene->GetSceneName();  // 新しいシーン名を取得
        sceneFactories[currentSceneName] = std::move(currentScene);  // 現在のシーンを格納

        currentScene->Start();  // 新しいシーンの開始処理
    }

    if (currentScene != nullptr)
    {
        return currentScene->Update();  // 現在のシーンの更新
    }

    return -1;  // シーンがない場合は-1を返す
}

// 描画処理
int SceneManager::Draw()
{
    D3D_StartRender();

    if (currentScene != nullptr)
    {
        currentScene->Draw();  // 現在のシーンの描画
    }

    D3D_FinishRender();
    return 0;
}

std::string SceneManager::SceneNameToString( SCENENAME _sceneName)
{
    
    switch (_sceneName)
    {
    case TITLE:
        return "Title";
        break;
    case RESULT:
        return "Result";
        break;
    default:
        break;
    }
    return "Error";
}

// シーンを追加
void SceneManager::AddScene(SCENENAME sceneName, std::unique_ptr<Scene> _scene)
{
    if (_scene == nullptr) {
        cerr << "Cannot add a null scene!" << endl;
        return;
    }

    if (sceneFactories.find(sceneName) != sceneFactories.end()) {
        cerr << "Scene " << sceneName << " is already registered!" << endl;
        return;
    }
    sceneFactories[sceneName] = std::move(_scene);
}

// シーンを切り替える
void SceneManager::ChangeScene(SCENENAME sceneName)
{
    auto it = sceneFactories.find(sceneName);
    if (it != sceneFactories.end()) {
        nextScene = std::move(it->second);
    }
    else {
        cerr << "Scene with name " << sceneName << " not found!" << endl;
    }
}

HRESULT SceneManager::Initialize(HWND hWnd)
{
    srand((unsigned)time(NULL));
    D3D_Create(hWnd);                //DirectXを初期化

    return S_OK;
}
