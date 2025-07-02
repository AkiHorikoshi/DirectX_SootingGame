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


/**********************************     �萔��`    **************************************/
static constexpr unsigned int BULLET_MAX = 512;			// �e�̕\���ő吔�i�^�C�v���Ɓj
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
};


/*******************************     �O���[�o���ϐ��錾    ************************************/
static Bullet g_NormalBullets[BULLET_MAX]{};			// �m�[�}���̒e
static Bullet g_WaveBullets[BULLET_MAX]{};				// �g�łe
static int g_BulletTexid{};								// �e�̃e�N�X�`���Ǘ��ԍ�
static float g_WaveAngle[BULLET_MAX]{};					// �g�łe��sin�g�̑傫���H�p�x�H


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
	g_BulletTexid = TextureLoad(L"resource/texture/tama2.png");
}

void BulletFinalize()
{
}

void BulletUpdate(double elapsed_time)
{
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
		XMStoreFloat2(&bull.position, pos);
		XMStoreFloat2(&bull.velocity, vel);
	}

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

		g_WaveAngle[i] += XM_2PI / 2 * elapsed_time * 5.0f;

		if (i % 2 == 0)
		{
			g_WaveBullets[i].velocity.y += sinf(g_WaveAngle[i]) * 300.0f;
		}
		else
		{
			g_WaveBullets[i].velocity.y += -sinf(g_WaveAngle[i]) * 300.0f;
		}

		g_WaveBullets[i].position.y = g_WaveBullets[i].offsetY;
		// ���Z�p�̕ϐ��Ɋi�[
		XMVECTOR pos = XMLoadFloat2(&g_WaveBullets[i].position);
		XMVECTOR vel = XMLoadFloat2(&g_WaveBullets[i].velocity);

		// �|�W�V���������炷
		pos += vel * elapsed_time;

		// ���̕ϐ��ɕԂ�
		XMStoreFloat2(&g_WaveBullets[i].position, pos);
		XMStoreFloat2(&g_WaveBullets[i].velocity, vel);
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
			bull.offsetY = position.y;
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
				bull.offsetY = position.y;
				break;
			}
		}
		break;
	}
}
