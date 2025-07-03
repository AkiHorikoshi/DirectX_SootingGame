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

class Player
{
private:
	/* �萔��` */
	static constexpr float PLAYER_SPEED = 0.5f;			// �v���C���[�ړ����x
	static constexpr float SHOTDELAY = 0.1f;			// �e�̔��ˊԊu

	/* �����o�ϐ��錾 */
	int m_PlayerTexid;				// �v���C���[�̃e�N�X�`���Ǘ�ID
	DirectX::XMFLOAT2 m_PlayerPos;			// �v���C���[�̌��ݒn
	DirectX::XMFLOAT2 m_PlayerSize;			// �v���C���[�̃|���S���T�C�Y
	DirectX::XMFLOAT2 m_PlayerVelocity;		// �v���C���[�̈ړ�����
	float m_Speed;					// �v���C���[�̃X�s�[�h
	float m_ShotDelay;				// �v���C���[�̒e���� �Ԋu �v���p

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