/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		弾の制御[bullet.h]									┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.1				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "bullet.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"


/**********************************     定数定義    **************************************/
static constexpr float BULLET_SPEED = 300.0f;			// 弾の速度


/**********************************     構造体定義    ***************************************/
struct BulletType
{

};

struct Bullet
{
	XMFLOAT2 position;
	XMFLOAT2 size;
	XMFLOAT2 velocity;
	float offsetY;
	double lifeTime;
	bool isEnable;
	Circle collision;
};


/*******************************     グローバル変数宣言    ************************************/
static Bullet g_NormalBullets[BULLET_MAX]{};			// ノーマルの弾
static Bullet g_WaveBullets[BULLET_MAX]{};				// 波打つ弾
static Bullet g_MiddleBullets[BULLET_MAX]{};			// 全方位中距離弾
static int g_BulletTexid{};								// 弾のテクスチャ管理番号


/************************************     関数宣言    ****************************************/
void BulletInitialize()
{
	for (Bullet& bull : g_NormalBullets)
	{
		bull.isEnable = false;
	}
	for (Bullet& bull : g_WaveBullets)
	{
		bull.isEnable = false;
	}
	for (Bullet& bull : g_MiddleBullets)
	{
		bull.isEnable = false;
	}

	g_BulletTexid = TextureLoad(L"resource/texture/tama1.png");
}

void BulletFinalize()
{
}

void BulletUpdate(double elapsed_time)
{
	// 通常弾
	for (Bullet& bull : g_NormalBullets)
	{
		// 弾の表示時間を計測
		bull.lifeTime += elapsed_time;
		// 弾の使用フラグを折る
		if (bull.lifeTime >= 5.0)
		{
			bull.isEnable = false;
		}
		if (bull.position.x > Direct3D_GetBackBufferWidth())
		{
			bull.isEnable = false;
		}

		// 使われてない弾の処理はしない
		if (!bull.isEnable)	continue;

		// 演算用の変数に格納
		XMVECTOR pos = XMLoadFloat2(&bull.position);
		XMVECTOR vel = XMLoadFloat2(&bull.velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&bull.position, pos);
		DirectX::XMStoreFloat2(&bull.velocity, vel);
	}

	// 波打つ弾
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// 弾の表示時間を計測
		g_WaveBullets[i].lifeTime += elapsed_time;
		// 弾の使用フラグを折る
		if (g_WaveBullets[i].lifeTime >= 5.0)
		{
			g_WaveBullets[i].isEnable = false;
		}
		if (g_WaveBullets[i].position.x > Direct3D_GetBackBufferWidth())
		{
			g_WaveBullets[i].isEnable = false;
		}

		// 使われてない弾の処理はしない
		if (!g_WaveBullets[i].isEnable)	continue;

		if (i % 2 == 0)
		{
			g_WaveBullets[i].velocity.y += sinf(g_WaveBullets[i].lifeTime * 15.0f) * 300.0f;
		}
		else
		{
			g_WaveBullets[i].velocity.y += -sinf(g_WaveBullets[i].lifeTime * 15.0f) * 300.0f;
		}

		g_WaveBullets[i].position.y = g_WaveBullets[i].offsetY;
		// 演算用の変数に格納
		XMVECTOR pos = XMLoadFloat2(&g_WaveBullets[i].position);
		XMVECTOR vel = XMLoadFloat2(&g_WaveBullets[i].velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&g_WaveBullets[i].position, pos);
		DirectX::XMStoreFloat2(&g_WaveBullets[i].velocity, vel);
	}

	// 全方位中距離弾
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// 弾の表示時間を計測
		g_MiddleBullets[i].lifeTime += elapsed_time;
		// 弾の使用フラグを折る
		if (g_MiddleBullets[i].lifeTime >= 0.5)
		{
			g_MiddleBullets[i].isEnable = false;
		}
		if (g_MiddleBullets[i].position.x > Direct3D_GetBackBufferWidth())
		{
			g_MiddleBullets[i].isEnable = false;
		}

		// 使われてない弾の処理はしない
		if (!g_MiddleBullets[i].isEnable)	continue;

		// 演算用の変数に格納
		XMVECTOR pos = XMLoadFloat2(&g_MiddleBullets[i].position);
		XMVECTOR vel = XMLoadFloat2(&g_MiddleBullets[i].velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&g_MiddleBullets[i].position, pos);
		DirectX::XMStoreFloat2(&g_MiddleBullets[i].velocity, vel);
	}
}

