/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		敵キャラの発生制御[enemy_spawner.cpp]					┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.2				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "enemy_spawner.h"
#include <DirectXMath.h>
using namespace DirectX;


static constexpr unsigned int NEMY_SPAWNER_MAX = 100;


struct EnemySpawn
{
	XMFLOAT2 position;				// エネミーの発生場所
	ENEMY_TYPE_ID id;				// エネミーの種類を管理するID
	int count;						// 生成させられるエネミーの最大数

	double time;					// スポナーを発生させる時間
	double rate;					// 生成間隔
	double spawnTime;				// 生成を行った時間
	int spawnCount;					// 生成したエネミーの数
	bool isEnded;					// 生成数が最大になったか
};


static EnemySpawn g_EnemySpawners[NEMY_SPAWNER_MAX]{};
static int g_SpawnerCount{};
static double g_Time{};


void EnemySpawnerInitialize()
{
	g_SpawnerCount = 0;
	g_Time = 0;
}

void EnemySpawnerFinalize()
{
}

void EnemySpawnerUpdate(double elapsed_time)
{
	g_Time += elapsed_time;

	for (int i = 0; i < g_SpawnerCount; i++)
	{
		// 使い終わったスポナーはスルー
		if (g_EnemySpawners[i].isEnded) continue;
		// 使用時間に達していないスポナーにたどり着いたらbreakで抜ける（それ以降を観察しても使用時間に達しているものはないから）
		if (g_EnemySpawners[i].time > g_Time) break;
		// 一回目の生成時だけの処理
		if (g_EnemySpawners[i].count == 0)
		{
			g_EnemySpawners[i].spawnTime = g_Time - g_EnemySpawners[i].rate - 0.00001;
		}
		// 前回の生成時間から生成間隔分経っていたら
		if (g_EnemySpawners[i].rate <= g_Time - g_EnemySpawners[i].spawnTime)
		{
			CreateEnemy(g_EnemySpawners[i].id, g_EnemySpawners[i].position);
			// 生成した体数を増やす
			g_EnemySpawners[i].spawnCount++;
			// 生成できる最大数を超えたら終了フラグをおこす
			if (g_EnemySpawners[i].spawnCount >= g_EnemySpawners[i].count)
			{
				g_EnemySpawners[i].isEnded = true;
			}
			// 生成した時間を保存
			g_EnemySpawners[i].spawnTime = g_Time;
		}
	}
}

void EnemySpawnerDraw()
{
}

void CreateEnemySpawner(const DirectX::XMFLOAT2& position, ENEMY_TYPE_ID id, double spawn_time, double spawn_rate, int spawn_count)
{
	if (g_SpawnerCount >= NEMY_SPAWNER_MAX)return;

	EnemySpawn* pEneSpa = &g_EnemySpawners[g_SpawnerCount];
	pEneSpa->position = position;
	pEneSpa->id = id;
	pEneSpa->time = spawn_time;
	pEneSpa->rate = spawn_rate;
	pEneSpa->count = spawn_count;
	pEneSpa->spawnCount = 0;
	pEneSpa->spawnTime = 0.0;
	pEneSpa->isEnded = false;
	g_SpawnerCount++;
}
