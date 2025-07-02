/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�G�L�����̔�������[enemy_spawner.h]					��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.2				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef ENEMYSPAWNER_H
#define ENEMYSPAWNER_H


#include <DirectXMath.h>
#include "enemy.h"


void EnemySpawnerInitialize();
void EnemySpawnerFinalize();
void EnemySpawnerUpdate(double elapsed_time);
void EnemySpawnerDraw();

// ����: �P�E�����ꏊ �Q�E�G�l�~�[�ԍ� �R�E��������(���Ԍo��)
void CreateEnemySpawner(const DirectX::XMFLOAT2& position, ENEMY_TYPE_ID id, double spawn_time, double spawn_rate, int spawn_count);



#endif  //ENEMY_SPAWNER_H