/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�e�̍쐬[gun.h]										��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.9				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef GUN_H
#define GUN_H


#include <DirectXMath.h>
#include "bullet.h"


class Gun
{
private:
	/* �����o�ϐ��錾 */
	int m_Texid;
	DirectX::XMFLOAT2 m_Position;
	DirectX::XMFLOAT2 m_Size;
	Circle m_Collision;

public:
	Gun();
	void Initialize();
	void Finalize();
	void Update(double elapsed_time, BULLET_TYPE_ID bullet_type);
	void Draw(BULLET_TYPE_ID bullet_type);

	void Shot(BULLET_TYPE_ID type, const DirectX::XMFLOAT2& position);
};

#endif //GUN_H