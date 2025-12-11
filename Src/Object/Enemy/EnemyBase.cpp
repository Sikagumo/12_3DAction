#include "EnemyBase.h"
#include "../Actor/CharaBase.h"

EnemyBase::EnemyBase(const EnemyBase::EnemyData& data)
	:
	CharaBase::CharaBase(),
	type_(data.type),
	hp_(data.hp)
{
	// ‰ŠúÀ•W‚Ìİ’è
	transform_.pos = data.defaultPos;
}