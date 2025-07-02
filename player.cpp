/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�v���C���[����[player.cpp]								��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.27				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#include "player.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "key_logger.h"
#include "bullet.h"


constexpr float PLAYER_SPEED = 0.5f;		// �v���C���[�ړ����x
constexpr float SHOTDELAY = 0.3f;			// �e�̔��ˊԊu


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
	/* �ړ����� */
	// ���Z�p�̕ϐ��Ɋi�[
	XMVECTOR pos = XMLoadFloat2(&g_PlayerPos);
	XMVECTOR vel = XMLoadFloat2(&g_PlayerVelocity);

	XMVECTOR direction{};

	// �L�[�{�[�h WASD�ړ�
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

	// �P�ʃx�N�g���ɂ���֐���direction�̑傫�����P�ɂ���
	direction = XMVector2Normalize(direction);
	// �x�N�g���T�C�Y��ύX���đ��x�ɗ^����
	vel += direction * g_Speed;
	// �|�W�V���������炷
	pos += vel;
	// ���x������������i����₷���̕\���F�l���傫���قǊ���₷���j
	vel *= 0.9f;

	// ���̕ϐ��ɕԂ�
	XMStoreFloat2(&g_PlayerPos, pos);
	XMStoreFloat2(&g_PlayerVelocity, vel);

	// ��ʊO�ւ̈ړ���j�~
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

	// �e�̔���
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
