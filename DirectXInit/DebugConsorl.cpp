#include "DebugConsorl.h"
#include<Windows.h>
#include<iostream>
#include<fstream>


#ifdef _DEBUG
void DebugConsole()
{
    // デバッグ用コンソールを作成
    AllocConsole(); // コンソールウィンドウを作成

    // cout用のコンソール出力をリダイレクト
    FILE* stream;
    if (freopen_s(&stream, "CONOUT$", "w", stdout) != 0) {
        std::cerr << "Failed to redirect stdout to console!" << std::endl; // エラー出力
    }

    // cin用のコンソール入力をリダイレクト
    if (freopen_s(&stream, "CONIN$", "r", stdin) != 0) {
        std::cerr << "Failed to redirect stdin to console!" << std::endl; // エラー出力
    }


}
#else
void DebugConsole() {
    return;
}

#endif // DEBUG