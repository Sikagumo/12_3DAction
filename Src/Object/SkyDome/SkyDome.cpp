#include "SkyDome.h"
#include <Dxlib.h>
#include "../Actor/ActorBase.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"

SkyDome::SkyDome(void)
{
}

void SkyDome::InitLoad(void)
{
	transform_.SetModel(resMng_.GetHandleId(ResourceManager::SRC::MODEL_SKYDOME));
}
void SkyDome::InitTransform(void)
{
	transform_.InitTransform(SCALE,
							 Quaternion::Identity(), Quaternion::AngleAxis(180.0f, AsoUtility::AXIS_Y),
							 AsoUtility::VECTOR_ZERO);
}
void SkyDome::InitCollider(void)
{
}
void SkyDome::InitAnimation(void)
{
}
void SkyDome::InitPost(void)
{
	// Zバッファの使用&書き込み無効(突き抜け対策)
	MV1SetUseZBuffer(transform_.modelId, false);
	MV1SetWriteZBuffer(transform_.modelId, false);
}

void SkyDome::Update(void)
{
	transform_.Rotate(AsoUtility::AXIS_Y, ROT_SPEED);
}

void SkyDome::Draw(void)
{
	// ライト効果を無効化して描画
	SetUseLighting(FALSE);
	ActorBase::Draw();
	SetUseLighting(TRUE);
}