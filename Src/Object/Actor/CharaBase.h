#pragma once
#include "./ActorBase.h"
class AnimationController;

class CharaBase : public ActorBase
{
public:

	enum class ANIM_TYPE
	{
		IDLE,
		RUN,
		FAST_RUN,
		MAX,

	};
	// コンストラクタ
	CharaBase(void);

	// デストラクタ
	virtual ~CharaBase(void) override = default;

	virtual void Update(void)override;

	void Release(void)override;

protected:

	AnimationController* anim_;

	virtual void InitAnimation(void)override;

	void PlayAnim(ANIM_TYPE type, bool _isLoop = true);
};