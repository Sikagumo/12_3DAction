#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Stage/Stage.h"
#include "../Object/SkyDome/SkyDome.h"
#include "../Object/Player/Player.h"


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

	player_ = new Player();
	player_->Init();
}

void GameScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	InputManager& input = InputManager::GetInstance();
	if (input.KeyIsTrgDown(KEY_INPUT_SPACE))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}


	skyDome_->Update();

	player_->Update();
}

void GameScene::Draw(void)
{
	skyDome_->Draw();

	stage_->Draw();

	player_->Draw();
}

void GameScene::Release(void)
{
	skyDome_->Release();
	delete skyDome_;

	stage_->Release();
	delete stage_;

	player_->Release();
	delete player_;
}
