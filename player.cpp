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
#include "collision.h"


Player::Player()
{
	/* �ϐ������� */
	m_Texid = -1;// TextureLoad(L"resource/texture/moai.png");
	m_Position = { 100.0f, 405.0f };
	m_Size = { 32.0f, 32.0f };
	m_Velocity = {};
	m_Speed = PLAYER_SPEED;
	m_ShotDelay = SHOTDELAY;
	m_Collision = { {16.0f, 16.0f}, 16.0f };
	m_Enable = true;
}

void Player::Initialize()
{
	m_Texid = TextureLoad(L"resource/texture/moai.png");
}

void Player::Finalize()
{
}

void Player::Update(double elapsed_time)
{
	// �v���C���[������ł��珈�����s��Ȃ�
	if (!m_Enable) return;

	/* �ړ����� */
	// ���Z�p�̕ϐ��Ɋi�[
	XMVECTOR pos = XMLoadFloat2(&m_Position);
	XMVECTOR vel = XMLoadFloat2(&m_Velocity);

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
	vel += direction * m_Speed;
	// �|�W�V���������炷
	pos += vel;
	// ���x������������i����₷���̕\���F�l���傫���قǊ���₷���j
	vel *= 0.9f;

	// ���̕ϐ��ɕԂ�
	XMStoreFloat2(&m_Position, pos);
	XMStoreFloat2(&m_Velocity, vel);

	// ��ʊO�ւ̈ړ���j�~
	if (m_Position.x <= 0)
	{
		m_Position.x = 0;
	}
	if (m_Position.x >= Direct3D_GetBackBufferWidth() - m_Size.x)
	{
		m_Position.x = Direct3D_GetBackBufferWidth() - m_Size.x;
	}
	if (m_Position.y <= 0)
	{
		m_Position.y = 0;
	}
	if (m_Position.y >= Direct3D_GetBackBufferHeight() - m_Size.y)
	{
		m_Position.y = Direct3D_GetBackBufferHeight() - m_Size.y;
	}

	// �e�̔���
	m_ShotDelay += -elapsed_time;
	if (m_ShotDelay <= 0)
	{
		if (KeyLoggerIsPressed(KK_SPACE))
		{
			ShotBullet(NORMAL_BULLET, { m_Position.x + (m_Size.x * 0.3f), m_Position.y + (m_Size.y * 0.3f) });
		}
		m_ShotDelay = SHOTDELAY;
	}
}

void Player::Draw()
{
	// �v���C���[������ł��珈�����s��Ȃ�
	if (!m_Enable) return;

	Sprite_Draw(m_Texid, m_Position, m_Size, { 0, 0 }, { 512, 512 });
}

Circle Player::GetCollision()
{
	float cx = m_Collision.center.x + m_Position.x;
	float cy = m_Collision.center.y + m_Position.y;

	return { {cx, cy}, m_Collision.radius };
}