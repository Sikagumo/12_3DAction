#include "Player.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Common/AnimationController.h"
#include "../../Manager/InputManager.h"


Player::Player(void)
{
}

void Player::InitLoad(void)
{
	transform_.SetModel(resMng_.LoadModelDuplicate(ResourceManager::SRC::MODEL_PLAYER));
}

void Player::InitTransform(void)
{
	transform_.InitTransform(1.0f,
							 Quaternion::Identity(), Quaternion::AngleAxis(180.0f, AsoUtility::AXIS_Y),
							 AsoUtility::VECTOR_ZERO);
}

void Player::InitCollider(void)
{
}

void Player::InitAnimation(void)
{
	CharaBase::InitAnimation();
	anim_->AddExternal(static_cast<int>(ANIM_TYPE::IDLE), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_IDLE));
	anim_->AddExternal(static_cast<int>(ANIM_TYPE::RUN), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_RUN));
	anim_->AddExternal(static_cast<int>(ANIM_TYPE::FAST_RUN), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_RUN_FAST));

	PlayAnim(ANIM_TYPE::IDLE);
}

void Player::InitPost(void)
{
}

void Player::Update(void)
{
	CharaBase::Update();

	// 移動操作
	ProcessMove();

	// 移動処理
	transform_.pos = VAdd(transform_.pos, movePow_);

	// 3Dの基礎情報更新
	transform_.Update();
}

void Player::ProcessMove(void)
{
	InputManager& input = InputManager::GetInstance();

	VECTOR dir = AsoUtility::VECTOR_ZERO;
	float speed = SPEED_MOVE;

	if (GetJoypadNum() > 0)
	{
		dir = input.GetAlgKeyDirXZ(InputManager::PAD_NO::PAD1, InputManager::JOYPAD_ALGKEY::LEFT);
	}
	else
	{
		if (input.KeyIsNew(KEY_INPUT_W)) { dir.z += 1.0f; }
		if (input.KeyIsNew(KEY_INPUT_S)) { dir.z += -1.0f; }
		if (input.KeyIsNew(KEY_INPUT_A)) { dir.x += -1.0f; }
		if (input.KeyIsNew(KEY_INPUT_D)) { dir.x += 1.0f; }
	}

	if (!AsoUtility::EqualsVZero(dir))
	{
		movePow_ = AsoUtility::VECTOR_ZERO;

		// ダッシュ処理
		if (input.KeyIsNew(KEY_INPUT_LSHIFT) && GetJoypadNum() <= 0 ||
			input.PadIsBtnNew(1,static_cast<int>(InputManager::PAD_BTN::R_TRIGGER)) && GetJoypadNum() > 0)
		{
			speed = SPEED_DASH;
			PlayAnim(ANIM_TYPE::FAST_RUN);
		}
		else
		{
			PlayAnim(ANIM_TYPE::RUN);
		}

		dir = VNorm(dir);

		// 加速度に割り当て
		movePow_ = VScale(dir, speed);
	}
	else
	{
		movePow_ = AsoUtility::VECTOR_ZERO;

		PlayAnim(ANIM_TYPE::IDLE);
	}
}