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

class Player
{
private:
	/* 定数定義 */
	static constexpr float PLAYER_SPEED = 0.5f;			// プレイヤー移動速度
	static constexpr float SHOTDELAY = 0.1f;			// 弾の発射間隔

	/* メンバ変数宣言 */
	int m_PlayerTexid;				// プレイヤーのテクスチャ管理ID
	DirectX::XMFLOAT2 m_PlayerPos;			// プレイヤーの現在地
	DirectX::XMFLOAT2 m_PlayerSize;			// プレイヤーのポリゴンサイズ
	DirectX::XMFLOAT2 m_PlayerVelocity;		// プレイヤーの移動方向
	float m_Speed;					// プレイヤーのスピード
	float m_ShotDelay;				// プレイヤーの弾発射 間隔 計測用

public:
	Player();
	void PlayerInitialize();
	void PlayerFinalize();
	void PlayerUpdate(double elapsed_time);
	void PlayerDraw();
};
//void PlayerInitialize(const DirectX::XMFLOAT2& playerpos);
//void PlayerFinalize();
//void PlayerUpdate(double elapsed_time);
//void PlayerDraw();


#endif //PLAYER_H