#pragma once
#include <Windows.h>

class MouseInput {
private:
    POINT clickPosition; // 左クリックした位置
    POINT releasePosition; // 左クリックを離した位置
    bool isLeftButtonDown; // 左ボタンが押されているか

    static MouseInput* instance;
    MouseInput();

public:
    ~MouseInput();

    static MouseInput* GetInstance();


    void Update(); // マウス入力の状態を更新する
    POINT GetClickPosition() const; // 左クリックした座標を取得
    POINT GetReleasePosition() const; // 左クリックを離した座標を取得
    bool IsLeftButtonDown() const; // 左ボタンが押されているか
};
