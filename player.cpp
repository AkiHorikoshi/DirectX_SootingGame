/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		プレイヤー制御[player.cpp]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.6.27				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "key_logger.h"
#include "bullet.h"


constexpr float PLAYER_SPEED = 0.5f;		// プレイヤー移動速度
constexpr float SHOTDELAY = 0.3f;			// 弾の発射間隔


static int g_PlayerTexid = -1;
static XMFLOAT2 g_PlayerPos{};
static XMFLOAT2 g_PlayerSize{};
static XMFLOAT2 g_PlayerVelocity{};
static float g_Speed{};

static float g_ShotDelay;


void PlayerInitialize(const XMFLOAT2& playerpos)
{
	g_PlayerTexid = TextureLoad(L"resource/texture/moai.png");
	g_PlayerPos = playerpos;
	g_PlayerSize = { 32.0f, 32.0f };
	g_PlayerVelocity = { 0.0f, 0.0f };
	g_Speed = PLAYER_SPEED;

	g_ShotDelay = SHOTDELAY;
}

void PlayerFinalize()
{
}

void PlayerUpdate(double elapsed_time)
{
	/* 移動処理 */
	// 演算用の変数に格納
	XMVECTOR pos = XMLoadFloat2(&g_PlayerPos);
	XMVECTOR vel = XMLoadFloat2(&g_PlayerVelocity);

	XMVECTOR direction{};

	// キーボード WASD移動
	if (KeyLoggerIsPressed(KK_W))
	{
		direction += { 0.0f, -1.0f};
	}
	if (KeyLoggerIsPressed(KK_A))
	{
		direction += { -1.0f, 0.0f};
	}
	if (KeyLoggerIsPressed(KK_S))
	{
		direction += { 0.0f, 1.0f};
	}
	if (KeyLoggerIsPressed(KK_D))
	{
		direction += { 1.0f, 0.0f};
	}

	// 単位ベクトルにする関数でdirectionの大きさを１にする
	direction = XMVector2Normalize(direction);
	// ベクトルサイズを変更して速度に与える
	vel += direction * g_Speed;
	// ポジションをずらす
	pos += vel;
	// 速度を減衰させる（滑りやすさの表現：値が大きいほど滑りやすい）
	vel *= 0.9f;

	// 元の変数に返す
	XMStoreFloat2(&g_PlayerPos, pos);
	XMStoreFloat2(&g_PlayerVelocity, vel);

	// 画面外への移動を阻止
	if (g_PlayerPos.x <= 0)
	{
		g_PlayerPos.x = 0;
	}
	if (g_PlayerPos.x >= Direct3D_GetBackBufferWidth() - g_PlayerSize.x)
	{
		g_PlayerPos.x = Direct3D_GetBackBufferWidth() - g_PlayerSize.x;
	}
	if (g_PlayerPos.y <= 0)
	{
		g_PlayerPos.y = 0;
	}
	if (g_PlayerPos.y >= Direct3D_GetBackBufferHeight() - g_PlayerSize.y)
	{
		g_PlayerPos.y = Direct3D_GetBackBufferHeight() - g_PlayerSize.y;
	}

	// 弾の発射
	g_ShotDelay += -elapsed_time;
	if (g_ShotDelay <= 0)
	{
		if (KeyLoggerIsPressed(KK_SPACE))
		{
			ShotBullet(WAVE_BULLET, g_PlayerPos);
		}
		g_ShotDelay = SHOTDELAY;
	}
}

void PlayerDraw()
{
	Sprite_Draw(g_PlayerTexid, g_PlayerPos, g_PlayerSize, { 0, 0 }, { 512, 512 });
}
