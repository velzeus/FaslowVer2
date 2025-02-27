#pragma once
#include "Word1_Stage.h" 
#include "HoldArea.h"
#include"Hold.h"
#include <iostream>
#include"MouseInput.h"

class Reposition {
public:
    Reposition(Hold* holdInstance, World1_Stage* worldInstance);
    void PlaceArea(int holdIndex, int targetX, int targetY);  // �ۑ��G���A��z�u

private:
    Hold* hold;
    World1_Stage* world;
    int selectedIndex = -1;
};


                                        
