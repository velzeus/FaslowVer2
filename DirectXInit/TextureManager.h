#pragma once
#include"WICTextureLoader.h"
#include<unordered_map>
#include<wrl.h>
#include<wrl/client.h>
#include<string>
#include <stdio.h>
#include<iostream>
#include<fstream>
class TextureManager
{
public:
	static TextureManager* GetInstance();//シングルトン方式を採用

	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> LoadTexture(ID3D11Device* _device, ID3D11DeviceContext* _context, const std::wstring& _fileName);
private:
	~TextureManager();

	//静的メンバ変数
	static TextureManager* instance;

	std::unordered_map<std::wstring, Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>> textureList;
};

