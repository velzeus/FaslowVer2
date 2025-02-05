#pragma once
#include"../../BlockFanction.h"
#include"../Scene.h"
#include<memory>

#define STAGE_WIDTH		(32)	// 横幅
#define STAGE_HEIGHT	(18)	// 高さ

// 西嶋君とは違うやり方でStageSceneを作成
class TS_StageScene:public Scene
{
public:

	int Start() override;	// ステージの初期化
	int Update() override;	// ステージのアップデートを行う
	int Draw() override;	// ステージの描画
	int End() override;		// ステージの後処理

private:

	
	TS::TS_InputSystem* inputSystem;	// 入力

	// Ballの当たり判定
	HitColBlock hitColBlack[4];

	std::unordered_map<GridState, std::shared_ptr<Object>> constantObject;
	
	Object ball;
	Object coin;
};

