#pragma once
#include<fstream>
#include"json.hpp"
#include"SceneFolder/Scene.h"
#include"../../Object.h"

//座標を取得するための構造体
struct VECTOR2
{
    float x, y;
};

class ClassA :
    public Scene
{
public:
    ClassA();
    ~ClassA() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //jsonファイルを読み込む（引数にStage番号を持ってくる）
    void ReadFile();


private:
    SceneManager* manager;

    std::vector<std::vector<int>> read_gridStateList;//マス目の状態を保存する

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//ブロックの座標を保存する


};

