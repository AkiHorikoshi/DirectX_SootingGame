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


/************************************     関数宣言    ****************************************/
BulletStatus::BulletStatus()
{
	m_Position = { 0.0f,0.0f };
	m_Size     = { 0.0f,0.0f };
	m_Velocity = { 0.0f,0.0f };
	m_LifeTime = 0.0;
}

Bullet::Bullet()
{
	m_Texid[NORMAL_BULLET]       = -1;
	m_Texid[WAVE_BULLET]         = -1;
	m_Texid[MIDDLE_RANGE_BULLET] = -1;
	m_Enable = false;
	m_OffsetY     = 0.0f;
	m_Collision   = { {0.0f,0.0f}, 0.0f};
}

void Bullet::Initialize()
{
	m_Texid[NORMAL_BULLET]       = TextureLoad(L"resource/texture/tama1.png");
	m_Texid[WAVE_BULLET]         = TextureLoad(L"resource/texture/tama2.png");
	m_Texid[MIDDLE_RANGE_BULLET] = TextureLoad(L"resource/texture/tama1.png");
}

void Bullet::Finalize()
{
}

void Bullet::Update(double elapsed_time, BULLET_TYPE_ID bullet_type, int index)
{
	// 弾の表示時間を計測
	m_LifeTime += -elapsed_time;

	// 弾の使用フラグを折る
	if (m_LifeTime <= 0.0)
	{// 生存時間
		m_Enable = false;
	}
	// 画面外
	if (m_Position.x > Direct3D_GetBackBufferWidth())
	{
		m_Enable = false;
	}

	// 使われてない弾の処理はしない
	if (!m_Enable) return;

	XMVECTOR pos{};
	XMVECTOR vel{};

	switch (bullet_type)
	{
	/* 通常弾 */
	case NORMAL_BULLET:
		// 演算用の変数に格納
		pos = XMLoadFloat2(&m_Position);
		vel = XMLoadFloat2(&m_Velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&m_Position, pos);
		DirectX::XMStoreFloat2(&m_Velocity, vel);
		break;

	/* 波打つ弾 */
	case WAVE_BULLET:
		if (index % 2 == 0)
		{
			m_Velocity.y += sinf(m_LifeTime * 15.0f) * 300.0f;
		}
		else
		{
			m_Velocity.y += -sinf(m_LifeTime * 15.0f) * 300.0f;
		}

		m_Position.y = m_OffsetY;
		// 演算用の変数に格納
		pos = XMLoadFloat2(&m_Position);
		vel = XMLoadFloat2(&m_Velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&m_Position, pos);
		DirectX::XMStoreFloat2(&m_Velocity, vel);
		break;

	/* 全方位中距離弾 */
	case MIDDLE_RANGE_BULLET:
		// 演算用の変数に格納
		pos = XMLoadFloat2(&m_Position);
		vel = XMLoadFloat2(&m_Velocity);

		// ポジションをずらす
		pos += vel * elapsed_time;

		// 元の変数に返す
		DirectX::XMStoreFloat2(&m_Position, pos);
		DirectX::XMStoreFloat2(&m_Velocity, vel);
		break;
	}
}

void Bullet::Draw(BULLET_TYPE_ID bullet_type)
{
	if (!m_Enable)	return;

	switch (bullet_type)
	{
	case NORMAL_BULLET:
		Sprite_Draw(m_Texid[NORMAL_BULLET], m_Position, m_Size, { 0, 0 }, { 512, 512 });
		break;
	case WAVE_BULLET:
		Sprite_Draw(m_Texid[WAVE_BULLET], m_Position, m_Size, { 0, 0 }, { 512, 512 });
		break;
	case MIDDLE_RANGE_BULLET:
		Sprite_Draw(m_Texid[MIDDLE_RANGE_BULLET], m_Position, m_Size, { 0, 0 }, { 512, 512 });
		break;
	}
}

void Bullet::Shot(BULLET_TYPE_ID type, int index, const XMFLOAT2& position)
{
	// 使われている時は処理しないで次へ
	if (m_Enable) return;

	switch (type)
	{
	case NORMAL_BULLET:
		m_Enable = true;
		m_LifeTime = 5.0f;
		m_Position = position;
		m_Size = { 32.0f, 32.0f };
		m_Velocity = { BULLET_SPEED, 0.0 };
		m_OffsetY = position.y;
		m_Collision = { { 32.0f * 0.7, 32.0f * 0.5f }, (32.0f * 0.5f) };
		break;
	case WAVE_BULLET:
		m_Enable = true;
		m_LifeTime = 5.0f;
		m_Position = position;
		m_Size = { 32.0f, 32.0f };
		m_Velocity = { BULLET_SPEED, 0.0 };
		m_OffsetY = position.y;
		m_Collision = { { 32.0f * 0.7, 32.0f * 0.5f }, (32.0f * 0.5f) };
		break;
	case MIDDLE_RANGE_BULLET:
		m_Enable = true;
		m_LifeTime = 0.5f;
		m_Position = position;
		m_Size = { 16.0f, 16.0f };
		m_Velocity = { BULLET_SPEED * cosf(XM_2PI / 16 * index), BULLET_SPEED * sinf(XM_2PI / 16 * index) };
		m_OffsetY = position.y;
		m_Collision = { { 16.0f * 0.7, 32.0f * 0.5f }, (16.0f * 0.5f) };
		break;
	}
}