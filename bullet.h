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
#include "collision.h"


enum BULLET_TYPE_ID
{
	NORMAL_BULLET,			// ����
	WAVE_BULLET,			// sin�E�F�[�u
	MIDDLE_RANGE_BULLET,	// �S���ʒ�����
	BULLET_TYPE_MAX
};


void BulletInitialize();
void BulletFinalize();
void BulletUpdate(double elapsed_time);
void BulletDraw();

void ShotBullet(BULLET_TYPE_ID type, const DirectX::XMFLOAT2& position);

// bool BulletIsEnable(int indx);
// Circle BulletGetCollision(int index);

#endif  //BULLET_H