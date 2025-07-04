/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		ゲームメイン[game.cpp]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.6.27				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"
#include "game_window.h"
#include "key_logger.h"
#include "user_interface.h"


void HitJudgmentBulletVSEnemy();
void HitJudgmentPlayerVSEnemy();


Player g_Player;
UI g_Ui;


void GameInitialize()
{
	g_Ui.UiInitialize();
	g_Player.Initialize();
	BulletInitialize();
	EnemyInitialize();
	EnemySpawnerInitialize();

	CreateEnemySpawner({ SCREEN_WIDTH, 300.0f }, ENEMY_01, 3.0, 3.0, 100);
	CreateEnemySpawner({ 1500.0f, 300.0f }, ENEMY_02, 5.0, 1.0, 100);
}

void GameFinalize()
{
	EnemySpawnerFinalize();
	EnemyFinalize();
	BulletFinalize();
	g_Player.Finalize();
	g_Ui.UiFinalize();
}

void GameUpdate(double elapsed_time)
{
	g_Ui.UiUppdate(elapsed_time);
	EnemySpawnerUpdate(elapsed_time);

	g_Player.Update(elapsed_time);
	BulletUpdate(elapsed_time);
	EnemyUpdate(elapsed_time);

	HitJudgmentBulletVSEnemy();
	HitJudgmentPlayerVSEnemy();
}

void GameDraw()
{
	EnemyDraw();
	BulletDraw();
	g_Player.Draw();

	g_Ui.UiDraw();
}

void HitJudgmentBulletVSEnemy()
{
	for (int bulli = 0; bulli < BULLET_MAX; bulli++)
	{
		// 不使用のバレットは調べずにスルー
		if (!BulletIsEnable(bulli)) continue;

		// エネミー全部との当たり判定をとる
		for (int enei = 0; enei < ENEMY_MAX; enei++)
		{
			// 不使用のエネミーは調べずにスルー
			if (!EnemyIsEnable(enei)) continue;

			// ヒット判定を調べる
			if (CollisionIsOverlapCircle(BulletGetCollision(bulli), EnemyGetCollision(enei)))
			{
				// 当たった弾とエネミーを消す
				BulletDestroy(bulli);
				EnemyDestory(enei);

				g_Ui.AddPoint(1);
			}
		}
	}
}

void HitJudgmentPlayerVSEnemy()
{
	if (!g_Player.IsEnable())return;

	for (int enei = 0; enei + ENEMY_MAX; enei++)
	{
		if (!EnemyIsEnable(enei)) continue;

		if (CollisionIsOverlapCircle(g_Player.GetCollision(), EnemyGetCollision(enei)))
		{
			// 当たった弾とエネミーを消す
			g_Player.Destroy();
			EnemyDestory(enei);

			g_Ui.AddPoint(1);
		}
	}
}
