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


enum BULLET_TYPE_ID
{
	NORMAL_BULLET,			// 直線
	WAVE_BULLET,			// sinウェーブ
	BULLET_TYPE_MAX
};


void BulletInitialize();
void BulletFinalize();
void BulletUpdate(double elapsed_time);
void BulletDraw();

void ShotBullet(BULLET_TYPE_ID type, const DirectX::XMFLOAT2& position);


#endif  //BULLET_H