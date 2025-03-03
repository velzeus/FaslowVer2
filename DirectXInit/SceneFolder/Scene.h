#pragma once
#include"SceneManager.h"
#include"../direct3d.h"

//前方宣言
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

	//方向ベクトルを求めて返す関数
	DirectX::XMFLOAT3 RotateVector(DirectX::XMFLOAT3 _target, DirectX::XMFLOAT3 _base);

	//方向ベクトルの長さを求めて返す
	float VectorLength(DirectX::XMFLOAT3 _direction);

	//正規化した方向ベクトルを返す
	DirectX::XMFLOAT3 NormalizedRotateVector(DirectX::XMFLOAT3 _direction);

public:
	//コンストラクタ、デストラクタ
	Scene(SCENENAME _sceneName);
	virtual ~Scene();

	virtual int Start();
	virtual int Update();
	virtual int Draw();
	virtual int End();

	SCENENAME GetSceneName();
};


