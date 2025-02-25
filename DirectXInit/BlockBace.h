#pragma once
#include"Object.h"


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


class BlockBace :public Object
{
private:
	int index;//ブロックのインデックス
	GridState blocktype;

	//座標の代入が完了したかを判定するフラグ
	bool setFlg;
public:
	BlockBace();
	BlockBace(int _index, GridState _blocktype);
	GridState GetBlockType();
	int GetIndex();//インデックスを取得
	
	//勝手に追加しました by西嶋
	void SetIndex(int _index);
	bool GetFlg();
	void SetFlg(bool _setFlg);

};