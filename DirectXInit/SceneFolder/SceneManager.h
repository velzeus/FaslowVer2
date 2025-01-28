#pragma once
#include "Scene.h"
#include"../Object.h"
#include"../input.h"
#include"../MouseInput.h"
#include"../Sound.h"
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
    RESULT,
    SCENENAME_MAX,
};


class SceneManager {
private:
    static bool endFlg;  // �I���t���O

    static SceneManager* instance; // �V���O���g���C���X�^���X

    // Scene��
    std::unique_ptr<Scene> currentScene; // ���݂̃V�[��
    std::unique_ptr<Scene> nextScene; // ���̃V�[��
    std::unordered_map<SCENENAME, std::unique_ptr<Scene>> sceneFactories; // �V�[���������W�b�N

    SceneManager(); // �R���X�g���N�^

public:
    static SceneManager* GetInstance(); // �V���O���g���C���X�^���X���擾
    ~SceneManager(); // �f�X�g���N�^

    void AddScene(SCENENAME _sceneName, std::unique_ptr<Scene> _scene);
    void ChangeScene(SCENENAME _sceneName);

    HRESULT Initialize(HWND hWnd);

    int Update();
    int Draw();

    // �G���[�p
    std::string SceneNameToString( SCENENAME _sceneName);
};