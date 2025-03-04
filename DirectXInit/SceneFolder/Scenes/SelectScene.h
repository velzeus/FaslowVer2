#pragma once
#include "../Scene.h"

//��ʂɕ\��������̂̏��
enum DRAWSTATE
{
    WORLDSELECTSCENE = 0,
    STAGESELECTSCENE,
    SETSTAGE,
    MOVEFLAME,
};

#define FLAMENUM (20)

class SelectScene :
    public Scene
{
public:
    SelectScene();
    ~SelectScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

private:
    
    WORLDNUMBER worldNum;
    STAGENUMBER stageNum;

    DRAWSTATE stateNum;

   // MouseInput* mouseInput;
    
    TS::TS_InputSystem* inputSystem;

    //���[���h
    Object selectImage_world[6];

    //World�̕���
    Object worldNameImage[6];

    //�ԍ�
    Object numberText[6];

    //�X�e�[�W
    Object selectImage_stage[5];

    //Stage�̕���
    Object stageNameImage[5];
    
    //�߂�{�^��
    Object backButton;

    //�w�i
    Object backGround;

    //�X�e�[�W���
    Object stageTexture;

    //�X�e�[�W��
    Object stageName;

    //�X�e�[�W���̘g
    Object stageNameFlame;

    //�X�e�[�W���̔ԍ�
    Object stageNameNumber;

    //�X�^�[�g�{�^��
    Object startButton;

    //���j���[�{�^��
    Object menuButton;

    //�������p�̘g
    Object moveFlame;

    //�g�𓮂���
    bool MoveFlame();

    //���K�����������x�N�g��
    DirectX::XMFLOAT3 normalizedDirection;

    DirectX::XMFLOAT3 normalizedScaleVector;

    //�ړ����鑬�x
    float moveSpeed;

    //�傫���̕ω���
    float deltaScale;

    //�ڕW�n�_�̍��W
    //DirectX::XMFLOAT3 targetPos;

    //�ړ������������t���[����
    int moveCount;

    ////�ڕW�̑傫��
    //DirectX::XMFLOAT3 targetScale;
    //�����x�N�g��
    //DirectX::XMFLOAT3 direction;

    //�x�N�g���̒���

};

