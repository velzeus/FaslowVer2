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
	// ���_�o�b�t�@���쐬����
	// �����_�o�b�t�@��VRAM�ɒ��_�f�[�^��u�����߂̋@�\
	D3D11_BUFFER_DESC bufferDesc;
	bufferDesc.ByteWidth = sizeof(vertexList);// �m�ۂ���o�b�t�@�T�C�Y���w��
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;// ���_�o�b�t�@�쐬���w��
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA subResourceData;
	subResourceData.pSysMem = vertexList;// VRAM�ɑ���f�[�^���w��
	subResourceData.SysMemPitch = 0;
	subResourceData.SysMemSlicePitch = 0;

	HRESULT hr = g_pDevice->CreateBuffer(&bufferDesc, &subResourceData, &m_pVertexBuffer);
	if (FAILED(hr)) return ;

	//�C���X�^���X�擾
	textureManager = TextureManager::GetInstance();

	//�e�N�X�`���ǂݍ���
	//ComPtr�̏ꍇ
	m_pTextureView = textureManager->LoadTexture(g_pDevice, g_pDeviceContext, imgname);

	
	////�e�N�X�`���Ǎ�
	//hr = DirectX::CreateWICTextureFromFile(g_pDevice,imgname, NULL, &m_pTextureView);
	//if (FAILED(hr))
	//{
	//	if (FAILED(hr))
	//	{
	//		char errorMsg[256];
	//		sprintf_s(errorMsg, "�e�N�X�`���Ǎ����s, HRESULT: 0x%08X", hr);
	//		std::cout << errorMsg << std::endl;
	//		MessageBoxA(NULL, errorMsg, "�G���[", MB_ICONERROR | MB_OK);
	//	}
	//	
	//	if (!std::ifstream(imgname)) {
	//		std::cout << "�w�肳�ꂽ�t�@�C�������݂��܂���" << std::endl;
	//		MessageBoxA(NULL, "�w�肳�ꂽ�t�@�C�������݂��܂���", "�G���[", MB_ICONERROR | MB_OK);
	//		
	//	}
	//
	//	if (g_pDevice == nullptr) {
	//		MessageBoxA(NULL, "�O���[�o���f�o�C�X��nullptr�ł�", "�G���[", MB_ICONERROR | MB_OK);
	//		
	//	}

	//	MessageBoxA(NULL, "�e�N�X�`���Ǎ����s", "�G���[", MB_ICONERROR | MB_OK);
	//	return ;
	//}
}

void Object::Draw()
{
	//���_�o�b�t�@��ݒ�
	UINT strides = sizeof(Vertex);
	UINT offsets = 0;
	g_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &strides, &offsets);

	//�e�N�X�`�����s�N�Z���V�F�[�_�[�ɓn��
	/*g_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);*/
	//ComPtr��p����ꍇ
	g_pDeviceContext->PSSetShaderResources(0, 1, m_pTextureView.GetAddressOf());

	//�萔�o�b�t�@���X�V
	ConstBuffer cb;
	//�v���W�F�N�V�����ϊ��s����쐬
	cb.matrixProj = DirectX::XMMatrixOrthographicLH(SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 3.0f);
	cb.matrixProj = DirectX::XMMatrixTranspose(cb.matrixProj);

	//���[���h�ϊ��s��̍쐬
	//�I�u�W�F�N�g�̈ʒu�E�傫���E�������w��
	cb.matrixWorld = DirectX::XMMatrixScaling(size.x, size.y, size.z);
	cb.matrixWorld *= DirectX::XMMatrixRotationZ(angle * 3.14 / 180);
	cb.matrixWorld *= DirectX::XMMatrixTranslation(pos.x, pos.y, pos.z);
	cb.matrixWorld = DirectX::XMMatrixTranspose(cb.matrixWorld);

	//UV�A�j���[�V�����̍s��쐬
	float u = (float)numU / splitX;
	float v = (float)numV / splitY;
	cb.matrixTex = DirectX::XMMatrixTranslation(u, v, 0.0f);
	cb.matrixTex = DirectX::XMMatrixTranspose(cb.matrixTex);

	//���_�J���[�̃f�[�^���쐬
	cb.color = color;

	//�s����V�F�[�_�[�ɓn��
	g_pDeviceContext->UpdateSubresource(g_pConstantBuffer, 0, NULL, &cb, 0, 0);
	g_pDeviceContext->Draw(4, 0); // �`�施��
}

void Object::Uninit()
{
	//�J������
	SAFE_RELEASE(m_pVertexBuffer);
	//SAFE_RELEASE(m_pTextureView);
}

void Object::SetPos(float x, float y, float z)
{
	//���W���Z�b�g����
	pos.x = x;
	pos.y = y;
	pos.z = z;

}

void Object::SetSize(float x, float y, float z)
{
	//�傫�����Z�b�g����
	size.x = x;
	size.y = y;
	size.z = z;
}

void Object::SetAngle(float a)
{
	//�p�x���Z�b�g����
	angle=a;
}

void Object::SetColor(float r, float g, float b, float a)
{
	//�F���Z�b�g����
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;
}

DirectX::XMFLOAT3 Object::GetPos(void)
{
	return pos;//���W���Q�b�g
}

DirectX::XMFLOAT3 Object::GetSize(void)
{
	return size;//�傫�����Q�b�g
}

float Object::GetAngle(void)
{
	return angle;//�p�x���Q�b�g
}

DirectX::XMFLOAT4 Object::GetColor(void)
{
	return color;//�F���Q�b�g
}


void Object::Animation(int fps, Direction direct)
{
	numV = direct;
	//0.1.2.1.0�̏��Ԃɂ���
	//�t���O�؂�ւ�
	if (anim_cnt == 0)
	{
		anim_flg = 0;
	}
	if (anim_cnt == fps*3)
	{
		anim_flg = 1;
	}

	//�J�E���g�v�Z
	if (anim_flg == 0)
	{
		anim_cnt++;
	}
	else if (anim_flg == 1)
	{
		anim_cnt--;
	}


	//�t���[�����[�g�v�Z
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
