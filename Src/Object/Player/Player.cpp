#include "Player.h"
#include "../../Manager/ResourceManager.h"
#include "../../Utility/AsoUtility.h"
#include "../Common/AnimationController.h"


Player::Player(void)
{
}

void Player::Update(void)
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
	anim_->AddExternal(
}

void Player::InitPost(void)
{
}
