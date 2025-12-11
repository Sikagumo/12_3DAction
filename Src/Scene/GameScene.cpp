#include "GameScene.h"
#include <DxLib.h>
#include "../Manager/SceneManager.h"
#include "../Manager/InputManager.h"
#include "../Object/Actor/ActorBase.h"
#include "../Object/Stage/Stage.h"
#include "../Object/SkyDome/SkyDome.h"
#include "../Object/Player/Player.h"
#include "../Object/Enemy/EnemyManager.h"
#include "../Object/Collider/ColliderBase.h"
#include "../Manager/Camera.h"


GameScene::GameScene(void)
	: stage_(nullptr),
	  skyDome_(nullptr),
	  player_(nullptr),
	  enemies_(nullptr),
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

	player_ = new Player();
	player_->Init();

	enemies_ = new EnemyManager();
	enemies_->Init();

	skyDome_ = new SkyDome(player_->GetTransform());
	skyDome_->Init();

	Camera* camera = sceneMng_.GetCamera();
	camera->SetFollow(&player_->GetTransform());
	camera->Init();

	// ステージモデルのコライダーをプレイヤーに登録
	const ColliderBase* stageCollider = stage_->GetOwnCollider(static_cast<int>(Stage::COLLIDER_TYPE::MODEL));
	player_->AddHitCollider(stageCollider);
	camera->AddHitCollider(stageCollider);
	enemies_->AddHitCollider(stageCollider);
}

void GameScene::Update(void)
{

	// シーン遷移
	InputManager& input = InputManager::GetInstance();
	if (input.KeyIsTrgDown(KEY_INPUT_RETURN))
	{
		sceneMng_.ChangeScene(SceneManager::SCENE_ID::TITLE);
	}


	skyDome_->Update();

	player_->Update();

	enemies_->Update();

	Camera* camera = sceneMng_.GetCamera();
	camera->SetFollow(&player_->GetTransform());
	camera->Update();
}

void GameScene::Draw(void)
{
	skyDome_->Draw();

	stage_->Draw();

	player_->Draw();

	enemies_->Draw();
}

void GameScene::Release(void)
{
	skyDome_->Release();
	delete skyDome_;

	stage_->Release();
	delete stage_;

	enemies_->Release();
	delete enemies_;

	player_->Release();
	delete player_;
}
