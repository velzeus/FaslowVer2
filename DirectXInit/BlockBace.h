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
};