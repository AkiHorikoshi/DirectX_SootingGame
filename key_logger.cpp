/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�L�[�{�[�h���͂̋L�^[key_logger.cpp]					��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.27				��
��															��
����������������������������������������������������������������������������������������������������������������������*/


#include "key_logger.h"


static Keyboard_State g_PrevState{};		// �O�t���[���̃L�[�X�e�[�^�X
static Keyboard_State g_TriggerState{};
static Keyboard_State g_ReleaseState{};



void KeyLoggerInitialize()
{
	Keyboard_Initialize();
}

void KeyLoggerUpdate()
{
	const Keyboard_State* pState = Keyboard_GetState();
	LPBYTE pnow = (LPBYTE)pState;		// ���݂̃L�[�{�[�h�X�e�[�^�X�ۑ�

	LPBYTE pprev = (LPBYTE)&g_PrevState;
	LPBYTE ptri = (LPBYTE)&g_TriggerState;
	LPBYTE prele = (LPBYTE)&g_ReleaseState;

	for (int i = 0; i < sizeof(Keyboard_State); i++)
	{
		// �g���K�[����
		// �O�t���[���͉�����Ă��ȁ@���@���̃t���[���͉�����Ă���
		// �O�@��
		// 0   1 -> 1
		// 1   0 -> 0
		// 1   1 -> 0
		// 0   0 -> 0
		ptri[i] = (pprev[i] ^ pnow[i]) & pnow[i];

		// �����[�X����
		// �O�t���[���͉�����Ă��ȁ@���@���̃t���[���͉�����Ă���
		// �O�@��
		// 0   1 -> 1
		// 1   0 -> 0
		// 1   1 -> 0
		// 0   0 -> 0
		prele[i] = (pprev[i] ^ pnow[i]) & pprev[i];
	}

	g_PrevState = *pState;
}

bool KeyLoggerIsPressed(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key);
}

bool KeyLoggerIsTrigger(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_TriggerState);
}

bool KeyLoggerIsRelease(Keyboard_Keys key)
{
	return Keyboard_IsKeyDown(key, &g_ReleaseState);
}
