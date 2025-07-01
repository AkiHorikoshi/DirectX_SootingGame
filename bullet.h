/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�e�̐���[bullet.h]									��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.1				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef BULLET_H
#define BULLET_H


#include <DirectXMath.h>


void BulletInitialize();
void BulletFinalize();
void BulletUpdate(double elapsed_time);
void BulletDraw();

void ShotBullet(const DirectX::XMFLOAT2& position);


#endif  //BULLET_H