void BulletDraw()
{
	for (Bullet& bull : g_NormalBullets)
	{
		if (!bull.isEnable)	continue;

		Sprite_Draw(g_BulletTexid, bull.position, bull.size, { 0, 0 }, { 512, 512 });
	}
	for (Bullet& bull : g_WaveBullets)
	{
		if (!bull.isEnable)	continue;

		Sprite_Draw(g_BulletTexid, bull.position, bull.size, { 0, 0 }, { 512, 512 });
	}
	for (Bullet& bull : g_MiddleBullets)
	{
		if (!bull.isEnable)	continue;

		Sprite_Draw(g_BulletTexid, bull.position, bull.size, { 0, 0 }, { 512, 512 });
	}
}

void ShotBullet(BULLET_TYPE_ID type, const XMFLOAT2& position)
{
	switch (type)
	{
	case NORMAL_BULLET:
		for (Bullet& bull : g_NormalBullets)
		{
			// 使われているBullet管理番号の時は処理しないで次へ
			if (bull.isEnable) continue;

			bull.isEnable = true;
			bull.lifeTime = 0.0f;
			bull.position = position;
			bull.size     = { 32.0f, 32.0f };
			bull.velocity = { BULLET_SPEED, 0.0 };
			bull.offsetY  = position.y;
			bull.collision   = { { 32.0f * 0.7, 32.0f * 0.5f }, (32.0f * 0.9f)};
			break;
		}
	break;
	case WAVE_BULLET:
		for (int i = 0; i < 2; i++)
		{
			for (Bullet& bull : g_WaveBullets)
			{
				// 使われているBullet管理番号の時は処理しないで次へ
				if (bull.isEnable) continue;

				bull.isEnable = true;
				bull.lifeTime = 0.0f;
				bull.position = position;
				bull.size     = { 32.0f, 32.0f };
				bull.velocity = { BULLET_SPEED, 0.0 };
				bull.offsetY  = position.y;
				bull.collision   = { { 32.0f * 0.7, 32.0f * 0.5f }, (32.0f * 0.9f) };
				break;
			}
		}
		break;
	case MIDDLE_RANGE_BULLET:
		for (int i = 0; i < 16; i++)
		{
			for (Bullet& bull : g_MiddleBullets)
			{
				// 使われているBullet管理番号の時は処理しないで次へ
				if (bull.isEnable) continue;

				bull.isEnable = true;
				bull.lifeTime = 0.0f;
				bull.position = position;
				bull.size = { 16.0f, 16.0f };
				bull.velocity = { BULLET_SPEED * cosf(XM_2PI / 16* i), BULLET_SPEED * sinf(XM_2PI / 16 * i) };
				bull.offsetY = position.y;
				bull.collision = { { 16.0f * 0.7, 32.0f * 0.5f }, (16.0f * 0.9f) };
				break;
			}
		}
		break;
	}
}

bool BulletIsEnable(int index)
{
	// バレットが存在するはずのない値をもらったら false を返す
	if (index < 0 || index > BULLET_MAX)
	{
		return false;
	}

	return g_NormalBullets[index].isEnable;
}

Circle BulletGetCollision(int index)
{
	float cx = g_NormalBullets[index].collision.center.x + g_NormalBullets[index].position.x;
	float cy = g_NormalBullets[index].collision.center.y + g_NormalBullets[index].position.y;

	return { {cx, cy}, g_NormalBullets[index].collision.radius };
}

void BulletDestroy(int index)
{
	g_NormalBullets[index].isEnable = false;
}
