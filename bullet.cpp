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
static constexpr unsigned int BULLET_MAX = 512;
static constexpr float BULLET_SPEED = 600.0f;


/*********************************     �\���̒�`    **************************************/
struct Bullet
{
	XMFLOAT2 position;
	XMFLOAT2 size;
	XMFLOAT2 velocity;
	double lifeTime;
	bool isEnable;
};


/*******************************     �O���[�o���ϐ��錾    ************************************/
static Bullet g_Bullets[BULLET_MAX]{};
static int g_BulletTexid{};


/************************************     �֐��錾    ****************************************/
void BulletInitialize()
{
	for (Bullet& bull : g_Bullets)
	{
		bull.isEnable = false;
	}
	g_BulletTexid = TextureLoad(L"resource/texture/tama.png");
}

void BulletFinalize()
{
}

void BulletUpdate(double elapsed_time)
{
	for (Bullet& bull : g_Bullets)
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
}

void BulletDraw()
{
	for (Bullet& bull : g_Bullets)
	{
		if (!bull.isEnable)	continue;

		Sprite_Draw(g_BulletTexid, bull.position, bull.size, { 0, 0 }, { 512, 512 });
	}
}

void ShotBullet(const XMFLOAT2& position)
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		// �g���Ă���Bullet�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
		if (g_Bullets[i].isEnable) continue;

		g_Bullets[i].isEnable = true;
		g_Bullets[i].lifeTime = 0.0f;
		g_Bullets[i].position = position;
		g_Bullets[i].size = { 32.0f, 32.0f };
		g_Bullets[i].velocity = { BULLET_SPEED, 0.0 };
		break;
	}
}
