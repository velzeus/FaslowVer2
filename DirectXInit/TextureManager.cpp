#include "TextureManager.h"

//静的メンバの初期化
TextureManager* TextureManager::instance = nullptr;

TextureManager* TextureManager::GetInstance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}

Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> TextureManager::LoadTexture(ID3D11Device* _device, ID3D11DeviceContext* _context, const std::wstring& _fileName)
{
    //指定したテクスチャ画像が読み込まれていなかったら
    if (textureList.find(_fileName) == textureList.end())
    {
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
        //コンテキストを用いないで行う
        //HRESULT hr = DirectX::CreateWICTextureFromFile(_device, /*context,*/ _fileName.c_str(), nullptr, texture.GetAddressOf());
        HRESULT hr = DirectX::CreateWICTextureFromFile(_device, _context, _fileName.c_str(), NULL, texture.GetAddressOf());

        if (SUCCEEDED(hr))
        {
            //読み込んだテクスチャを格納
            textureList[_fileName] = texture;
        }
        else
        {
            if (FAILED(hr))
            {
                char errorMsg[256];
                sprintf_s(errorMsg, "テクスチャ読込失敗, HRESULT: 0x%08X", hr);
                std::cout << errorMsg << std::endl;
                MessageBoxA(NULL, errorMsg, "エラー", MB_ICONERROR | MB_OK);
            }

            if (!std::ifstream(_fileName)) {
                std::cout << "指定されたファイルが存在しません" << std::endl;
                MessageBoxA(NULL, "指定されたファイルが存在しません", "エラー", MB_ICONERROR | MB_OK);

            }

            if (_device == nullptr) {
                MessageBoxA(NULL, "グローバルデバイスがnullptrです", "エラー", MB_ICONERROR | MB_OK);

            }

            MessageBoxA(NULL, "テクスチャ読込失敗", "エラー", MB_ICONERROR | MB_OK);
        }
    }

    //読み込まれているテクスチャを返す
    return textureList[_fileName];
}

TextureManager::~TextureManager()
{
    delete instance;
}
