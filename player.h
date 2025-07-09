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
#include "bullet.h"

class Player
{
private:
	/* �萔��` */
	static constexpr float PLAYER_SPEED = 0.5f;			// �v���C���[�ړ����x
	static constexpr float SHOTDELAY = 0.1f;			// �e�̔��ˊԊu

	/* �����o�ϐ��錾 */
	int  m_Texid;					// �v���C���[�̃e�N�X�`���Ǘ�ID
	int  m_SoundId;					// �v���C���[���S���̃T�E���hID
	bool m_Enable;					// �v���C���[�̐����m�F
	DirectX::XMFLOAT2 m_Position;	// �v���C���[�̌��ݒn
	DirectX::XMFLOAT2 m_Size;		// �v���C���[�̃|���S���T�C�Y
	DirectX::XMFLOAT2 m_Velocity;	// �v���C���[�̈ړ�����
	float  m_Speed;					// �v���C���[�̈ړ����x
	BULLET_TYPE_ID m_BulletType;	// ���݂̎g�p���Ă���e�̎��
	float  m_ShotDelay;				// �v���C���[�̒e���� �Ԋu �v���p
	Circle m_Collision;				// �����蔻��p

public:
	Player();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time);
	void Draw();

	Circle GetCollision();
	void Destroy();

	/* �Z�b�^�[ */
	void Speed(float speed) { m_Speed = speed; };

	/* �Q�b�^�[ */
	bool IsEnable() { return m_Enable; };
	DirectX::XMFLOAT2 GetPosition() { return m_Position; };
	DirectX::XMFLOAT2 GetSize() { return m_Size; };
};


#endif //PLAYER_H