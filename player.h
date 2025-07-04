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


class Player
{
private:
	/* 定数定義 */
	static constexpr float PLAYER_SPEED = 0.5f;			// プレイヤー移動速度
	static constexpr float SHOTDELAY = 0.3f;			// 弾の発射間隔

	/* メンバ変数宣言 */
	int m_Texid;						// プレイヤーのテクスチャ管理ID
	DirectX::XMFLOAT2 m_Position;		// プレイヤーの現在地
	DirectX::XMFLOAT2 m_Size;			// プレイヤーのポリゴンサイズ
	DirectX::XMFLOAT2 m_Velocity;		// プレイヤーの移動方向
	float m_Speed;						// プレイヤーの移動速度
	float m_ShotDelay;					// プレイヤーの弾発射 間隔 計測用
	Circle m_Collision;					// 当たり判定用
	bool m_Enable;						// プレイヤーの生存確認

public:
	Player();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time);
	void Draw();

	bool IsEnable();
	Circle GetCollision();
	void Destroy();

	/* セッター */
	void Speed(float speed);

	/* ゲッター */
	DirectX::XMFLOAT2 GetPosition();
	DirectX::XMFLOAT2 GetSize();
};


#endif //PLAYER_H