#pragma once
#include "../Actor/ActorBase.h"

class SkyDome : public ActorBase
{
public:

	SkyDome(void);

	~SkyDome(void)override = default;

	void Update(void)override;

	void Draw(void)override;

	void SetPos(const VECTOR& _pos) { transform_.pos = _pos; };
	

protected:

	// リソースロード
	void InitLoad(void)override;

	// 大きさ、回転、座標の初期化
	void InitTransform(void)override;

	// 衝突判定の初期化
	void InitCollider(void)override;

	// アニメーションの初期化
	void InitAnimation(void)override;

	// 初期化後の個別処理
	void InitPost(void)override;

private:

	static constexpr float SCALE = 100.0f;

	static constexpr float ROT_SPEED = 0.005f;
};