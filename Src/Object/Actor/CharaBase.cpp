#include "CharaBase.h"
#include "../Common/AnimationController.h"

CharaBase::CharaBase(void)
{
}

void CharaBase::Release(void)
{
	if (anim_)
	{
		anim_->Release();
		delete anim_;
	}
}

void CharaBase::InitAnimation(void)
{
	if (transform_.modelId != -1)
	{
		anim_ = new AnimationController(transform_.modelId);
	}
}
