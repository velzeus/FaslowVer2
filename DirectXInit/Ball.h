#pragma once
#include"Object.h"


enum DIRECTION
{
	DOWN,//下
	RIGHT,//右
	UP,//上
	LEFT,//左
	STOP//止まる
};


class Ball :public Object
{
private:
	bool rotDirection = true;//回転方向の指定 true:右　false:左
	DIRECTION crntDrct;//ボールがくっついている辺
	DIRECTION precDrct;//ボールがくっついていた辺
	DIRECTION moveDir = LEFT; // ボールの移動方向 (新しく追加)

public:
	Ball();
	Ball(bool _rotDir);

	DIRECTION GetMoveDir();//進行方向のゲッター
	void SetMoveDir(DIRECTION dir);//進行方向のセッター
	void Move();//移動

	void Move_Cannon(DirectX::XMFLOAT3 _normalizedDirection);

	bool GetrotDir();//回転方向のゲッター
	void SetrotDir(bool _rotdir);//回転方向のセッター

	void Setborder();//端に行った時の処理

	float vel_x = 1.0f;//横の移動量
	float vel_y = 1.0f;//縦の移動量
};