#pragma once
#include"Object.h"


enum DIRECTION
{
	DOWN,//��
	RIGHT,//�E
	UP,//��
	LEFT,//��
	STOP//�~�܂�
};


class Ball :public Object
{
private:
	bool rotDirection = true;//��]�����̎w�� true:�E�@false:��
	DIRECTION crntDrct;//�{�[�����������Ă����
	DIRECTION precDrct;//�{�[�����������Ă�����
	DIRECTION moveDir = LEFT; // �{�[���̈ړ����� (�V�����ǉ�)

public:
	Ball();
	Ball(bool _rotDir);

	DIRECTION GetMoveDir();//�i�s�����̃Q�b�^�[
	void SetMoveDir(DIRECTION dir);//�i�s�����̃Z�b�^�[
	void Move();//�ړ�

	void Move_Cannon(DirectX::XMFLOAT3 _normalizedDirection);

	bool GetrotDir();//��]�����̃Q�b�^�[
	void SetrotDir(bool _rotdir);//��]�����̃Z�b�^�[

	void Setborder();//�[�ɍs�������̏���

	float vel_x = 1.0f;//���̈ړ���
	float vel_y = 1.0f;//�c�̈ړ���
};