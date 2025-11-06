#include "CharaBase.h"
#include "../Common/AnimationController.h"


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
	if (anim_)
	{
		anim_->Update();
	}
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
