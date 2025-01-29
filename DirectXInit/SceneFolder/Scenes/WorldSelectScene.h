#pragma once
#include"../Scene.h"
#include"../../Object.h"
class WorldSelectScene :
    public Scene
{
public:
    WorldSelectScene();
    ~WorldSelectScene() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;
    
private:
    SceneManager* manager;
};

