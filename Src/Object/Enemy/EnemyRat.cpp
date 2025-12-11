#include "EnemyRat.h"
#include "./EnemyBase.h"
#include "../Common/Transform.h"
#include "../Common/AnimationController.h"
#include "../../Common/Quaternion.h"
#include "../../Utility/AsoUtility.h"
#include "../../Manager/ResourceManager.h"
#include "../Collider/ColliderLine.h"
#include "../Collider/ColliderCapsule.h"

EnemyRat::EnemyRat(const EnemyBase::EnemyData& data)
:
EnemyBase(data)
{

}


void EnemyRat::InitLoadPost(void)
{
	transform_.modelId = resMng_.LoadModelDuplicate(ResourceManager::SRC::MODEL_RAT);
}

void EnemyRat::InitTransform(void)
{
	transform_.GetScale(0.5f);
	transform_.quaRot = Quaternion::AngleAxis(AsoUtility::Rad2DegF(180.0f), AsoUtility::AXIS_Y);
	transform_.quaRotLocal = Quaternion::Identity();
	transform_.pos = { 0.0f, 100.0f, 1500.0f };
}

void EnemyRat::InitCollider(void)
{
	// 主に地面との衝突で仕様する線分コライダ
	ColliderLine* colLine = new ColliderLine(ColliderBase::TAG::ENEMY, &transform_,
		COL_LINE_START_LOCAL_POS, COL_LINE_END_LOCAL_POS);

	// 主に壁や木などの衝突で仕様するカプセルコライダ
	ColliderCapsule* colCapsule = new ColliderCapsule(ColliderBase::TAG::ENEMY, &transform_,
		COL_CAPSULE_TOP_LOCAL_POS, COL_CAPSULE_DOWN_LOCAL_POS,
		COL_CAPSULE_RADIUS);

	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::CAPSULE), colCapsule);


	// 当たり判定リストに格納
	ownColliders_.emplace(static_cast<int>(COLLIDER_TYPE::LINE), colLine);
}

void EnemyRat::InitAnimationPost(void)
{
	animation_->AddInternal(static_cast<int>(ANIM_TYPE::IDLE));
	animation_->Play(static_cast<int>(ANIM_TYPE::IDLE), true);
}

void EnemyRat::InitPost(void)
{
}


void EnemyRat::UpdateProcess(void)
{
}

void EnemyRat::UpdateProcessPost(void)
{
}
