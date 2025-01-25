#pragma once
#include "Object.h"
#include"input.h"
#include"Sound.h"

#include<iostream>
#include<fstream>
#include<string>
#include"json.hpp"

#define STAGE_X (32)//���̃}�X��
#define STAGE_Y (18)//�c�̃}�X��

//�u���b�N�̃T�C�Y
#define BLOCKSIZE_X (40)
#define BLOCKSIZE_Y (40)

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

//�X�e�[�W�ԍ�
enum STAGE_NUMBER
{
	STAGE1 = 1,
	STAGE2,
	STAGE3,
	STAGE4,
	STAGE5,
	STAGEINIT,
};

//���W���擾���邽�߂̍\����
struct VECTOR2
{
	float x, y;
};

class World1_Stage
{
private:
	Input input;//�L�[���̓I�u�W�F�N�g
	//Sound sound;
	Object player;//�v���C���[�I�u�W�F�N�g
	Object background; //�w�i�I�u�W�F�N�g
	Object scoreboard;//�X�R�A�I�u�W�F�N�g
	Object grids[STAGE_X][STAGE_Y];//�}�X�I�u�W�F�N�g
	int gridData[STAGE_X][STAGE_Y] = {};//�f�[�^�z��
	//int TetrominoType; //�e�g���~�m�̎�ށi�O�`�U�j
	//int TetrominoDirection; //�e�g���~�m�̌����i�O�`�R�j
	//int state = 0;//�Q�[���̏�ԁi�O�F����������̂��Ȃ���ԁ@�P�F�������j
	int score = 0;//���_
	int scene = 0;//�V�[���i�O�F�^�C�g���A�P�F�Q�[���{�ҁj
	//int Exflg = 0;//�O�F�����ĂȂ��@�P�F�����Ă�
	//int check = 0;
	//int limy;

	std::vector<std::vector<int>> read_gridStateList;//�}�X�ڂ̏�Ԃ�ۑ�����

	std::vector<std::vector<VECTOR2>> read_blockPositionList;//�u���b�N�̍��W��ۑ�����

public:

	World1_Stage();//�R���X�g���N�^

	//json�t�@�C����ǂݍ��ށi������Stage�ԍ��������Ă���j
	void ReadFile(int _stageNumber);

	void Init(HWND hWnd); //������

	void Update(void);    //�X�V
	void Draw();          //�`�� 
	void Uninit();        //�I��  
};

