#include "Player.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../../Utility/MatrixUtility.h"
#include "../Common/AnimationController.h"
#include "../../Manager/InputManager.h"
#include "../../Manager/SceneManager.h"
#include "../../Manager/Camera.h"
#include "../Collider/ColliderLine.h"


Player::Player(void)
	:movePow_(AsoUtility::VECTOR_ZERO)
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
	// 主に地面との衝突で仕様する線分コライダ
	ColliderLine* colLine = new ColliderLine(ColliderBase::TAG::PLAYER, &transform_,
											 COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);

	// 当たり判定リストに格納
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::LINE), colLine);
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

void Player::UpdateProcess(void)
{
}

void Player::UpdateProcessPost(void)
{
	// 移動操作
	ProcessMove();

	// 移動処理
	transform_.pos = VAdd(transform_.pos, movePow_);
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

		// カメラの方向で進行
		VECTOR cameraAngle = SceneManager::GetInstance().GetCamera()->GetAngles();
		cameraAngle.y = AsoUtility::Deg2RadF(cameraAngle.y);
		MATRIX cameraMat = MatrixUtility::GetMatrixRotateXYZ(cameraAngle);

		// 移動方向を取得
		moveDir_ = VTransform(dir, cameraMat);


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

		// 加速度に割り当て
		movePow_ = VScale(moveDir_, speed);
	}
	else
	{
		movePow_ = AsoUtility::VECTOR_ZERO;

		PlayAnim(ANIM_TYPE::IDLE);
	}
}