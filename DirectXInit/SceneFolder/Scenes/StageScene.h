#pragma once
#include<fstream>
#include"../../json.hpp"
#include "../Scene.h"
#include"../../BlockBace.h"
#include"../../Ball.h"
#include"../../Cannon.h"
#include"../../CutAndPaste.h"
#include <vector>
#include <utility> // std::pair ���g������
#include<iostream>
#include <unordered_map>
#include<algorithm>
using namespace std;



#define STAGE_X (32)//���̃}�X��
#define STAGE_Y (18)//�c�̃}�X��

//�u���b�N�̃T�C�Y
#define BLOCKSIZE_X (40)
#define BLOCKSIZE_Y (40)



//GridState��BlockBace�Ɉڂ��܂���



class StageScene :
    public Scene
{
public:

	Ball ball;
    StageScene();
    ~StageScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //json�t�@�C����ǂݍ��ށi������Stage�ԍ��������Ă���j
    void ReadFile();

	//Ball ball;//�{�[��

	void UpdateMoveDir();

	DirectX::XMFLOAT3 center;//�{�[���̈ʒu
	DirectX::XMFLOAT3 prvpos;//�{�[���̉ߋ��̈ʒu
	std::vector<std::pair<float, float>> surroundingBlocks;//���͂W�}�X�̂����蔻��
	bool Collision(BlockBace* obj1, const std::pair<float, float>& obj2);//�����蔻��

	std::vector<BlockBace*> GetNearbyBlocks(const std::vector<std::pair<float, float>>& surroundingBlocks);//�X�e�[�W��ɂ�����͂W�}�X���擾
	std::vector<BlockBace*> nearbyBlocks;//�{�[���̎���8�}�X�ɑ��݂���u���b�N

	//�{�[�����u���b�N�̋�؂�ɂ���Ƃ����������蔻������s
	bool onGridX;
	bool onGridY;

	int prv_index = -1;//�����������ʂ̃u���b�N

	//�O�Ffront�@�P�Fback�@�Q�Fleft�@�R�Fright
	int hitIndex[4] = { -1,-1,-1,-1 };//���������u���b�N�̓Y����
	int hitSafe[4] = { -1,-1,-1,-1 };//���������u���b�N���Z�[�u����
	bool hitFlgs[4] = { false,false,false,false };//�����蔻��
	GridState hitBlockType[4] = { NULLBLOCK ,NULLBLOCK ,NULLBLOCK ,NULLBLOCK };//���������u���b�N�̎��
	void CheckSurroundingCollisions();

	DIRECTION _moveDir;


	void SetGridStateList(std::vector<std::vector<int>> _gridStateList);
	std::vector<std::vector<int>> GetGridStateList();

private:
    SceneManager* manager;

	//MouseInput* mouseInput;

	TS::TS_InputSystem* inputSystem;

    std::vector<std::vector<int>> read_gridStateList;//�}�X�ڂ̏�Ԃ�ۑ�����

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//�u���b�N�̍��W��ۑ�����

    //Object grids[STAGE_X][STAGE_Y];

	int gridData[STAGE_X][STAGE_Y];

	//BlockBase�ŉ��u��
	//BlockBace* blocks[STAGE_X][STAGE_Y];
	std::vector<BlockBace*> blocks;

	std::vector<Cannon*> cannons;

	//�I�v�V�����{�^��
	Object optionButton;

	//���g���C�{�^��
	Object retryButton;

	//�S�[���i���j
	Object gorl;

	//�w�i
	Object background;

	//�R�C��
	Object coin;

	//�J�b�g�{�^��
	Object cutButton;

	//
	Object holdAreaFlame;



	//�F��ς���t���O
	bool accelerationFlg;

	bool triggerFlg_O;
	bool triggerFlg_N;
	bool triggerFlg_T;

	int cannonIndex;

	bool cannonFlg;


	CutAndPaste cutAndPaste;

	//Area area;

	std::vector<Area*> holdAreas;

	int gridIndex_X[2] = {};
	int gridIndex_Y[2] = {};

	int animCount;

	bool addFlg;
};

