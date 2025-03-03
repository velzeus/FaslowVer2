#include "Scene.h"


DirectX::XMFLOAT3 Scene::RotateVector(DirectX::XMFLOAT3 _target, DirectX::XMFLOAT3 _base)
{
	//方向ベクトル
	DirectX::XMFLOAT3 direction;

	//目標-基準でのベクトル
	direction.x = _target.x - _base.x;
	direction.y = _target.y - _base.y;

	return direction;
}

float Scene::VectorLength(DirectX::XMFLOAT3 _direction)
{
	float length = std::sqrt((_direction.x * _direction.x) + (_direction.y * _direction.y));
	return length;
}

DirectX::XMFLOAT3 Scene::NormalizedRotateVector(DirectX::XMFLOAT3 _direction)
{
	DirectX::XMFLOAT3 normalizedDirection
	{
		_direction.x / VectorLength(_direction),
		_direction.y / VectorLength(_direction),
		0
	};

	return normalizedDirection;
}

//コンストラクタ
Scene::Scene(SCENENAME _sceneName):sceneName(_sceneName){
	//初期化
	//Start();
	std::cout << SceneManager::GetInstance()->SceneNameToString(_sceneName)
		<< ": Sceneコンストラクタ" << std::endl;

}

Scene::~Scene()
{
	//終了
	//End();


}

//開始処理
int Scene::Start()
{
	//シーン開始時の処理
	std::cout << "error is Scene::Strt" << std::endl;

	return 0;
}

//更新処理
int Scene::Update()
{
	//シーン更新時の処理

	//シーンを変更
	if (0)
	{
		SceneManager::GetInstance()->ChangeScene(RESULT);
	}
	
	return 0;
}

//描画処理
int Scene::Draw()
{
	//シーン描画時の処理

	return 0;
}

//終了処理
int Scene::End()
{
	//シーン終了時の処理

	return 0;
}

SCENENAME Scene::GetSceneName()
{
	std::cout << "GetSceneNameが読み出されました:sceneName(" 
		<< sceneName << ")" << std::endl;
	return sceneName;
}
