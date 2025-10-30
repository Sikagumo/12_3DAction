#include "TitleScene.h"
#include <DxLib.h>
#include "../Utility/AsoUtility.h"
#include "../Manager/InputManager.h"
#include "../Manager/SceneManager.h"
#include "../Manager/Camera.h"
#include "../Manager/ResourceManager.h"

TitleScene::TitleScene(void)
	:
	SceneBase(),
	imgTitle_(-1),
	imgPushSpace_(-1)
{
}

TitleScene::~TitleScene(void)
{
}

void TitleScene::Init(void)
{
	// タイトル画像
	imgTitle_ = resMng_.GetHandleId(ResourceManager::SRC::IMG_TITLE);

	imgPushSpace_ = resMng_.GetHandleId(ResourceManager::SRC::IMG_PUSH_SPACE);

	// 定点カメラ
	sceMng_.GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);

}

void TitleScene::Update(void)
{

	// シーン遷移
	auto const& ins = InputManager::GetInstance();
	if (ins.IsTrgDown(KEY_INPUT_SPACE))
	{
		sceMng_.ChangeScene(SceneManager::SCENE_ID::GAME);
	}

}

void TitleScene::Draw(void)
{
	DrawGraph(IMG_TITLE_X, IMG_TITLE_Y, imgTitle_, true);
	DrawGraph(IMG_PUSH_X, IMG_PUSH_Y, imgPushSpace_, true);
}

void TitleScene::Release(void)
{
}
