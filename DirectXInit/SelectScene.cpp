#include "SelectScene.h"
#include"StageScene.h"

SelectScene::SelectScene() :
	Scene(SCENENAME::SELECT), manager(SceneManager::GetInstance())
{
	stateNum = WOELDSELECTSCENE;
	
}

SelectScene::~SelectScene()
{
}

int SelectScene::Start()
{
	return 0;
}

int SelectScene::Update()
{
	switch (stateNum)
	{
	case WOELDSELECTSCENE:
		
		worldNum = WORLD1;
		stateNum = STAGESELECTSCENE;
		
		break;
	case STAGESELECTSCENE:
		
		stageNum = STAGE1;
		stateNum = SETSTAGE;
		
		break;
	case SETSTAGE:

		//ワールド番号とステージ番号をセット
		manager->SetWorldNumber(worldNum);
		manager->SetStageNumber(stageNum);

		manager->AddScene(SCENENAME::STAGE, std::make_unique<StageScene>());
		manager->ChangeScene(STAGE);

		break;
	}


	return 0;
}

int SelectScene::Draw()
{
	return 0;
}

int SelectScene::End()
{
	return 0;
}
