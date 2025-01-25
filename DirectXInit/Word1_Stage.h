#pragma once
#include "Object.h"
#include"input.h"
#include"Sound.h"

#include<iostream>
#include<fstream>
#include<string>
#include"json.hpp"

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

//ステージ番号
enum STAGE_NUMBER
{
	STAGE1 = 1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGEINIT,
};

//座標を取得するための構造体
struct VECTOR2
{
	float x, y;
};

class World1_Stage
{
private:
	Input input;//キー入力オブジェクト
	//Sound sound;
	Object player;//プレイヤーオブジェクト
	Object background; //背景オブジェクト
	Object scoreboard;//スコアオブジェクト
	Object grids[STAGE_X][STAGE_Y];//マスオブジェクト
	int gridData[STAGE_X][STAGE_Y] = {};//データ配列
	//int TetrominoType; //テトリミノの種類（０～６）
	//int TetrominoDirection; //テトリミノの向き（０～３）
	//int state = 0;//ゲームの状態（０：落下するものがない状態　１：落下中）
	int score = 0;//得点
	int scene = 0;//シーン（０：タイトル、１：ゲーム本編）
	//int Exflg = 0;//０：揃ってない　１：揃ってる
	//int check = 0;
	//int limy;

	std::vector<std::vector<int>> read_gridStateList;//マス目の状態を保存する

	std::vector<std::vector<VECTOR2>> read_blockPositionList;//ブロックの座標を保存する

public:

	World1_Stage();//コンストラクタ

	//jsonファイルを読み込む（引数にStage番号を持ってくる）
	void ReadFile(int _stageNumber);

	void Init(HWND hWnd); //初期化

	void Update(void);    //更新
	void Draw();          //描画 
	void Uninit();        //終了  
};

