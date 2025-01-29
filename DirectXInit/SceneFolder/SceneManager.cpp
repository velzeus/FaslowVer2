#include "SceneManager.h"
#include "../input.h"
#include "../Sound.h"
#include "../Object.h"
#include <iostream>

using namespace std;

// �ÓI�����o�ϐ��̏�����
SceneManager* SceneManager::instance = nullptr;
bool SceneManager::endFlg = false;

// �R���X�g���N�^
SceneManager::SceneManager()
    : currentScene(nullptr), nextScene(nullptr)
{
    // ���ʂȏ������͕s�v
}

// �f�X�g���N�^
SceneManager::~SceneManager() = default;  // unique_ptr�������I�Ƀ��\�[�X�����

// �C���X�^���X���擾�i�V���O���g���p�^�[���j
SceneManager* SceneManager::GetInstance()
{
    if (instance==nullptr)
    {
        instance = new SceneManager;  // �C���X�^���X���쐬
    }
    return instance;
}

// �X�V����
int SceneManager::Update()
{
    if (nextScene != nullptr)  // ���̃V�[���ɐ؂�ւ���ꍇ
    {
        if (currentScene != nullptr) {
            currentScene->End();  // ���݂̃V�[�����I��
        }

        currentScene = std::move(nextScene);  // nextScene�̏��L����currentScene�Ɉړ�
        nextScene = nullptr;  // ���̃V�[���̓N���A

        currentScene->Start();  // �V�����V�[���̊J�n����
    }

    if (currentScene != nullptr)
    {
        return currentScene->Update();  // ���݂̃V�[���̍X�V
    }

    return -1;  // �V�[�����Ȃ��ꍇ��-1��Ԃ�
}

// �`�揈��
int SceneManager::Draw()
{
    D3D_StartRender();

    if (currentScene != nullptr)
    {
        currentScene->Draw();  // ���݂̃V�[���̕`��
    }

    D3D_FinishRender();
    return 0;
}

std::string SceneManager::SceneNameToString( SCENENAME _sceneName)
{
    
    switch (_sceneName)
    {
    case TITLE:
        return "Title";
        break;
    case RESULT:
        return "Result";
        break;
    default:
        break;
    }
    return "Error";
}

void SceneManager::SetWorldNumber(WORLDNUMBER _worldNum)
{
    worldNumber = _worldNum;
}

void SceneManager::SetStageNumber(STAGENUMBER _stageNum)
{
    stageNumber = _stageNum;
}

WORLDNUMBER SceneManager::GetWorldNumber()
{
    return worldNumber;
}

STAGENUMBER SceneManager::GetStageNumber()
{
    return stageNumber;
}

//���Őݒ肵���֐�---------------------
void SceneManager::SetHWND(HWND _hWnd)
{
    hwnd = _hWnd;
}

HWND SceneManager::GetHWND()
{
    return hwnd;
}
//-------------------------------------

// �V�[����ǉ�
void SceneManager::AddScene(SCENENAME sceneName, std::unique_ptr<Scene> _scene)
{
    if (_scene == nullptr) {
        cerr << "Cannot add a null scene!" << endl;
        return;
    }

    if (sceneFactories.find(sceneName) != sceneFactories.end()) {
        cerr << "Scene " << sceneName << " is already registered!" << endl;
        return;
    }
    sceneFactories[sceneName] = std::move(_scene);
}

// �V�[����؂�ւ���
void SceneManager::ChangeScene(SCENENAME sceneName)
{
    auto it = sceneFactories.find(sceneName);
    if (it != sceneFactories.end()) {
        nextScene = std::move(it->second);
    }
    else {
        cerr << "Scene with name " << sceneName << " not found!" << endl;
    }
}