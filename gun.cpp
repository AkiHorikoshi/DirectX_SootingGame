/*„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„­
„«															„«
„«		e‚Ìì¬[gun.h]										„«
„«															„«
„°„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„²
„«							Author: aki hoeikoshi			„«
„«							  data: 2025.7.9				„«
„«															„«
„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª*/

#include "gun.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "bullet.h"


void CreateBullet(BULLET_TYPE_ID type, int index, const DirectX::XMFLOAT2& position);


static Bullet g_Bullets[BULLET_MAX];


Gun::Gun()
{
	m_Texid = -1;
	m_Position = { 0.0f,0.0f };
	m_Size = { 0.0f,0.0f };
	m_Collision = { { 0.0f,0.0f }, 0.0f };
}

void Gun::Initialize()
{
	m_Texid = -1;
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].Initialize();
	}
}

void Gun::Finalize()
{
}

void Gun::Update(double elapsed_time, BULLET_TYPE_ID bullet_type)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].Update(elapsed_time, bullet_type, i);
	}
}

void Gun::Draw(BULLET_TYPE_ID bullet_type)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].Draw(bullet_type);
	}
}

void Gun::Shot(BULLET_TYPE_ID type, const DirectX::XMFLOAT2& position)
{
	switch (type)
	{
	case NORMAL_BULLET:
		CreateBullet(type, 0, position);
		break;
	case WAVE_BULLET:
		for (int i = 0; i < 2; i++)
		{
			CreateBullet(type, i, position);
		}
		break;
	case MIDDLE_RANGE_BULLET:
		for (int i = 0; i < 16; i++)
		{
			CreateBullet(type, i, position);
		}
		break;
	}
}

void CreateBullet(BULLET_TYPE_ID type, int index, const XMFLOAT2& position)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// Žg‚Á‚Ä‚¢‚é’e‚ÍƒXƒ‹[
		if (g_Bullets[i].GetEnable()) continue;

		g_Bullets[i].Shot(type, index, position);
		break;
	}
}