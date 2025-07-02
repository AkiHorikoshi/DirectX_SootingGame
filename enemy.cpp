/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�G�L�����̐���[enemy.h]								��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.2				��
��															��
����������������������������������������������������������������������������������������������������������������������*/


#include "enemy.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"


/**********************************     �萔��`    **************************************/
constexpr int ENEMY_MAX = 128;		// ��ʓ��ɑ��݂���G�l�~�[�̍ő吔
constexpr float ENEMY_SPEED = -150.0f;


/**********************************     �\���̒�`    ***************************************/
struct EnemyType
{
	ENEMY_TYPE_ID typeId;
	int texid;
	XMUINT2 tPos;
	XMUINT2 tSize;
};

struct Enemy
{
	EnemyType* type;
	XMFLOAT2 position;
	XMFLOAT2 size;
	XMFLOAT2 velocity;
	double lifeTime;
	float offsetY;
	bool isEnable;
};


/*******************************     �O���[�o���ϐ��錾    ************************************/
static Enemy g_Enemys[ENEMY_MAX];
static EnemyType g_EnemyType[ENEMY_TYPE_ID_MAX];


/************************************     �֐��錾    ****************************************/
void EnemyInitialize()
{
	for (Enemy& ene : g_Enemys)
	{
		// ene.type->texid = -1;
		ene.isEnable = false;
	}

	g_EnemyType[ENEMY_01].texid = TextureLoad(L"resource/texture/moai.png");
	g_EnemyType[ENEMY_01].typeId = ENEMY_01;
	g_EnemyType[ENEMY_01].tPos = { 0, 0 };
	g_EnemyType[ENEMY_01].tSize = { 512, 512 };

	g_EnemyType[ENEMY_02].texid = TextureLoad(L"resource/texture/text_itetu.png");
	g_EnemyType[ENEMY_02].typeId = ENEMY_02;
	g_EnemyType[ENEMY_02].tPos = { 0, 0 };
	g_EnemyType[ENEMY_02].tSize = { 256, 128 };
}

void EnemyFinalize()
{
}

void EnemyUpdate(double elapsed_time)
{
	for (Enemy& ene : g_Enemys)
	{
		// �G�l�~�[�̎g�p�t���O��܂�
		if (ene.position.x < 0 - ene.size.x)
		{
			ene.isEnable = false;
		}

		// �g���ĂȂ��G�l�~�[�̏����͂��Ȃ�
		if (!ene.isEnable)	continue;


		switch (ene.type->typeId)
		{
		case ENEMY_01:
			// ���Z�p�̕ϐ��Ɋi�[
			XMVECTOR pos = XMLoadFloat2(&ene.position);
			XMVECTOR vel = XMLoadFloat2(&ene.velocity);

			// �|�W�V���������炷
			pos += vel * elapsed_time;

			// ���̕ϐ��ɕԂ�
			XMStoreFloat2(&ene.position, pos);
			XMStoreFloat2(&ene.velocity, vel);
			break;
		case ENEMY_02:
			ene.position.x += ene.velocity.x * elapsed_time;
			ene.position.y = ene.offsetY + (sinf(ene.lifeTime * 5.0) * 150.0f);

			break;
		}
		ene.lifeTime += elapsed_time;
	}
}

void EnemyDraw()
{
	for (Enemy& ene : g_Enemys)
	{
		if (!ene.isEnable)	continue;

		Sprite_Draw(ene.type->texid, ene.position, ene.size, ene.type->tPos, ene.type->tSize);
	}
}

void CreateEnemy(ENEMY_TYPE_ID id, const DirectX::XMFLOAT2& position)
{
	for (Enemy& ene : g_Enemys)
	{
		// �g���Ă���Enemy�Ǘ��ԍ��̎��͏������Ȃ��Ŏ���
		if (ene.isEnable) continue;

		ene.type = &g_EnemyType[id];
		ene.isEnable = true;
		ene.position = position;
		ene.size = { 64.0f, 64.0f };
		ene.velocity = { ENEMY_SPEED, 0.0 };
		ene.lifeTime = 0.0;
		ene.offsetY = position.y;
		break;
	}
}
