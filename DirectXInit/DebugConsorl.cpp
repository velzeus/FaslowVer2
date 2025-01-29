#include "DebugConsorl.h"
#include<Windows.h>
#include<iostream>
#include<fstream>


#ifdef _DEBUG
void DebugConsole()
{
    // �f�o�b�O�p�R���\�[�����쐬
    AllocConsole(); // �R���\�[���E�B���h�E���쐬

    // cout�p�̃R���\�[���o�͂����_�C���N�g
    FILE* stream;
    if (freopen_s(&stream, "CONOUT$", "w", stdout) != 0) {
        std::cerr << "Failed to redirect stdout to console!" << std::endl; // �G���[�o��
    }

    // cin�p�̃R���\�[�����͂����_�C���N�g
    if (freopen_s(&stream, "CONIN$", "r", stdin) != 0) {
        std::cerr << "Failed to redirect stdin to console!" << std::endl; // �G���[�o��
    }


}
#else
void DebugConsole() {
    return;
}

#endif // DEBUG