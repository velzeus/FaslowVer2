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
	// 頂点データを決める
	Vertex vertexList[4] =
	{
		//  x    y    z    r    g    b    a    u    v  
		{-0.5f, 0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,0.0f,0.0f }, // ０番目の頂点座標
		{ 0.5f, 0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,1.0f,0.0f }, // １番目の頂点座標
		{-0.5f,-0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,0.0f,1.0f}, // ２番目の頂点座標
		{ 0.5f,-0.5f,0.5f, 1.0f,1.0f,1.0f,1.0f,1.0f,1.0f}, // ３番目の頂点座標
	};

	//座標
	DirectX::XMFLOAT3 pos = { 0.0f,0.0f,0.0f };
	//大きさ
	DirectX::XMFLOAT3 size = { 100.0f,100.0f,0.0f };
	//角度
	float angle = 0.0f;
	//色
	DirectX::XMFLOAT4 color = { 1.0f,1.0f,1.0f,1.0f };

	// 頂点バッファ
	ID3D11Buffer* m_pVertexBuffer;
	//テクスチャ用変数
	ID3D11ShaderResourceView* m_pTextureView;

	//テクスチャが縦横に何分割されているか
	int splitX = 1;
	int splitY = 1;


public:
	//左上から何段目を切り抜いて表示するか
	float numU = 0;
	float numV = 0;
	int anim_flg = 0;
	int anim_cnt = 0;
	//Direction direction = right;

	void Init(const wchar_t* imgname, int sx = 1, int sy = 1);//初期化
	void Draw();                                        //描画
	void Uninit();                                      //終了

	/*セット関数*/
	void SetPos(float x, float y, float z);             //座標をセット
	void SetSize(float x, float y, float z);            //大きさをセット
	void SetAngle(float a);                             //角度をセット
	void SetColor(float r, float g, float b, float a);  //色をセット

	/*ゲット関数*/
	DirectX::XMFLOAT3 GetPos(void);                     //座標をゲット
	DirectX::XMFLOAT3 GetSize(void);                    //大きさをゲット
	float GetAngle(void);                               //角度をゲット
	DirectX::XMFLOAT4 GetColor(void);                   //色をゲット


	void Animation(int fps = 10, Direction direct = front); //オブジェクトのアニメーション(引数：何秒に1回切り替えるか）
};