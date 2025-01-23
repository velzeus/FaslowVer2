#pragma once
#include "../Scene.h"
#include "../../Object.h"


class TitleScene :
    public Scene
{

public:

    // コンストラクタ/デストラクタ
    TitleScene();
    ~TitleScene() override;


    // 
    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;
    

private:

    Object titleImage;



};

