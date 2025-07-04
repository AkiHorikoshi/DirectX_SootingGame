/*����������������������������������������������������������������������������������������������������������������������
��															��
��		UI�쐬[user_interface.h]								��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.7.4				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <DirectXMath.h>
#include "game_window.h"


class UI
{
private:
	static constexpr DirectX::XMFLOAT2 TIME_POSITION = { SCREEN_WIDTH - 96.0f, 8.0f };
	static constexpr DirectX::XMFLOAT2 POINT_POSITION = { SCREEN_WIDTH - 96.0f, 8.0f };

	int m_UiTexid;							// UI�Ŏg���e�N�X�`���Ǘ�ID
	double m_Time;							// �o�ߎ���
	DirectX::XMFLOAT2 m_DrawTimePos;		// ���ԕ\���ꏊ
	int m_Pointo;							// �l���|�C���g
	DirectX::XMFLOAT2 m_DrawPointPos;		// �l���|�C���g�\���ꏊ

public:
	UI();
	void UiInitialize();
	void UiFinalize();
	void UiUppdate(double elapsed_time);
	void UiDraw();

	// �|�C���g�������̒l�����Z
	void AddPoint(int point);

	/* �Q�b�^�[ */
	int GetPosint();
};

#endif //USER_INTERFACE_H