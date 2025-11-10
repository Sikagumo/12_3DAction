#pragma once
#include "../Actor/CharaBase.h"

class Player : public CharaBase
{
public:

	Player(void);

	~Player(void)override = default;

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

	// 更新処理
	void UpdateProcess(void)override;

	// 
	void UpdateProcessPost(void)override;

private:

	// 移動速度(通常)
	static constexpr float SPEED_MOVE = 5.0f;

	// 移動速度(ダッシュ)
	static constexpr float SPEED_DASH = 10.0f;

	// 衝突判定用線分開始
	static constexpr VECTOR COL_LINE_START_LOCAL_POS = { 0.0f, 80.0f, 0.0f };

	// 衝突判定用線分終了
	static constexpr VECTOR COL_LINE_END_LOCAL_POS = { 0.0f, -10.0f, 0.0f };


	VECTOR movePow_;

	// 操作
	void ProcessMove(void);
};