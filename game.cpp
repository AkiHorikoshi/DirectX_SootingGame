/*„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„­
„«															„«
„«		ƒQ[ƒ€ƒƒCƒ“[game.cpp]								„«
„«															„«
„°„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„²
„«							Author: aki hoeikoshi			„«
„«							  data: 2025.6.27				„«
„«															„«
„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª*/

#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "enemy_spawner.h"

#include "key_logger.h"

Player g_Player;

void GameInitialize()
{
	g_Player.PlayerInitialize();
	BulletInitialize();
	EnemyInitialize();
	EnemySpawnerInitialize();

	CreateEnemySpawner({ 1000.0f, 300.0f }, ENEMY_01, 3.0, 3.0, 100);
	CreateEnemySpawner({ 1000.0f, 300.0f }, ENEMY_02, 5.0, 1.0, 100);
}

void GameFinalize()
{
	EnemySpawnerFinalize();
	EnemyFinalize();
	BulletFinalize();
	g_Player.PlayerFinalize();
}

void GameUpdate(double elapsed_time)
{
	//EnemySpawnerUpdate(elapsed_time);

	g_Player.PlayerUpdate(elapsed_time);
	BulletUpdate(elapsed_time);
	EnemyUpdate(elapsed_time);
}

void GameDraw()
{
	EnemyDraw();
	BulletDraw();
	g_Player.PlayerDraw();
}
