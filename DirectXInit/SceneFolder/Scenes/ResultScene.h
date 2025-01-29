#pragma once
#include "../Scene.h"
class ResultScene :
    public Scene
{
public:
    ResultScene();
    ~ResultScene();

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;


private:
    
    MouseInput* mouseInput;
    Input* input;
    Object resultImage;
    
};

