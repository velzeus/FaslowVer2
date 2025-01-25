#pragma once
#include "direct3d.h"
#include "WICTextureLoader.h"

typedef enum
{
	front,
	left,
	right,
	back
	
}Direction;

class Object
{
private:
	// ���_�f�[�^�����߂�
	Vertex vertexList[4] =
	{
		//  x    y    z    r    g    b    a    u    v  
		{-0.5f, 0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,0.0f,0.0f }, // �O�Ԗڂ̒��_���W
		{ 0.5f, 0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,1.0f,0.0f }, // �P�Ԗڂ̒��_���W
		{-0.5f,-0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,0.0f,1.0f}, // �Q�Ԗڂ̒��_���W
		{ 0.5f,-0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // �R�Ԗڂ̒��_���W
	};

	//���W
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	//�傫��
	DirectX::XMFLOAT3 size = { 100.0f,100.0f,0.0f };
	//�p�x
	float angle = 0.0f;
	//�F
	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	// ���_�o�b�t�@
	ID3D11Buffer* m_pVertexBuffer;
	//�e�N�X�`���p�ϐ�
	ID3D11ShaderResourceView* m_pTextureView;

	//�e�N�X�`�����c���ɉ���������Ă��邩
	int splitX = 1;
	int splitY = 1;


public:
	//���ォ�牽�i�ڂ�؂蔲���ĕ\�����邩
	float numU = 0;
	float numV = 0;
	int anim_flg = 0;
	int anim_cnt = 0;
	//Direction direction = right;

	void Init(const wchar_t* imgname, int sx = 1, int sy = 1);//������
	void Draw();                                        //�`��
	void Uninit();                                      //�I��

	/*�Z�b�g�֐�*/
	void SetPos(float x, float y, float z);             //���W���Z�b�g
	void SetSize(float x, float y, float z);            //�傫�����Z�b�g
	void SetAngle(float a);                             //�p�x���Z�b�g
	void SetColor(float r, float g, float b, float a);  //�F���Z�b�g

	/*�Q�b�g�֐�*/
	DirectX::XMFLOAT3 GetPos(void);                     //���W���Q�b�g
	DirectX::XMFLOAT3 GetSize(void);                    //�傫�����Q�b�g
	float GetAngle(void);                               //�p�x���Q�b�g
	DirectX::XMFLOAT4 GetColor(void);                   //�F���Q�b�g


	void Animation(int fps = 10, Direction direct = front); //�I�u�W�F�N�g�̃A�j���[�V����(�����F���b��1��؂�ւ��邩�j
};