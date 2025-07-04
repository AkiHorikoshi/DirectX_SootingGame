/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		敵キャラの制御[enemy.h]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.2				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "enemy.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "texture.h"
#include "sprite.h"
#include "collision.h"


/**********************************     定数定義    **************************************/
constexpr float ENEMY_SPEED = -150.0f;


/**********************************     構造体定義    ***************************************/
struct EnemyType
{
	ENEMY_TYPE_ID typeId;		// エネミータイプ管理ID
	int texid;					// エネミーテクスチャ管理ID

	XMUINT2 tPos;				// テクスチャ切り取り座標
	XMUINT2 tSize;				// テクスチャサイズ
	Circle collision;			//　当たり判定
};

struct Enemy
{
	EnemyType* type;			// エネミータイプ別情報
	XMFLOAT2 position;			// エネミー初期位置
	XMFLOAT2 size;				// ポリゴンサイズ
	XMFLOAT2 velocity;			// 進行方向
	double lifeTime;			// 発生してからの経過時間
	float offsetY;				// 発生地点Y座標
	bool isEnable;				// 使用中フラグ
};


/*******************************     グローバル変数宣言    ************************************/
static Enemy g_Enemys[ENEMY_MAX];
static EnemyType g_EnemyType[ENEMY_TYPE_ID_MAX];


/************************************     関数宣言    ****************************************/
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

	g_EnemyType[ENEMY_02].texid = TextureLoad(L"resource/texture/text_itetu.png");
	g_EnemyType[ENEMY_02].typeId = ENEMY_02;
	g_EnemyType[ENEMY_02].tPos = { 0, 0 };
	g_EnemyType[ENEMY_02].tSize = { 256, 128 };
	g_EnemyType[ENEMY_02].collision = { {32.0f,32.0f}, 32.0f };
}

void EnemyFinalize()
{
}

void EnemyUpdate(double elapsed_time)
{
	for (Enemy& ene : g_Enemys)
	{
		// エネミーの使用フラグを折る
		if (ene.position.x < 0 - ene.size.x)
		{
			ene.isEnable = false;
		}

		// 使われてないエネミーの処理はしない
		if (!ene.isEnable)	continue;


		switch (ene.type->typeId)
		{
		case ENEMY_01:
			// 演算用の変数に格納
			XMVECTOR pos = XMLoadFloat2(&ene.position);
			XMVECTOR vel = XMLoadFloat2(&ene.velocity);

			// ポジションをずらす
			pos += vel * elapsed_time;

			// 元の変数に返す
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
		// 使われているEnemy管理番号の時は処理しないで次へ
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

bool EnemyIsEnable(int index)
{
	// バレットが存在するはずのない値をもらったら false を返す
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

void EnemyDestory(int index)
{
	g_Enemys[index].isEnable = false;
}
