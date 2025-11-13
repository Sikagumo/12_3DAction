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

	// コンストラクタ
	CharaBase(void);

	// デストラクタ
	virtual ~CharaBase(void) override = default;

	void Update(void)override final;

	void Release(void)override;

protected:

	// 最大落下速度
	static constexpr float MAX_FALL_SPEED = -30.0f;


	AnimationController* animation_;

	VECTOR moveDir_;

	VECTOR movePow_;

	VECTOR jumpPow_;

	// 移動前の座標
	VECTOR prevPos_;

	// ジャンプ判定
	bool isJump_;

	

	virtual void InitAnimation(void)override;

	virtual void UpdateProcess(void) = 0;
	virtual void UpdateProcessPost(void) = 0;

	// 移動方向に応じた遅延回転
	void DelayRotate(void);

	void CalcGravityPow(void);

	// 衝突判定
	void Collision(void);
	void CollisionGravity(void);
};