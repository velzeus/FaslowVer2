#pragma once
#include"Object.h"

enum BLOCKTYPE
{
	SLIME,//�S���u���b�N
	SLIDE,//����u���b�N
	UNBREAK,//�󂹂Ȃ��u���b�N
	EMPTY//�����Ȃ�
};

class BlockBace :public Object
{
private:
	int index;//�u���b�N�̃C���f�b�N�X
	BLOCKTYPE blocktype;
public:
	BlockBace();
	BlockBace(int _index, BLOCKTYPE _blocktype);
	BLOCKTYPE GetBlockType();
	int GetIndex();//�C���f�b�N�X���擾
};