#include "CharaBase.h"
#include "../Common/AnimationController.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/SceneManager.h"
#include "../Collider/ColliderBase.h"
#include "../Collider/ColliderLine.h"
#include "../Collider/ColliderModel.h"
#include "../../Application.h"


CharaBase::CharaBase(void) :
	movePow_(AsoUtility::VECTOR_ZERO)
{
}


void CharaBase::InitAnimation(void)
{
	if (transform_.modelId != -1)
	{
		animation_ = new AnimationController(transform_.modelId);
	}
}

void CharaBase::Update(void)
{
	// 移動前座標を更新
	prevPos_ = transform_.pos;

	// 各キャラクターごとの更新処理
	UpdateProcess();

	// 移動方向に応じた遅延回転
	DelayRotate();

	// 重力による移動量
	CalcGravityPow();

	// 衝突判定
	Collision();

	// モデル制御更新
	transform_.Update();

	// アニメーション再生
	animation_->Update();

	// 各キャラクターごとの更新後処理
	UpdateProcessPost();

}

void CharaBase::Release(void)
{
	if (animation_)
	{
		animation_->Release();
		delete animation_;
	}
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

	// 重力制限	
	jumpPow_.y = ((jumpPow_.y < MAX_FALL_SPEED) ? MAX_FALL_SPEED : jumpPow_.y);
}

void CharaBase::Collision(void)
{
	// 移動処理
	transform_.pos = VAdd(transform_.pos, movePow_);

	// ジャンプ量を加算
	transform_.pos = VAdd(transform_.pos, jumpPow_);

	// 衝突(重力)
	CollisionGravity();
}

void CharaBase::CollisionGravity(void)
{
	// 線分コライダ
	int lineType = static_cast<int>(COLLIDER_TYPE::LINE);

	// 線分コライダが無ければ処理を抜ける
	if (ownColliders_.count(lineType) == 0) { return; }

	// 線分コライダ情報
	ColliderLine* colliderLine_ =
		dynamic_cast<ColliderLine*>(ownColliders_.at(lineType));

	if (colliderLine_ == nullptr) { return; }

	// 線分の始点と終点を取得
	VECTOR start = colliderLine_->GetPosStart();
	VECTOR end   = colliderLine_->GetPosEnd();

	// 登録されている衝突物を全てチェック
	for (const auto& hitCol : hitColliders_)
	{
		// ステージ以外は処理を飛ばす
		if (hitCol->GetTag() != ColliderBase::TAG::STAGE) { continue; }

		// 派生クラスへキャスト
		const ColliderModel* colliderModel =
			dynamic_cast<const ColliderModel*>(hitCol);

		if (colliderModel == nullptr) { continue; }

		// ステージモデル(地面)との衝突
		auto hit = MV1CollCheck_Line(
			colliderModel->GetFollow()->modelId, -1, start, end);

		if (hit.HitFlag > 0)
		{
			// 衝突地点から、少し上に移動
			transform_.pos = VAdd(hit.HitPosition,
								  VScale(AsoUtility::DIR_UP, 2.0f));

			// ジャンプリセット
			jumpPow_ = AsoUtility::VECTOR_ZERO;

			// ジャンプ判定
			isJump_ = false;

		}
	}
}

void CharaBase::DelayRotate(void)
{
	// 移動方向から回転に変換する
	Quaternion goalRot = Quaternion::LookRotation(moveDir_);
	// 回転の補間
	transform_.quaRot =
		Quaternion::Slerp(transform_.quaRot, goalRot, 0.2f);
}
