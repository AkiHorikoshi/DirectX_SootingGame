/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		敵キャラの制御[enemy.h]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.2				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef ENEMY_H
#define ENEMY_H


#include <DirectXMath.h>
#include "collision.h"


constexpr int ENEMY_MAX = 128;		// 画面内に存在するエネミーの最大数


enum ENEMY_TYPE_ID : int
{
	ENEMY_01,
	ENEMY_02,
	ENEMY_TYPE_ID_MAX
};


void EnemyInitialize();
void EnemyFinalize();
void EnemyUpdate(double elapsed_time);
void EnemyDraw();

void CreateEnemy(ENEMY_TYPE_ID id, const DirectX::XMFLOAT2& position);

bool EnemyIsEnable(int index);
Circle EnemyGetCollision(int index);

int EnemyDamege(int index);
void EnemyDestory(int index);
#endif  //ENEMY_H