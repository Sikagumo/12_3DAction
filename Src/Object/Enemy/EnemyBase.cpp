#include "EnemyBase.h"
#include "../Actor/CharaBase.h"
#include "../../Utility/AsoUtility.h"
#include "../Player/Player.h"
#include "../../Manager/SceneManager.h"

EnemyBase::EnemyBase(const EnemyBase::EnemyData& data, Player& _player)
	:
	player_(_player),
	CharaBase::CharaBase(),
	type_(data.type),
	hp_(data.hp),
	defaultPos_(data.defaultPos),
	moveRange_(data.moveRange)
{
	// 初期座標の設定
	transform_.pos = defaultPos_;
}

void EnemyBase::ChangeState(int state)
{
	// 各状態遷移の初期処理
	stateChanges_[state]();
}

void EnemyBase::Draw(void)
{
	CharaBase::Draw();

	if (sceneMng_.GetIsDebugMode())
	{

		// 移動可能範囲のデバッグ描画
		//DrawSphere3D(defaultPos_, moveRange_, 16, 0x000099, 0x000099, false);
	}
}

bool EnemyBase::InMovableRange(void) const
{
	bool ret = false;

	// 初期位置からの距離
	float dis = static_cast<float>(AsoUtility::SqrMagnitude(defaultPos_, transform_.pos));

	// 指定距離判定
	if (dis < (moveRange_ * moveRange_))
	{
		return true;
	}
	return ret;
}

void EnemyBase::Search(void)
{
	VECTOR pPos = player_.GetTransform().pos;

	// 敵の向いている方向
	VECTOR eDir = VNorm(moveDir_);

	// 敵とプレイヤーとの間のベクトル
	VECTOR diff = VSub(pPos, transform_.pos);

	// 敵から見たプレイヤーの方向
	VECTOR dirPlayerFromEnemy = VNorm(diff);


	// 内積を使ってベクトルの比較を行う
	// (+1.0)：２つのベクトルは同じ方向
	// (0.0)：２つのベクトルは直交
	// (-1.0)：２つのベクトルは逆方向
	float dot = VDot(eDir, dirPlayerFromEnemy);
	float angle = acosf(dot);

	const float VIEW_ANGLE = 60.0f;
	const float viewRad = AsoUtility::Deg2RadF(VIEW_ANGLE);

	// プレイヤーとの距離
	VECTOR vec = VSub(pPos, transform_.pos);
	float distance = ((vec.x * vec.x) + (vec.z * vec.z));

	// 視野左右内に入っている
	isNoticeVision_ = (distance <= VIEW_RANGE * VIEW_RANGE && (angle <= viewRad));
}

void EnemyBase::SearchField(void)
{
	// 360°範囲索敵処理
	VECTOR vec = VSub(player_.GetTransform().pos, transform_.pos);

	float diff = ((vec.x * vec.x) + (vec.z * vec.z));

	// 視野左右内に入っている
	isNoticeHearing_ = (diff <= (VIEW_RANGE * VIEW_RANGE));
}