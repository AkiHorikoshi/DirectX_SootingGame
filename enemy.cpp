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
#include "collision.h"
//#include "effect.h"


/**********************************     �萔��`    **************************************/
constexpr float ENEMY_SPEED = -150.0f;


/**********************************     �\���̒�`    ***************************************/
struct EnemyType
{
	ENEMY_TYPE_ID typeId;		// �G�l�~�[�^�C�v�Ǘ�ID
	int texid;					// �G�l�~�[�e�N�X�`���Ǘ�ID

	XMUINT2 tPos;				// �e�N�X�`���؂�����W
	XMUINT2 tSize;				// �e�N�X�`���T�C�Y
	Circle collision;			//�@�����蔻��
	int hp_max;
};

struct Enemy
{
	EnemyType* type;			// �G�l�~�[�^�C�v�ʏ��
	XMFLOAT2 position;			// �G�l�~�[�����ʒu
	XMFLOAT2 size;				// �|���S���T�C�Y
	XMFLOAT2 velocity;			// �i�s����
	double lifeTime;			// �������Ă���̌o�ߎ���
	int hp;
	float offsetY;				// �����n�_Y���W
	bool isEnable;				// �g�p���t���O
	bool isDanege;				// �_���[�W���󂯂���
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
	g_EnemyType[ENEMY_01].collision = { {32.0f,32.0f}, 32.0f };
	g_EnemyType[ENEMY_01].hp_max = 2;

	g_EnemyType[ENEMY_02].texid = TextureLoad(L"resource/texture/text_itetu.png");
	g_EnemyType[ENEMY_02].typeId = ENEMY_02;
	g_EnemyType[ENEMY_02].tPos = { 0, 0 };
	g_EnemyType[ENEMY_02].tSize = { 256, 128 };
	g_EnemyType[ENEMY_02].collision = { {32.0f,32.0f}, 32.0f };
	g_EnemyType[ENEMY_02].hp_max = 5;
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

		Sprite_Draw(ene.type->texid, ene.position, ene.size, ene.type->tPos, ene.type->tSize,ene.isDanege ? XMFLOAT4{1.0f,1.0f,0.0f,1.0f} : XMFLOAT4{1.0f, 1.0f, 0.0f, 1.0f});
		
		ene.isDanege = false;
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
		ene.hp = g_EnemyType[id].hp_max;
		ene.offsetY = position.y;
		ene.isDanege = false;
		break;
	}
}

bool EnemyIsEnable(int index)
{
	// �o���b�g�����݂���͂��̂Ȃ��l����������� false ��Ԃ�
	if (index < 0 || index > ENEMY_MAX)
	{
		return false;
	}
	return g_Enemys[index].isEnable;
}

Circle EnemyGetCollision(int index)
{
	int id = g_Enemys[index].type->typeId;

	float cx = g_EnemyType[id].collision.center.x + g_Enemys[index].position.x;
	float cy = g_EnemyType[id].collision.center.y + g_Enemys[index].position.y;

	return { {cx,cy},g_Enemys[index].type->collision.radius };
}

void EnemyDamege(int index)
{
	g_Enemys[index].hp--;
	g_Enemys[index].isDanege = true;

	if (g_Enemys[index].hp <= 0)
	{
		g_Enemys[index].isEnable = false;
	}
}

void EnemyDestory(int index)
{
	g_Enemys[index].isEnable = false;
}
