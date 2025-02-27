#include "HoldArea.h"

// コンストラクタ
HoldArea::HoldArea(Hold* holdInstance)
{
    hold = holdInstance;
}

// 初期化処理
void HoldArea::Init()
{
    // 各保存エリアのスプライトを初期化
    for (int i = 0; i < 5; i++)
    {
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                holdBlocks[i][x][y].Init(L"asset/block.png");  // 画像の初期化
                holdBlocks[i][x][y].SetSize(40.0f, 40.0f, 0.0f);  // サイズ設定
            }
        }
    }
}
void HoldArea::Update()
{
    MouseInput* mouse = MouseInput::GetInstance();

    if (!mouse->IsLeftButtonDown()) return;  // クリックされていなければ無視

    POINT clickPos = mouse->GetClickPosition();
    const auto& holdData = hold->GetHoldData();

    for (size_t i = 0; i < holdData.size(); i++) {
        int areaX = 130 + i * (40 * 3 + 80);
        int areaY = 895;
        int areaW = 40 * 3;
        int areaH = 40 * 3;

        if (clickPos.x >= areaX && clickPos.x < areaX + areaW &&
            clickPos.y >= areaY && clickPos.y < areaY + areaH)
        {
            selectedIndex = i; // 選択したエリアを記録
            break;
        }
    }
}
// 描画処理
void HoldArea::Draw()
{
    // 最大保存エリア数を取得（最大5つまで保存）
    const int maxSavedAreas = 5;

    for (int i = 0; i < maxSavedAreas; i++)
    {
        // 保存されたエリア情報を取得
        Hold::Area area = hold->GetSavedArea(i);  // インデックスiのエリアを取得

        // 3x3マス以内の範囲で描画
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                // 範囲内のブロックのみ描画
                if (area.startX + x <= area.endX && area.startY + y <= area.endY)
                {
                    int blockType = world->GetGridData(area.startX + x, area.startY + y);  // エリアのブロック情報を取得

                    if (blockType != NULLBLOCK)
                    {
                        // 描画位置を設定
                        holdBlocks[i][x][y].SetPos
                        (
                            130 + i * (40 * 3 + 80) + x * 40,
                            895 + y * 40,
                            0.0f
                        );
                        holdBlocks[i][x][y].Draw();  // ブロックを描画
                    }
                }
            }
        }
    }
}

