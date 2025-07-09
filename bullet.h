/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		弾の制御[bullet.h]									┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.1				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef BULLET_H
#define BULLET_H


#include <DirectXMath.h>
#include "collision.h"


static constexpr unsigned int BULLET_MAX = 512;			// 弾の表示最大数（タイプごと）


enum BULLET_TYPE_ID
{
	NORMAL_BULLET,			// 直線
	WAVE_BULLET,			// sinウェーブ
	MIDDLE_RANGE_BULLET,	// 全方位中距離
	BULLET_TYPE_MAX
};

class BulletStatus
{
protected:
	static constexpr float BULLET_SPEED = 300.0f;			// 弾の速度

	DirectX::XMFLOAT2 m_Position;
	DirectX::XMFLOAT2 m_Size;
	DirectX::XMFLOAT2 m_Velocity;
	double   m_LifeTime;

public:
	BulletStatus();
	/* セッター */
	void SetPosition(DirectX::XMFLOAT2 position) { m_Position = position; };
	void SetSize(DirectX::XMFLOAT2 size) { m_Size = size; };
	void SetVelocity(DirectX::XMFLOAT2 velocity) { m_Velocity = velocity; };
	void SetLifeTime(float life_time) { m_LifeTime = life_time; };

	/* ゲッター */
	DirectX::XMFLOAT2 GetPosition() { return m_Position; };
	DirectX::XMFLOAT2 GetSize() { return m_Size; };
	DirectX::XMFLOAT2 GetVelocity() { return m_Velocity; };
	float GetLifeTime() { return m_LifeTime; };
};

class Bullet : public BulletStatus
{
private:
	int      m_Texid[BULLET_TYPE_MAX];
	bool     m_Enable;
	float    m_OffsetY;
	Circle   m_Collision;

public:
	Bullet();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time, BULLET_TYPE_ID bullet_type, int index);
	void Draw(BULLET_TYPE_ID bullet_type);

	void Shot(BULLET_TYPE_ID type, int index, const DirectX::XMFLOAT2& position);

	/* セッター */
	void SetEnable(bool enable) { m_Enable = enable; };

	/* ゲッター */
	bool GetEnable() { return m_Enable; };
	Circle GetCollision() { return m_Collision; };
};


#endif  //BULLET_H