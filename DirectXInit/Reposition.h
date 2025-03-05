#pragma once
#include"SceneFolder/Scenes/StageScene.h"  
#include "HoldArea.h"
#include"Hold.h"
#include <iostream>
#include"MouseInput.h"

class Reposition {
public:
    Reposition(Hold* holdInstance, StageScene* stagesceneInstance);
    void PlaceArea(int holdIndex, int targetX, int targetY);  // �ۑ��G���A��z�u

private:
    Hold* hold;
    StageScene* stagescene;
    int selectedIndex = -1;
};


                                        
