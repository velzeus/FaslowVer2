#pragma once
#include "SceneFolder/Scene.h"

//âÊñ Ç…ï\é¶Ç∑ÇÈÇ‡ÇÃÇÃèÛë‘
enum DRAWSTATE
{
    WOELDSELECTSCENE = 0,
    STAGESELECTSCENE,
    SETSTAGE,
};

class SelectScene :
    public Scene
{
public:
    SelectScene();
    ~SelectScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

private:
    SceneManager* manager;

    WORLDNUMBER worldNum;
    STAGENUMBER stageNum;

    DRAWSTATE stateNum;

};

