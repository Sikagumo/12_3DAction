#pragma once
#include "../Actor/CharaBase.h"

class EnemyBase : public CharaBase
{
public:

	// 種別
	enum class TYPE
	{
		RAT,
	};

	// エネミーデータ
	struct EnemyData
	{
		int id;
		EnemyBase::TYPE type;
		int hp;
		VECTOR defaultPos;
	};

	// コンストラクタ
	EnemyBase(const EnemyBase::EnemyData& data);

	// デストラクタ
	virtual ~EnemyBase(void) override = default;

protected:

	// 種別
	TYPE type_;
	// HP
	int hp_;


	// 大きさ、回転、座標の初期化
	void InitTransform(void) override {}

	// 衝突判定の初期化
	void InitCollider(void) override {}

	// 初期化後の個別処理
	void InitPost(void) override {}
};