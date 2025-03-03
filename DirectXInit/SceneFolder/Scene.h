#pragma once
#include"SceneManager.h"
#include"../direct3d.h"

//�O���錾
enum SCENENAME;

enum WORLDNUMBER;
enum STAGENUMBER;

class SceneManager;

class TitleScene;
class SelectScene;
class StageScene;

class Scene
{
protected:
	const SCENENAME sceneName;

	//�����x�N�g�������߂ĕԂ��֐�
	DirectX::XMFLOAT3 RotateVector(DirectX::XMFLOAT3 _target, DirectX::XMFLOAT3 _base);

	//�����x�N�g���̒��������߂ĕԂ�
	float VectorLength(DirectX::XMFLOAT3 _direction);

	//���K�����������x�N�g����Ԃ�
	DirectX::XMFLOAT3 NormalizedRotateVector(DirectX::XMFLOAT3 _direction);

public:
	//�R���X�g���N�^�A�f�X�g���N�^
	Scene(SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	SCENENAME GetSceneName();
};


