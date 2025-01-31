#pragma once
#include<fstream>
#include"../../json.hpp"
#include "../Scene.h"
#include"../../BlockBace.h"

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

//���W���擾���邽�߂̍\����
struct VECTOR2
{
    float x, y;
};

class StageScene :
    public Scene
{
public:
    StageScene();
    ~StageScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //json�t�@�C����ǂݍ��ށi������Stage�ԍ��������Ă���j
    void ReadFile();

private:
    SceneManager* manager;

	//MouseInput* mouseInput;

	TS::TS_InputSystem* inputSystem;

    std::vector<std::vector<int>> read_gridStateList;//�}�X�ڂ̏�Ԃ�ۑ�����

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//�u���b�N�̍��W��ۑ�����

    Object grids[STAGE_X][STAGE_Y];

	int gridData[STAGE_X][STAGE_Y];

	//BlockBase�ŉ��u��
	//BlockBace* blocks[STAGE_X][STAGE_Y];
	std::vector<BlockBace*> blocks;

	//�I�v�V�����{�^��
	Object optionButton;

	//�S�[���i���j
	Object gorl;

};

