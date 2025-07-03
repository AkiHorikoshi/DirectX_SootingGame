/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�G�L�����̔�������[enemy_spawner.cpp]					��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.2				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#include "enemy_spawner.h"
#include <DirectXMath.h>
using namespace DirectX;


static constexpr unsigned int NEMY_SPAWNER_MAX = 100;


struct EnemySpawn
{
	XMFLOAT2 position;				// �G�l�~�[�̔����ꏊ
	ENEMY_TYPE_ID id;				// �G�l�~�[�̎�ނ��Ǘ�����ID
	int count;						// ������������G�l�~�[�̍ő吔

	double time;					// �X�|�i�[�𔭐������鎞��
	double rate;					// �����Ԋu
	double spawnTime;				// �������s��������
	int spawnCount;					// ���������G�l�~�[�̐�
	bool isEnded;					// ���������ő�ɂȂ�����
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
		// �g���I������X�|�i�[�̓X���[
		if (g_EnemySpawners[i].isEnded) continue;
		// �g�p���ԂɒB���Ă��Ȃ��X�|�i�[�ɂ��ǂ蒅������break�Ŕ�����i����ȍ~���ώ@���Ă��g�p���ԂɒB���Ă�����̂͂Ȃ�����j
		if (g_EnemySpawners[i].time > g_Time) break;
		// ���ڂ̐����������̏���
		if (g_EnemySpawners[i].count == 0)
		{
			g_EnemySpawners[i].spawnTime = g_Time - g_EnemySpawners[i].rate - 0.00001;
		}
		// �O��̐������Ԃ��琶���Ԋu���o���Ă�����
		if (g_EnemySpawners[i].rate <= g_Time - g_EnemySpawners[i].spawnTime)
		{
			CreateEnemy(g_EnemySpawners[i].id, g_EnemySpawners[i].position);
			// ���������̐��𑝂₷
			g_EnemySpawners[i].spawnCount++;
			// �����ł���ő吔�𒴂�����I���t���O��������
			if (g_EnemySpawners[i].spawnCount >= g_EnemySpawners[i].count)
			{
				g_EnemySpawners[i].isEnded = true;
			}
			// �����������Ԃ�ۑ�
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
