#include "Stage.h"
#include "../Actor/ActorBase.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"


Stage::Stage(void)
{
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	ActorBase::Draw();
}

void Stage::InitLoad(void)
{
	transform_.SetModel(resMng_.GetHandleId(ResourceManager::SRC::MODEL_STAGE_MAIN));
}

void Stage::InitTransform(void)
{
	transform_.InitTransform(1.0f,
							 Quaternion::Identity(), Quaternion::Identity(),
							 { 0.0f, -100.0f, 0.0f });
}

void Stage::InitCollider(void)
{
}

void Stage::InitAnimation(void)
{
}

void Stage::InitPost(void)
{
}
