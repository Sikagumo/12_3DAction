#pragma once
#include "./ActorBase.h"
class AnimationController;

class CharaBase : public ActorBase
{
public:

	// 衝突判定種別
	enum class COLLIDER_TYPE
	{
		LINE,
		MAX,
	};


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

	void Update(void)override final;

	void Release(void)override;

protected:

	AnimationController* anim_;

	VECTOR moveDir_;

	VECTOR jumpPow_;

	virtual void InitAnimation(void)override;

	virtual void UpdateProcess(void) = 0;
	virtual void UpdateProcessPost(void) = 0;

	// 移動方向に応じた遅延回転
	void DelayRotate(void);

	void PlayAnim(ANIM_TYPE type, bool _isLoop = true);

	void CalcGravityPow(void);
};