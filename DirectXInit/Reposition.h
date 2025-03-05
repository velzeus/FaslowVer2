#pragma once
#include"SceneFolder/Scenes/StageScene.h"  
#include "HoldArea.h"
#include"Hold.h"
#include <iostream>
#include"MouseInput.h"

class Reposition {
public:
    Reposition(Hold* holdInstance, StageScene* stagesceneInstance);
    void PlaceArea(int holdIndex, int targetX, int targetY);  // 保存エリアを配置

private:
    Hold* hold;
    StageScene* stagescene;
    int selectedIndex = -1;
};


                                        
