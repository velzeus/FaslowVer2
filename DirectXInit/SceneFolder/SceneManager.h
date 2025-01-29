#pragma once
#include "Scene.h"
#include <vector>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <functional>
#include<iostream>

// �O���錾
class Scene;


enum SCENENAME
{
    TITLE = 0,
    SELECT,
    STAGE,
    RESULT,
    OPTION,
    SCENENAME_MAX,
};

//�X�e�[�W�ԍ�
enum WORLDNUMBER
{
    
    WORLD1 = 1,
    WORLD2,
    WORLD3,
    WORLD4,
    WORLD5,
    WORLD6,
};

//�X�e�[�W�ԍ�
enum STAGENUMBER
{
    
    STAGE1 = 1,
    STAGE2,
    STAGE3,
    STAGE4,
    STAGE5,
    STAGEINIT,
};


class SceneManager {
private:
    static bool endFlg;  // �I���t���O

    static SceneManager* instance; // �V���O���g���C���X�^���X

    // Scene��
    std::unique_ptr<Scene> currentScene; // ���݂̃V�[��
    std::unique_ptr<Scene> nextScene; // ���̃V�[��
    std::unordered_map<SCENENAME, std::unique_ptr<Scene>> sceneFactories; // �V�[���������W�b�N

    WORLDNUMBER worldNumber;//���[���h�ԍ���ۑ�����

    STAGENUMBER stageNumber;//�X�e�[�W�ԍ���ۑ�����


    SceneManager(); // �R���X�g���N�^

public:
    static SceneManager* GetInstance(); // �V���O���g���C���X�^���X���擾
    ~SceneManager(); // �f�X�g���N�^

    void AddScene(SCENENAME _sceneName, std::unique_ptr<Scene> _scene);
    void ChangeScene(SCENENAME _sceneName);
    int Update();
    int Draw();

    // �G���[�p
    std::string SceneNameToString( SCENENAME _sceneName);

    //���[���h�ԍ��ƃX�e�[�W�ԍ��̃Z�b�^�[�E�Q�b�^�[�֐�
    void SetWorldNumber(WORLDNUMBER _worldNum);
    void SetStageNumber(STAGENUMBER _stageNum);

    WORLDNUMBER GetWorldNumber();
    STAGENUMBER GetStageNumber();


};