#pragma once
#include"../../BlockFanction.h"
#include"../Scene.h"
#include<memory>

#define STAGE_WIDTH		(32)	// ����
#define STAGE_HEIGHT	(18)	// ����

// �����N�Ƃ͈Ⴄ������StageScene���쐬
class TS_StageScene:public Scene
{
public:

	int Start() override;	// �X�e�[�W�̏�����
	int Update() override;	// �X�e�[�W�̃A�b�v�f�[�g���s��
	int Draw() override;	// �X�e�[�W�̕`��
	int End() override;		// �X�e�[�W�̌㏈��

private:

	
	TS::TS_InputSystem* inputSystem;	// ����

	// Ball�̓����蔻��
	HitColBlock hitColBlack[4];

	std::unordered_map<GridState, std::shared_ptr<Object>> constantObject;
	
	Object ball;
	Object coin;
};

