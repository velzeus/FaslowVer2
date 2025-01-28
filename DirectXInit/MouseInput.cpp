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
    // マウスの状態を取得
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) { // 左ボタンが押されたとき
        if (!isLeftButtonDown) {
            isLeftButtonDown = true;
            // 現在のマウスカーソル位置を取得
            GetCursorPos(&clickPosition);
            ScreenToClient(GetActiveWindow(), &clickPosition); // クライアント座標に変換
        }
    }
    else { // 左ボタンが離されたとき
        if (isLeftButtonDown) {
            isLeftButtonDown = false;
            // 現在のマウスカーソル位置を取得
            GetCursorPos(&releasePosition);
            ScreenToClient(GetActiveWindow(), &releasePosition); // クライアント座標に変換
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
