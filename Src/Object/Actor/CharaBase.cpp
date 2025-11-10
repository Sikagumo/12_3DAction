#include "CharaBase.h"
#include "../Common/AnimationController.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../../Application.h"


CharaBase::CharaBase(void)
{
}


void CharaBase::InitAnimation(void)
{
	if (transform_.modelId != -1)
	{
		anim_ = new AnimationController(transform_.modelId);
	}
}

void CharaBase::Update(void)
{
	// 各キャラクターごとの更新処理
	UpdateProcess();

	// 移動方向に応じた遅延回転
	DelayRotate();

	// 重力による移動量
	//CalcGravityPow();

	// モデル制御更新
	transform_.Update();

	// アニメーション再生
	if (anim_)
	{
		anim_->Update();
	}

	// 各キャラクターごとの更新後処理
	UpdateProcessPost();
}

void CharaBase::Release(void)
{
	if (anim_)
	{
		anim_->Release();
		delete anim_;
	}
}

void CharaBase::PlayAnim(CharaBase::ANIM_TYPE _type, bool _isLoop)
{
	int type = static_cast<int>(_type);

	// 指定したアニメーションが割り当てられているとき、処理終了
	if (type == anim_->GetPlayType()) { return; }

	anim_->Play(type, _isLoop);
}

void CharaBase::CalcGravityPow(void)
{
	// 重力方向
	VECTOR dirGravity = AsoUtility::DIR_DOWN;

	// 重力の強さ
	float gravityPow = Application::GetInstance().GetGravityPow() * sceneMng_.GetDeltaTime();

	// 重力
	VECTOR gravity = VScale(dirGravity, gravityPow);
	jumpPow_ = VAdd(jumpPow_, gravity);

	// ジャンプ量を加算
	transform_.pos = VAdd(transform_.pos, jumpPow_);
}

void CharaBase::DelayRotate(void)
{
	// 移動方向から回転に変換する
	Quaternion goalRot = Quaternion::LookRotation(moveDir_);
	// 回転の補間
	transform_.quaRot =
		Quaternion::Slerp(transform_.quaRot, goalRot, 0.2f);
}
