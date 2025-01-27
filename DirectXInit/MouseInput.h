#pragma once
#include <Windows.h>

class MouseInput {
private:
    POINT clickPosition; // ���N���b�N�����ʒu
    POINT releasePosition; // ���N���b�N�𗣂����ʒu
    bool isLeftButtonDown; // ���{�^����������Ă��邩

public:
    MouseInput();
    ~MouseInput();

    void Update(); // �}�E�X���͂̏�Ԃ��X�V����
    POINT GetClickPosition() const; // ���N���b�N�������W���擾
    POINT GetReleasePosition() const; // ���N���b�N�𗣂������W���擾
    bool IsLeftButtonDown() const; // ���{�^����������Ă��邩
};
