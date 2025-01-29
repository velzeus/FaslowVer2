#pragma once
#include<fstream>
#include"json.hpp"
#include"SceneFolder/Scene.h"
#include"../../Object.h"

//���W���擾���邽�߂̍\����
struct VECTOR2
{
    float x, y;
};

class ClassA :
    public Scene
{
public:
    ClassA();
    ~ClassA() override;

    int Start() override;
    int Update() override;
    int Draw() override;
    int End() override;

    //json�t�@�C����ǂݍ��ށi������Stage�ԍ��������Ă���j
    void ReadFile();


private:
    SceneManager* manager;

    std::vector<std::vector<int>> read_gridStateList;//�}�X�ڂ̏�Ԃ�ۑ�����

    std::vector<std::vector<VECTOR2>> read_blockPositionList;//�u���b�N�̍��W��ۑ�����


};

