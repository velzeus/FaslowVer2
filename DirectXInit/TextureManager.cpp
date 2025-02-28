#include "TextureManager.h"

//�ÓI�����o�̏�����
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
    //�w�肵���e�N�X�`���摜���ǂݍ��܂�Ă��Ȃ�������
    if (textureList.find(_fileName) == textureList.end())
    {
        Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> texture;
        //�R���e�L�X�g��p���Ȃ��ōs��
        //HRESULT hr = DirectX::CreateWICTextureFromFile(_device, /*context,*/ _fileName.c_str(), nullptr, texture.GetAddressOf());
        HRESULT hr = DirectX::CreateWICTextureFromFile(_device, _context, _fileName.c_str(), NULL, texture.GetAddressOf());

        if (SUCCEEDED(hr))
        {
            //�ǂݍ��񂾃e�N�X�`�����i�[
            textureList[_fileName] = texture;
        }
        else
        {
            if (FAILED(hr))
            {
                char errorMsg[256];
                sprintf_s(errorMsg, "�e�N�X�`���Ǎ����s, HRESULT: 0x%08X", hr);
                std::cout << errorMsg << std::endl;
                MessageBoxA(NULL, errorMsg, "�G���[", MB_ICONERROR | MB_OK);
            }

            if (!std::ifstream(_fileName)) {
                std::cout << "�w�肳�ꂽ�t�@�C�������݂��܂���" << std::endl;
                MessageBoxA(NULL, "�w�肳�ꂽ�t�@�C�������݂��܂���", "�G���[", MB_ICONERROR | MB_OK);

            }

            if (_device == nullptr) {
                MessageBoxA(NULL, "�O���[�o���f�o�C�X��nullptr�ł�", "�G���[", MB_ICONERROR | MB_OK);

            }

            MessageBoxA(NULL, "�e�N�X�`���Ǎ����s", "�G���[", MB_ICONERROR | MB_OK);
        }
    }

    //�ǂݍ��܂�Ă���e�N�X�`����Ԃ�
    return textureList[_fileName];
}

TextureManager::~TextureManager()
{
    delete instance;
}
