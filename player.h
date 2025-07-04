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
#include "collision.h"


class Player
{
private:
	/* �萔��` */
	static constexpr float PLAYER_SPEED = 0.5f;			// �v���C���[�ړ����x
	static constexpr float SHOTDELAY = 0.3f;			// �e�̔��ˊԊu

	/* �����o�ϐ��錾 */
	int m_Texid;						// �v���C���[�̃e�N�X�`���Ǘ�ID
	DirectX::XMFLOAT2 m_Position;		// �v���C���[�̌��ݒn
	DirectX::XMFLOAT2 m_Size;			// �v���C���[�̃|���S���T�C�Y
	DirectX::XMFLOAT2 m_Velocity;		// �v���C���[�̈ړ�����
	float m_Speed;						// �v���C���[�̈ړ����x
	float m_ShotDelay;					// �v���C���[�̒e���� �Ԋu �v���p
	Circle m_Collision;					// �����蔻��p
	bool m_Enable;						// �v���C���[�̐����m�F

public:
	Player();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time);
	void Draw();

	bool IsEnable();
	Circle GetCollision();
	void Destroy();

	/* �Z�b�^�[ */
	void Speed(float speed);

	/* �Q�b�^�[ */
	DirectX::XMFLOAT2 GetPosition();
	DirectX::XMFLOAT2 GetSize();
};


#endif //PLAYER_H