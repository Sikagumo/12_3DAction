#include "EnemyManager.h"
#include "./EnemyBase.h"
#include "./EnemyRat.h"
#include "../Common/Transform.h"

EnemyManager::EnemyManager(void)
{
}

void EnemyManager::Init(void)
{
	// “G¶¬
	CreateEnemy({});
}

void EnemyManager::Update(void)
{
	if (enemies_.empty()) { return; }
	for (auto& enemy : enemies_)
	{
		enemy->Update();
	}
}

void EnemyManager::Draw(void)
{
	if (enemies_.empty()) { return; }
	for (auto& enemy : enemies_)
	{
		enemy->Draw();
	}
}

void EnemyManager::Release(void)
{
	if (enemies_.empty()) { return; }
	for (auto& enemy : enemies_)
	{
		enemy->Release();
		delete enemy;
	}
}


void EnemyManager::AddHitCollider(const ColliderBase* hitCollider)
{
	if (enemies_.empty()) { return; }
	for (auto& enemy : enemies_)
	{
		enemy->AddHitCollider(hitCollider);
	}
}

void EnemyManager::CreateEnemy(const Transform& _transform)
{
	EnemyBase* enemy;
	enemy = new EnemyRat({});

	enemy->Init();
	enemies_.emplace_back(enemy);
}
