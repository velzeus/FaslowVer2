#include "Object.h"
#include <stdio.h>
#include<iostream>
#include<fstream>


void Object::Init(const wchar_t* imgname, int sx, int sy)
{

	splitX = sx;
	splitY = sy;
	vertexList[1].u = 1.0f / splitX;
	vertexList[2].v = 1.0f / splitY;
	vertexList[3].u = 1.0f / splitX;
	vertexList[3].v = 1.0f / splitY;
	// 頂点バッファを作成する
	// ※頂点バッファ→VRAMに頂点データを置くための機能
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// 確保するバッファサイズを指定
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// 頂点バッファ作成を指定
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAMに送るデータを指定
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr)) return ;

	//インスタンス取得
	textureManager = TextureManager::GetInstance();

	//テクスチャ読み込み
	//ComPtrの場合
	m_pTextureView = textureManager->LoadTexture(g_pDevice, g_pDeviceContext, imgname);

	
	////テクスチャ読込
	//hr = DirectX::CreateWICTextureFromFile(g_pDevice,imgname, NULL, &m_pTextureView);
	//if (FAILED(hr))
	//{
	//	if (FAILED(hr))
	//	{
	//		char errorMsg[256];
	//		sprintf_s(errorMsg, "テクスチャ読込失敗, HRESULT: 0x%08X", hr);
	//		std::cout << errorMsg << std::endl;
	//		MessageBoxA(NULL, errorMsg, "エラー", MB_ICONERROR | MB_OK);
	//	}
	//	
	//	if (!std::ifstream(imgname)) {
	//		std::cout << "指定されたファイルが存在しません" << std::endl;
	//		MessageBoxA(NULL, "指定されたファイルが存在しません", "エラー", MB_ICONERROR | MB_OK);
	//		
	//	}
	//
	//	if (g_pDevice == nullptr) {
	//		MessageBoxA(NULL, "グローバルデバイスがnullptrです", "エラー", MB_ICONERROR | MB_OK);
	//		
	//	}

	//	MessageBoxA(NULL, "テクスチャ読込失敗", "エラー", MB_ICONERROR | MB_OK);
	//	return ;
	//}
}

void Object::Draw()
{
	//頂点バッファを設定
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	//テクスチャをピクセルシェーダーに渡す
	/*g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);*/
	//ComPtrを用いる場合
	g_pDeviceContext->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());

	//定数バッファを更新
	ConstBuffer cb;
	//プロジェクション変換行列を作成
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	//ワールド変換行列の作成
	//オブジェクトの位置・大きさ・向きを指定
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14 / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	//UVアニメーションの行列作成
	float u = (float)numU / splitX;
	float v = (float)numV / splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	//頂点カラーのデータを作成
	cb.color = color;

	//行列をシェーダーに渡す
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);
	g_pDeviceContext->Draw(4, 0); // 描画命令
}

void Object::Uninit()
{
	//開放処理
	SAFE_RELEASE(m_pVertexBuffer);
	//SAFE_RELEASE(m_pTextureView);
}

void Object::SetPos(float x, float y, float z)
{
	//座標をセットする
	pos.x = x;
	pos.y = y;
	pos.z = z;

}

void Object::SetSize(float x, float y, float z)
{
	//大きさをセットする
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetAngle(float a)
{
	//角度をセットする
	angle=a;
}

void Object::SetColor(float r, float g, float b, float a)
{
	//色をセットする
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

DirectX::XMFLOAT3 Object::GetPos(void)
{
	return pos;//座標をゲット
}

DirectX::XMFLOAT3 Object::GetSize(void)
{
	return size;//大きさをゲット
}

float Object::GetAngle(void)
{
	return angle;//角度をゲット
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return color;//色をゲット
}


void Object::Animation(int fps, Direction direct)
{
	numV = direct;
	//0.1.2.1.0の順番にする
	//フラグ切り替え
	if (anim_cnt == 0)
	{
		anim_flg = 0;
	}
	if (anim_cnt == fps*3)
	{
		anim_flg = 1;
	}

	//カウント計算
	if (anim_flg == 0)
	{
		anim_cnt++;
	}
	else if (anim_flg == 1)
	{
		anim_cnt--;
	}


	//フレームレート計算
	if (anim_cnt / fps == 0)
	{
		numU = 0;
	}
	else if (anim_cnt / fps == 1)
	{
		numU = 1;
	}
	else if (anim_cnt / fps == 2)
	{
		numU = 2;
	}

}
