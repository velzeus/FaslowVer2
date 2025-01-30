#include "HoldArea.h"


void HoldArea::Init(HWND hWnd)
{
    // ホールドエリアの中心座標
    float centerX = -190.0f;
    float centerY = -403.0f;

    // 各ブロックの初期化
    for (int x = 0; x < 19; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            // それぞれのブロックの初期化
            blocks[x][y].Init(L"asset/block.png");  // ブロック画像をセット
            blocks[x][y].SetSize(40.0f, 40.0f, 0.0f);  // ブロックサイズ40x40に設定

            // 座標を設定 (中心から計算)
            blocks[x][y].SetPos(centerX + x * 80.0f, centerY + y * 80.0f, 0.0f);
        }
    }
}

void HoldArea::Draw()
{
    // 各ブロックを描画
    for (int x = 0; x < 19; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            blocks[x][y].Draw();
        }
    }
}

void HoldArea::SetPos(float x, float y, float z)
{
    // ホールドエリア全体の位置を設定
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            blocks[i][j].SetPos(x, y, z);
        }
    }
}

void HoldArea::SetSize(float width, float height, float depth)
{
    // ホールドエリア全体のサイズを設定
    for (int i = 0; i < 19; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            blocks[i][j].SetSize(width, height, depth);
        }
    }
}
