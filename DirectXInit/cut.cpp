#include "CUT.h"

CUT::CUT(StageScene* stagesceneInstance)
{
    stagescene = stagesceneInstance; // インスタンスを保持
}

// マウス選択エリアを基にグリッドデータを更新
void CUT::UpdateSelection(const POINT& clickPosition, const POINT& releasePosition)
{
    
    // クリックされた位置から離された位置をもとに、選択範囲の左上と右下のマスを決定
    int startX = std::min<int>(clickPosition.x, releasePosition.x);
    int startY = std::min<int>(clickPosition.y, releasePosition.y);
    int endX = std::max<int>(clickPosition.x, releasePosition.x);
    int endY = std::max<int>(clickPosition.y, releasePosition.y);

    // 40pxのマスサイズで範囲をマス単位に変換
    startX = (startX - 130) / BLOCKSIZE_X;
    startY = (startY - 130) / BLOCKSIZE_Y;
    endX = (endX - 130) / BLOCKSIZE_X;
    endY = (endY - 130) / BLOCKSIZE_Y;

    // 3x3マス以内の範囲に制限
    endX = std::min<int>(endX, startX + 2);
    endY = std::min<int>(endY, startY + 2);

    // 選択されたエリアをNULLBLOCKに置き換え
    ClearSelectedArea(startX, startY, endX, endY);

    // 選択範囲をHoldに保存
    //hold.SaveArea(startX, startY, endX, endY);
}

// 選択範囲のマスを更新する
//void CUT::ClearSelectedArea(int startX, int startY, int endX, int endY)
//{
//    for (int x = startX; x <= endX; ++x)
//    {
//        for (int y = startY; y <= endY; ++y)
//        {
//            // STICKY_BLOCK や SLIP_BLOCK を NULLBLOCK に置き換える
//            int currentGridData = world->GetGridData(x, y); // GetGridData を使用して取得
//            if (currentGridData == STICKY_BLOCK || currentGridData == SLIP_BLOCK)
//            {
//                world->SetGridData(x, y, NULLBLOCK);  // SetGridData を使用して更新
//            }
//        }
//    }
//}
void CUT::ClearSelectedArea(int startX, int startY, int endX, int endY)
{
    // 全体のグリッドデータを取得
    std::vector<std::vector<int>> gridStateList = stagescene->GetGridStateList();

    // 選択範囲内の STICKY_BLOCK や SLIP_BLOCK を NULLBLOCK に置き換え
    for (int x = startX; x <= endX; ++x)
    {
        for (int y = startY; y <= endY; ++y)
        {
            if (gridStateList[y][x] == STICKY_BLOCK || gridStateList[y][x] == SLIP_BLOCK)
            {
                gridStateList[y][x] = NULLBLOCK;
            }
        }
    }

    // 更新したデータを SetGridStateList で適用
    stagescene->SetGridStateList(gridStateList);
}

void CUT::Update()
{
    MouseInput* mouse = MouseInput::GetInstance();

    // 左クリックが離されたら選択範囲を処理
    if (!mouse->IsLeftButtonDown())
    {
        POINT clickPos = mouse->GetClickPosition();
        POINT releasePos = mouse->GetReleasePosition();

        // 範囲をクリアする処理
        UpdateSelection(clickPos, releasePos);
    }
}


