#include "ResultScene.h"

ResultScene::ResultScene() 
    :Scene(SCENENAME::RESULT), input(nullptr)//, mouseInput(nullptr)
{
    std::cout << SceneManager::GetInstance()->SceneNameToString(GetSceneName())
        << "コンストラクタ" << std::endl;
    std::cout << "    SceneName(" << sceneName << ")" << std::endl;
}

ResultScene::~ResultScene()
{
}

int ResultScene::Start()
{
    //mouseInput = MouseInput::GetInstance();
    inputSystem = TS::TS_InputSystem::GetInstance();
    
    
    resultImage.Init(L"./asset/UI/Back.png");
    resultImage.SetColor(1, 1, 1, 1);
    resultImage.SetPos(-400, -200, 0);
    resultImage.SetSize(100, 100, 1);

    nextStage.Init(L"asset/block.png");
    nextStage.SetColor(1, 1, 1, 1);
    nextStage.SetPos(400, -200, 0);
    nextStage.SetSize(100, 100, 1);
    return 0;
}

int ResultScene::Update()
{
    if (inputSystem->GetTrigger(MK_LEFT)) {

        //ワールドセレクトに戻る
        if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (resultImage.GetPos().x - resultImage.GetSize().x / 2) &&
            inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (resultImage.GetPos().x + resultImage.GetSize().x / 2))
        {
            //
            if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (resultImage.GetPos().y - resultImage.GetSize().y / 2) &&
                (inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (resultImage.GetPos().y + resultImage.GetSize().y / 2))
            {
                //決定されてない状態に戻す
                SceneManager::GetInstance()->SetWorldNumber(NOTDONE_WORLD);
                SceneManager::GetInstance()->SetStageNumber(NOTDONE_STAGE);

                //ワールドセレクトへ
                SceneManager::GetInstance()->ChangeScene(SELECT);
            }

        }

        //次のステージへ
        if (inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 > (nextStage.GetPos().x - nextStage.GetSize().x / 2) &&
            inputSystem->GetClickPosition().x - SCREEN_WIDTH / 2 < (nextStage.GetPos().x + nextStage.GetSize().x / 2))
        {
            //
            if ((inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 > (nextStage.GetPos().y - nextStage.GetSize().y / 2) &&
                (inputSystem->GetClickPosition().y - SCREEN_HEIGHT / 2) * -1 < (nextStage.GetPos().y + nextStage.GetSize().y / 2))
            {
                //次のワールドとステージを指定
                SceneManager::GetInstance()->SetWorldNumber(SceneManager::GetInstance()->GetWorldNumber());

                STAGENUMBER stageNum = SceneManager::GetInstance()->GetStageNumber();

                switch (stageNum)
                {
                case STAGE1:
                    stageNum = STAGE2;
                    break;
                case STAGE2:
                    stageNum = STAGE3;
                    break;
                case STAGE3:
                    stageNum = STAGE4;
                    break;
                case STAGE4:
                    stageNum = STAGE5;
                    break;
                case STAGE5:
                    stageNum =NOTDONE_STAGE;
                    break;
                }

                SceneManager::GetInstance()->SetStageNumber(stageNum);

                if (stageNum == NOTDONE_STAGE)
                {
                    //ワールドセレクトへ
                    SceneManager::GetInstance()->ChangeScene(SELECT);
                }
                else
                {
                    //次のステージへ
                    SceneManager::GetInstance()->ChangeScene(STAGE);
                }

                
            }

        }

        
    }
    return 0;
}

int ResultScene::Draw()
{
    resultImage.Draw();

    nextStage.Draw();
    return 0;
}

int ResultScene::End()
{
    return 0;
}
