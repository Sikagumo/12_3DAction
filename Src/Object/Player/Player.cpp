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
	:CharaBase::CharaBase()
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
	animation_->AddExternal(static_cast<int>(ANIM_TYPE::IDLE), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_IDLE));

	animation_->AddExternal(static_cast<int>(ANIM_TYPE::RUN), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_RUN));

	animation_->AddExternal(static_cast<int>(ANIM_TYPE::FAST_RUN), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_RUN_FAST));

	animation_->AddExternal(static_cast<int>(ANIM_TYPE::JUMP), 30.0f,
					   resMng_.GetHandleId(ResourceManager::SRC::ANIM_PLAYER_JUMPING));

	PlayAnim(ANIM_TYPE::IDLE);
}

void Player::InitPost(void)
{
}

void Player::UpdateProcess(void)
{
	ProcessJump();

	// 移動操作
	ProcessMove();

	// アニメーションごとの線分調整
	if (animation_->GetPlayType() == static_cast<int>(ANIM_TYPE::JUMP))
	{
		// ジャンプ中は線分を伸ばす
		if (ownColliders_.count(static_cast<int>(COLLIDER_TYPE::LINE)) != 0)
		{
			ColliderLine* colLine = dynamic_cast<ColliderLine*>(
				ownColliders_.at(static_cast<int>(COLLIDER_TYPE::LINE)));
			colLine->SetLocalPosStart(COL_LINE_JUMP_START_LOCAL_POS);
			colLine->SetLocalPosEnd(COL_LINE_JUMP_END_LOCAL_POS);
		}
	}
	else
	{
		// 通常時の線分に戻す
		if (ownColliders_.count(static_cast<int>(COLLIDER_TYPE::LINE)) != 0)
		{
			ColliderLine* colLine = dynamic_cast<ColliderLine*>(
				ownColliders_.at(static_cast<int>(COLLIDER_TYPE::LINE)));
			colLine->SetLocalPosStart(COL_LINE_START_LOCAL_POS);
			colLine->SetLocalPosEnd(COL_LINE_END_LOCAL_POS);
		}
	}

}

void Player::UpdateProcessPost(void)
{
	
}

void Player::ProcessMove(void)
{
	InputManager& input = InputManager::GetInstance();

	VECTOR dir = AsoUtility::VECTOR_ZERO;

	// ダッシュ処理
	isDash_ = (input.KeyIsNew(KEY_INPUT_LSHIFT) && GetJoypadNum() <= 0
			   || input.PadIsBtnNew(1, static_cast<int>(InputManager::PAD_BTN::R_TRIGGER))
			      && GetJoypadNum() > 0);


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
		//movePow_ = AsoUtility::VECTOR_ZERO;

		// ダッシュ入力時にダッシュ加速度にする
		moveSpeed_ = ((isDash_) ? SPEED_DASH : SPEED_MOVE);

		if (!isJump_)
		{
			if (isDash_)
			{
				PlayAnim(ANIM_TYPE::FAST_RUN);
			}
			else
			{
				PlayAnim(ANIM_TYPE::RUN);
			}
		}

		// カメラの方向で進行
		Quaternion cameraRot = sceneMng_.GetCamera()->GetQuaRotY();

		// 移動方向を取得
		moveDir_ = Quaternion::PosAxis(cameraRot, dir);

		// 加速度に割り当て
		movePow_ = VScale(moveDir_, moveSpeed_);
	}
	else
	{
		movePow_ = AsoUtility::VECTOR_ZERO;

		if (!isJump_)
		{
			PlayAnim(ANIM_TYPE::IDLE);
		}
	}
}

void Player::ProcessJump(void)
{
	auto& input = InputManager::GetInstance();

	bool isHitKey = input.KeyIsTrgDown(KEY_INPUT_SPACE)
		|| input.PadIsBtnTrgDown(InputManager::PAD_NO::PAD1, 
								 InputManager::PAD_BTN::DOWN);
	// ジャンプ
	if (isHitKey && !isJump_)
	{
		// ジャンプ量の計算
		float jumpSpeed = (POW_JUMP * sceneMng_.GetDeltaTime());
		jumpPow_ = VScale(AsoUtility::DIR_UP, jumpSpeed);

		isJump_ = true;

		// アニメーション再生
		PlayAnim(ANIM_TYPE::JUMP, false);
	}
}

void Player::PlayAnim(Player::ANIM_TYPE _type, bool _isLoop)
{
	int type = static_cast<int>(_type);

	// 指定したアニメーションが割り当てられているとき、処理終了
	if (type == animation_->GetPlayType()) { return; }

	animation_->Play(type, _isLoop);
}