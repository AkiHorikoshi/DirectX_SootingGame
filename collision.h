/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�R���W��������[collision.h]							��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.3				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef COLLISION_H
#define COLLISION_H


#include <DirectXMath.h>


struct Circle
{
	DirectX::XMFLOAT2 center;		// ����p�̉~�̒��S
	float radius;
};

struct Box
{
	DirectX::XMFLOAT2 center;		// ����p�̎l�p�`�̍���
	float width;
	float height;
};

bool CollisionIsOverlapCircle(const Circle& a, const Circle& b);
bool CollisionIsOverlapBox(const Box& a, const Box& b);
#endif //COLLISION_H