/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		プレイヤー制御[player.h]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.6.27				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef PLAYER_H
#define PLAYER_H


#include <DirectXMath.h>
#include "collision.h"
#include "bullet.h"

class Player
{
private:
	/* 定数定義 */
	static constexpr float PLAYER_SPEED = 0.5f;			// プレイヤー移動速度
	static constexpr float SHOTDELAY = 0.1f;			// 弾の発射間隔

	/* メンバ変数宣言 */
	int  m_Texid;					// プレイヤーのテクスチャ管理ID
	int  m_SoundId;					// プレイヤー死亡時のサウンドID
	bool m_Enable;					// プレイヤーの生存確認
	DirectX::XMFLOAT2 m_Position;	// プレイヤーの現在地
	DirectX::XMFLOAT2 m_Size;		// プレイヤーのポリゴンサイズ
	DirectX::XMFLOAT2 m_Velocity;	// プレイヤーの移動方向
	float  m_Speed;					// プレイヤーの移動速度
	BULLET_TYPE_ID m_BulletType;	// 現在の使用している弾の種類
	float  m_ShotDelay;				// プレイヤーの弾発射 間隔 計測用
	Circle m_Collision;				// 当たり判定用

public:
	Player();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time);
	void Draw();

	Circle GetCollision();
	void Destroy();

	/* セッター */
	void Speed(float speed) { m_Speed = speed; };

	/* ゲッター */
	bool IsEnable() { return m_Enable; };
	DirectX::XMFLOAT2 GetPosition() { return m_Position; };
	DirectX::XMFLOAT2 GetSize() { return m_Size; };
};


#endif //PLAYER_H