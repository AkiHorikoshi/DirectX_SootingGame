/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�L�[�{�[�h���͂̋L�^[key_logger.h]						��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.27				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#ifndef KEY_LOGGER_H
#define KEY_LOGGER_H


#include "keyboard.h"


void KeyLoggerInitialize();

void KeyLoggerUpdate();

// �����Ă����true
bool KeyLoggerIsPressed(Keyboard_Keys key);
// �������u�Ԃ���true
bool KeyLoggerIsTrigger(Keyboard_Keys key);
// �������u�Ԃ���true
bool KeyLoggerIsRelease(Keyboard_Keys key);

#endif //KEY_LOGGER_H