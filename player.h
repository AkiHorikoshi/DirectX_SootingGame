/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�v���C���[����[player.h]								��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.27				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef PLAYER_H
#define PLAYER_H


#include <DirectXMath.h>


void PlayerInitialize(const DirectX::XMFLOAT2& playerpos);
void PlayerFinalize();
void PlayerUpdate(double elapsed_time);
void PlayerDraw();


#endif //PLAYER_H