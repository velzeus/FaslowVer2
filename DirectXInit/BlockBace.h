#pragma once
#include"Object.h"

enum BLOCKTYPE
{
	SLIME,//粘着ブロック
	SLIDE,//滑るブロック
	UNBREAK,//壊せないブロック
	EMPTY//何もない
};

class BlockBace :public Object
{
private:
	int index;//ブロックのインデックス
	BLOCKTYPE blocktype;
public:
	BlockBace();
	BlockBace(int _index, BLOCKTYPE _blocktype);
	BLOCKTYPE GetBlockType();
	int GetIndex();//インデックスを取得
	
	//勝手に追加しました by西嶋
	void SetIndex(int _index);
};