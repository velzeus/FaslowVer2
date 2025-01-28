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
        // ���݂̃V�[�������݂��Ă���ꍇ
        if (currentScene != nullptr) {
            currentScene->End();  // ���݂̃V�[�����I��

            // sceneFactories�Ɍ��݂̃V�[�����i�[
            SCENENAME currentSceneName = currentScene->GetSceneName();  // ���݂̃V�[�������擾
            sceneFactories[currentSceneName] = std::move(currentScene);  // ���݂̃V�[�����i�[
        }

        currentScene = std::move(nextScene);  // nextScene�̏��L����currentScene�Ɉړ�
        nextScene = nullptr;  // ���̃V�[���̓N���A

        SCENENAME currentSceneName = currentScene->GetSceneName();  // �V�����V�[�������擾
        sceneFactories[currentSceneName] = std::move(currentScene);  // ���݂̃V�[�����i�[

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

HRESULT SceneManager::Initialize(HWND hWnd)
{
    srand((unsigned)time(NULL));
    D3D_Create(hWnd);                //DirectX��������

    return S_OK;
}
