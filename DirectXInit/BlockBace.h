#pragma once
#include"Object.h"


//�}�X�ڂ̏��
enum GridState
{
	//�ς��Ȃ�����
	NULLBLOCK = 0,			//�����Ȃ�
	BOLL,			//�{�[��
	GORL,			//�S�[��
	COIN,			//�R�C��

	//�u���b�N
	STICKY_BLOCK = 10,	//�S���u���b�N
	SLIP_BLOCK,		//����u���b�N
	UNBREAK_BLOCK,	//�j��s�u���b�N

	//�M�~�b�N
	CANNON = 20,	//��C
	WORMHOLE,		//���[���z�[��
	SWITCH_BOLL,	//�X�C�b�`�̃{�[��
	SWITCH_GORL,	//�X�C�b�`�̃S�[��
};


class BlockBace :public Object
{
private:
	int index;//�u���b�N�̃C���f�b�N�X
	GridState blocktype;

	//���W�̑���������������𔻒肷��t���O
	bool setFlg;
public:
	BlockBace();
	BlockBace(int _index, GridState _blocktype);
	GridState GetBlockType();
	int GetIndex();//�C���f�b�N�X���擾
	
	//����ɒǉ����܂��� by����
	void SetIndex(int _index);
	bool GetFlg();
	void SetFlg(bool _setFlg);

};