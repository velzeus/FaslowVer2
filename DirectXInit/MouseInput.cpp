#include "MouseInput.h"

MouseInput::MouseInput()
    : isLeftButtonDown(false) {
    clickPosition = { 0, 0 };
    releasePosition = { 0, 0 };
}

MouseInput::~MouseInput() {}

MouseInput* MouseInput::GetInstance()
{
    if(instance!=nullptr) return instance;

    static MouseInput _instance;
    return &_instance;
}

void MouseInput::Update() {
    // �}�E�X�̏�Ԃ��擾
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // ���{�^���������ꂽ�Ƃ�
        if (!isLeftButtonDown) {
            isLeftButtonDown = true;
            // ���݂̃}�E�X�J�[�\���ʒu���擾
            GetCursorPos(&clickPosition);
            ScreenToClient(GetActiveWindow(), &clickPosition); // �N���C�A���g���W�ɕϊ�
        }
    }
    else { // ���{�^���������ꂽ�Ƃ�
        if (isLeftButtonDown) {
            isLeftButtonDown = false;
            // ���݂̃}�E�X�J�[�\���ʒu���擾
            GetCursorPos(&releasePosition);
            ScreenToClient(GetActiveWindow(), &releasePosition); // �N���C�A���g���W�ɕϊ�
        }
    }
}

POINT MouseInput::GetClickPosition() const {
    return clickPosition;
}

POINT MouseInput::GetReleasePosition() const {
    return releasePosition;
}

bool MouseInput::IsLeftButtonDown() const {
    return isLeftButtonDown;
}
