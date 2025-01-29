#pragma once
#include "Scene.h"
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
    SELECT,
    STAGE,
    RESULT,
    OPTION,
    SCENENAME_MAX,
};

//ステージ番号
enum WORLDNUMBER
{
    
    WORLD1 = 1,
    WORLD2,
    WORLD3,
    WORLD4,
    WORLD5,
    WORLD6,
};

//ステージ番号
enum STAGENUMBER
{
    
    STAGE1 = 1,
    STAGE2,
    STAGE3,
    STAGE4,
    STAGE5,
    STAGEINIT,
};


class SceneManager {
private:
    static bool endFlg;  // 終了フラグ

    static SceneManager* instance; // シングルトンインスタンス

    // Sceneの
    std::unique_ptr<Scene> currentScene; // 現在のシーン
    std::unique_ptr<Scene> nextScene; // 次のシーン
    std::unordered_map<SCENENAME, std::unique_ptr<Scene>> sceneFactories; // シーン生成ロジック

    WORLDNUMBER worldNumber;//ワールド番号を保存する

    STAGENUMBER stageNumber;//ステージ番号を保存する


    SceneManager(); // コンストラクタ

public:
    static SceneManager* GetInstance(); // シングルトンインスタンスを取得
    ~SceneManager(); // デストラクタ

    void AddScene(SCENENAME _sceneName, std::unique_ptr<Scene> _scene);
    void ChangeScene(SCENENAME _sceneName);
    int Update();
    int Draw();

    // エラー用
    std::string SceneNameToString( SCENENAME _sceneName);

    //ワールド番号とステージ番号のセッター・ゲッター関数
    void SetWorldNumber(WORLDNUMBER _worldNum);
    void SetStageNumber(STAGENUMBER _stageNum);

    WORLDNUMBER GetWorldNumber();
    STAGENUMBER GetStageNumber();


};