#include "SceneManager.h"
#include <iostream>
#include<Windows.h>



using namespace std;

// �ÓI�����o�ϐ��̏�����
SceneManager* SceneManager::instance = nullptr;
bool SceneManager::endFlg = false;

// �R���X�g���N�^
SceneManager::SceneManager()
    : currentScene(nullptr), nextScene(nullptr)//, mouseInput(nullptr)
{
    // ���ʂȏ������͕s�v

     //mouseInput = MouseInput::GetInstance();

     //g_inputSystem = TS::TS_InputSystem::GetInstance();
     inputSystem=TS::TS_InputSystem::GetInstance();

     inputSystem->Init();
}

// �f�X�g���N�^
SceneManager::~SceneManager() = default;  // unique_ptr�������I�Ƀ��\�[�X�����

// �C���X�^���X���擾�i�V���O���g���p�^�[���j
SceneManager* SceneManager::GetInstance()
{
    static SceneManager inst;
    return &inst;

}

// �X�V����
int SceneManager::Update()
{
    //mouseInput->Update();

    inputSystem->Update();

    if (endFlg == true) {
        return 1;
    }

    if (nextScene != nullptr)  // ���̃V�[���ɐ؂�ւ���ꍇ
    {
        cout << "Update: currentScene = "
            << (currentScene ? "valid" : "nullptr")
            << ", nextScene = "
            << (nextScene ? "valid" : "nullptr") << endl;

        // ���݂̃V�[�������݂��Ă���ꍇ
        if (currentScene != nullptr) {
            currentScene->End();  // ���݂̃V�[�����I��

            // sceneFactories�Ɍ��݂̃V�[�����i�[
            SCENENAME currentSceneName = currentScene->GetSceneName();  // ���݂̃V�[�������擾
            sceneFactories[currentSceneName] = std::move(currentScene);  // ���݂̃V�[�����i�[
        }


        currentScene = std::move(nextScene);  // nextScene�̏��L���� currentScene�Ɉړ�
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

// �V�[����ǉ�
void SceneManager::AddScene(SCENENAME sceneName, std::unique_ptr<Scene> _scene)
{
    if (_scene == nullptr) {
        cerr << "Cannot add a null scene!" << endl;
        cout << "Cannot add a null scene!" << SceneNameToString(_scene.get()->GetSceneName()) << endl;
        return;
    }

    if (sceneFactories.find(sceneName) != sceneFactories.end()) {
        cerr << "Scene " << sceneName << " is already registered!" << endl;
        cout << "Scene " << sceneName << " is already registered!" << endl;
        return;
    }
    sceneFactories[sceneName] = std::move(_scene);
}

// �V�[����؂�ւ���
void SceneManager::ChangeScene(SCENENAME sceneName)
{
    if (sceneName == SCENENAME::END) {
        return;
    }
    auto it = sceneFactories.find(sceneName);
    if (it != sceneFactories.end()) {

        if (!it->second) {
            cout << "scene��nullptr�ł�" << sceneName << endl;
            return;
        }
        else
            cout << "scene������ɍ쓮���Ă܂�(" 
            << SceneNameToString(sceneFactories[sceneName]->GetSceneName()) 
            << ")" << endl;

        nextScene = std::move(it->second);

        // �G���[�������L�q���Ă�������

    }
    else {
        cerr << "Scene with name " << SceneNameToString(sceneName) << " not found!" << endl;
    }
}

HRESULT SceneManager::Initialize(HWND hWnd)
{
    srand((unsigned)time(NULL));
    D3D_Create(hWnd);                //DirectX��������

    return S_OK;
}
