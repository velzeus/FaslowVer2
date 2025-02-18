#include "SceneManager.h"
#include <iostream>
#include<Windows.h>



using namespace std;

// 静的メンバ変数の初期化
SceneManager* SceneManager::instance = nullptr;
bool SceneManager::endFlg = false;

// コンストラクタ
SceneManager::SceneManager()
    : currentScene(nullptr), nextScene(nullptr)//, mouseInput(nullptr)
{
    // 特別な初期化は不要

     //mouseInput = MouseInput::GetInstance();

     //g_inputSystem = TS::TS_InputSystem::GetInstance();
     inputSystem=TS::TS_InputSystem::GetInstance();

     inputSystem->Init();
}

// デストラクタ
SceneManager::~SceneManager() = default;  // unique_ptrが自動的にリソースを解放

// インスタンスを取得（シングルトンパターン）
SceneManager* SceneManager::GetInstance()
{
    static SceneManager inst;
    return &inst;

}

// 更新処理
int SceneManager::Update()
{
    //mouseInput->Update();

    inputSystem->Update();

    if (endFlg == true) {
        return 1;
    }

    if (nextScene != nullptr)  // 次のシーンに切り替える場合
    {
        cout << "Update: currentScene = "
            << (currentScene ? "valid" : "nullptr")
            << ", nextScene = "
            << (nextScene ? "valid" : "nullptr") << endl;

        // 現在のシーンが存在している場合
        if (currentScene != nullptr) {
            currentScene->End();  // 現在のシーンを終了

            // sceneFactoriesに現在のシーンを格納
            SCENENAME currentSceneName = currentScene->GetSceneName();  // 現在のシーン名を取得
            sceneFactories[currentSceneName] = std::move(currentScene);  // 現在のシーンを格納
        }


        currentScene = std::move(nextScene);  // nextSceneの所有権を currentSceneに移動
        nextScene = nullptr;  // 次のシーンはクリア




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

void SceneManager::SetWorldNumber(WORLDNUMBER _worldNum)
{
    worldNumber = _worldNum;
}

void SceneManager::SetStageNumber(STAGENUMBER _stageNum)
{
    stageNumber = _stageNum;
}

WORLDNUMBER SceneManager::GetWorldNumber()
{
    return worldNumber;
}

STAGENUMBER SceneManager::GetStageNumber()
{
    return stageNumber;
}

// シーンを追加
void SceneManager::AddScene(SCENENAME sceneName, std::unique_ptr<Scene> _scene)
{
    if (_scene == nullptr) {
        cerr << "Cannot add a null scene!" << endl;
        cout << "Cannot add a null scene!" << SceneNameToString(_scene.get()->GetSceneName()) << endl;
        return;
    }

    if (sceneFactories.find(sceneName) != sceneFactories.end()) {
        cerr << "Scene " << sceneName << " is already registered!" << endl;
        cout << "Scene " << sceneName << " is already registered!" << endl;
        return;
    }
    sceneFactories[sceneName] = std::move(_scene);
}

// シーンを切り替える
void SceneManager::ChangeScene(SCENENAME sceneName)
{
    if (sceneName == SCENENAME::END) {
        return;
    }
    auto it = sceneFactories.find(sceneName);
    if (it != sceneFactories.end()) {

        if (!it->second) {
            cout << "sceneがnullptrです" << sceneName << endl;
            return;
        }
        else
            cout << "sceneが正常に作動してます(" 
            << SceneNameToString(sceneFactories[sceneName]->GetSceneName()) 
            << ")" << endl;

        nextScene = std::move(it->second);

        // エラー処理を記述してください

    }
    else {
        cerr << "Scene with name " << SceneNameToString(sceneName) << " not found!" << endl;
    }
}

HRESULT SceneManager::Initialize(HWND hWnd)
{
    srand((unsigned)time(NULL));
    D3D_Create(hWnd);                //DirectXを初期化

    return S_OK;
}
