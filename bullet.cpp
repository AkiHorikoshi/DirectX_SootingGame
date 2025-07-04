/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�e�̐���[bullet.h]									��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.1				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#include "bullet.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"


/**********************************     �萔��`    **************************************/
static constexpr float BULLET_SPEED = 300.0f;			// �e�̑��x


/**********************************     �\���̒�`    ***************************************/
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


/*******************************     �O���[�o���ϐ��錾    ************************************/
static Bullet g_NormalBullets[BULLET_MAX]{};			// �m�[�}���̒e
static Bullet g_WaveBullets[BULLET_MAX]{};				// �g�łe
static Bullet g_MiddleBullets[BULLET_MAX]{};			// �S���ʒ������e
static int g_BulletTexid{};								// �e�̃e�N�X�`���Ǘ��ԍ�


/************************************     �֐��錾    ****************************************/
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
	// �ʏ�e
	for (Bullet& bull : g_NormalBullets)
	{
		// �e�̕\�����Ԃ��v��
		bull.lifeTime += elapsed_time;
		// �e�̎g�p�t���O��܂�
		if (bull.lifeTime >= 5.0)
		{
			bull.isEnable = false;
		}
		if (bull.position.x > Direct3D_GetBackBufferWidth())
		{
			bull.isEnable = false;
		}

		// �g���ĂȂ��e�̏����͂��Ȃ�
		if (!bull.isEnable)	continue;

		// ���Z�p�̕ϐ��Ɋi�[
		XMVECTOR pos = XMLoadFloat2(&bull.position);
		XMVECTOR vel = XMLoadFloat2(&bull.velocity);

		// �|�W�V���������炷
		pos += vel * elapsed_time;

		// ���̕ϐ��ɕԂ�
		DirectX::XMStoreFloat2(&bull.position, pos);
		DirectX::XMStoreFloat2(&bull.velocity, vel);
	}

	// �g�łe
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �e�̕\�����Ԃ��v��
		g_WaveBullets[i].lifeTime += elapsed_time;
		// �e�̎g�p�t���O��܂�
		if (g_WaveBullets[i].lifeTime >= 5.0)
		{
			g_WaveBullets[i].isEnable = false;
		}
		if (g_WaveBullets[i].position.x > Direct3D_GetBackBufferWidth())
		{
			g_WaveBullets[i].isEnable = false;
		}

		// �g���ĂȂ��e�̏����͂��Ȃ�
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
		// ���Z�p�̕ϐ��Ɋi�[
		XMVECTOR pos = XMLoadFloat2(&g_WaveBullets[i].position);
		XMVECTOR vel = XMLoadFloat2(&g_WaveBullets[i].velocity);

		// �|�W�V���������炷
		pos += vel * elapsed_time;

		// ���̕ϐ��ɕԂ�
		DirectX::XMStoreFloat2(&g_WaveBullets[i].position, pos);
		DirectX::XMStoreFloat2(&g_WaveBullets[i].velocity, vel);
	}

	// �S���ʒ������e
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �e�̕\�����Ԃ��v��
		g_MiddleBullets[i].lifeTime += elapsed_time;
		// �e�̎g�p�t���O��܂�
		if (g_MiddleBullets[i].lifeTime >= 0.5)
		{
			g_MiddleBullets[i].isEnable = false;
		}
		if (g_MiddleBullets[i].position.x > Direct3D_GetBackBufferWidth())
		{
			g_MiddleBullets[i].isEnable = false;
		}

		// �g���ĂȂ��e�̏����͂��Ȃ�
		if (!g_MiddleBullets[i].isEnable)	continue;

		// ���Z�p�̕ϐ��Ɋi�[
		XMVECTOR pos = XMLoadFloat2(&g_MiddleBullets[i].position);
		XMVECTOR vel = XMLoadFloat2(&g_MiddleBullets[i].velocity);

		// �|�W�V���������炷
		pos += vel * elapsed_time;

		// ���̕ϐ��ɕԂ�
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
			// �g���Ă���Bullet�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
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
				// �g���Ă���Bullet�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
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
				// �g���Ă���Bullet�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
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
	// �o���b�g�����݂���͂��̂Ȃ��l����������� false ��Ԃ�
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
