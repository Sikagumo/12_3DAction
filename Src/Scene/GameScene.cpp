#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Stage/Stage.h"
#include "../Object/SkyDome/SkyDome.h"

GameScene::GameScene(void)
	:
	SceneBase()
{
}

GameScene::~GameScene(void)
{
}

void GameScene::Init(void)
{
	stage_ = new Stage();
	stage_->Init();

	skyDome_ = new SkyDome();
	skyDome_->Init();
}

void GameScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}

	skyDome_->Update();
}

void GameScene::Draw(void)
{
	skyDome_->Draw();

	stage_->Draw();
}

void GameScene::Release(void)
{
	skyDome_->Release();
	delete skyDome_;

	stage_->Release();
	delete stage_;
}
