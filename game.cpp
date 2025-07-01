/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�Q�[�����C��[game.cpp]								��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.27				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#include "game.h"
#include "player.h"
#include "bullet.h"
void GameInitialize()
{
	PlayerInitialize({ 200.0f, 200.0f });
	BulletInitialize();
}

void GameFinalize()
{
	BulletFinalize();
	PlayerFinalize();
}

void GameUpdate(double elapsed_tipe)
{
	PlayerUpdate(elapsed_tipe);
	BulletUpdate(elapsed_tipe);
}

void GameDraw()
{
	BulletDraw();
	PlayerDraw();
}
