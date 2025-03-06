#pragma once
#include<fstream>
#include"../../json.hpp"
#include "../Scene.h"
#include"../../BlockBace.h"
#include"../../Ball.h"
#include"../../Cannon.h"
#include"../../CutAndPaste.h"
#include <vector>
#include <utility> // std::pair を使うため
#include<iostream>
#include <unordered_map>
#include<algorithm>
using namespace std;



#define STAGE_X (32)//横のマス数
#define STAGE_Y (18)//縦のマス数

//ブロックのサイズ
#define BLOCKSIZE_X (40)
#define BLOCKSIZE_Y (40)



//GridStateはBlockBaceに移しました



class StageScene :
    public Scene
{
public:

	Ball ball;
    StageScene();
    ~StageScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //jsonファイルを読み込む（引数にStage番号を持ってくる）
    void ReadFile();

	//Ball ball;//ボール

	void UpdateMoveDir();

	DirectX::XMFLOAT3 center;//ボールの位置
	DirectX::XMFLOAT3 prvpos;//ボールの過去の位置
	std::vector<std::pair<float, float>> surroundingBlocks;//周囲８マスのあたり判定
	bool Collision(BlockBace* obj1, const std::pair<float, float>& obj2);//あたり判定

	std::vector<BlockBace*> GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks);//ステージ上にある周囲８マスを取得
	std::vector<BlockBace*> nearbyBlocks;//ボールの周り8マスに存在するブロック

	//ボールがブロックの区切りにいるときだけ当たり判定を実行
	bool onGridX;
	bool onGridY;

	int prv_index = -1;//あたった正面のブロック

	//０：front　１：back　２：left　３：right
	int hitIndex[4] = { -1,-1,-1,-1 };//あたったブロックの添え字
	int hitSafe[4] = { -1,-1,-1,-1 };//あたったブロックをセーブする
	bool hitFlgs[4] = { false,false,false,false };//あたり判定
	GridState hitBlockType[4] = { NULLBLOCK ,NULLBLOCK ,NULLBLOCK ,NULLBLOCK };//当たったブロックの種類
	void CheckSurroundingCollisions();

	DIRECTION _moveDir;


	void SetGridStateList(std::vector<std::vector<int>> _gridStateList);
	std::vector<std::vector<int>> GetGridStateList();

private:
    SceneManager* manager;

	//MouseInput* mouseInput;

	TS::TS_InputSystem* inputSystem;

    std::vector<std::vector<int>> read_gridStateList;//マス目の状態を保存する

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//ブロックの座標を保存する

    //Object grids[STAGE_X][STAGE_Y];

	int gridData[STAGE_X][STAGE_Y];

	//BlockBaseで仮置き
	//BlockBace* blocks[STAGE_X][STAGE_Y];
	std::vector<BlockBace*> blocks;

	std::vector<Cannon*> cannons;

	//オプションボタン
	Object optionButton;

	//リトライボタン
	Object retryButton;

	//ゴール（仮）
	Object gorl;

	//背景
	Object background;

	//コイン
	Object coin;

	//カットボタン
	Object cutButton;

	//
	Object holdAreaFlame;



	//色を変えるフラグ
	bool accelerationFlg;

	bool triggerFlg_O;
	bool triggerFlg_N;
	bool triggerFlg_T;

	int cannonIndex;

	bool cannonFlg;


	CutAndPaste cutAndPaste;

	//Area area;

	std::vector<Area*> holdAreas;

	int gridIndex_X[2] = {};
	int gridIndex_Y[2] = {};

	int animCount;

	bool addFlg;
};

