#pragma once
#include<fstream>
#include"../../json.hpp"
#include "../Scene.h"
#include"../../BlockBace.h"

#define STAGE_X (32)//横のマス数
#define STAGE_Y (18)//縦のマス数

//ブロックのサイズ
#define BLOCKSIZE_X (40)
#define BLOCKSIZE_Y (40)

//マス目の状態
enum GridState
{
	//変わらないもの
	NULLBLOCK = 0,			//何もない
	BOLL,			//ボール
	GORL,			//ゴール
	COIN,			//コイン

	//ブロック
	STICKY_BLOCK = 10,	//粘着ブロック
	SLIP_BLOCK,		//滑るブロック
	UNBREAK_BLOCK,	//破壊不可ブロック

	//ギミック
	CANNON = 20,	//大砲
	WORMHOLE,		//ワームホール
	SWITCH_BOLL,	//スイッチのボール
	SWITCH_GORL,	//スイッチのゴール
};

//座標を取得するための構造体
struct VECTOR2
{
    float x, y;
};

class StageScene :
    public Scene
{
public:
    StageScene();
    ~StageScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //jsonファイルを読み込む（引数にStage番号を持ってくる）
    void ReadFile();

private:
    SceneManager* manager;

	//MouseInput* mouseInput;

	TS::TS_InputSystem* inputSystem;

    std::vector<std::vector<int>> read_gridStateList;//マス目の状態を保存する

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//ブロックの座標を保存する

    Object grids[STAGE_X][STAGE_Y];

	int gridData[STAGE_X][STAGE_Y];

	//BlockBaseで仮置き
	//BlockBace* blocks[STAGE_X][STAGE_Y];
	std::vector<BlockBace*> blocks;

	//オプションボタン
	Object optionButton;

	//ゴール（仮）
	Object gorl;

};

