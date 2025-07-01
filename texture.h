/*================================================

		�e�N�X�`���\�Ǘ�[texture.h]

					Author: aki hoeikoshi
					  data: 2025.6.13

================================================*/

#ifndef TEXTURE_H
#define TEXTURE_H

#include <d3d11.h>

void TextureInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext);
void TextureFinalize();

// �e�N�X�`���摜�̓ǂݍ���
// �߂�l�F�Ǘ��ԍ��B�ǂݍ��߂Ȃ������ꍇ -1
// �����F�t�@�C����
int TextureLoad(const wchar_t* pFilename);

// �e�N�X�`���̑S�J��
// �ʉ������ꂽ����ǂ�
void TextureAllRelease();

// �e�N�X�`���̊Ǘ��ԍ���n���ƒ���t���Ă����
// �����F�e�N�X�`���Ǘ��ԍ�
void TextureSetTexture(int texid);

// �e�N�X�`���̕�
unsigned int GetTextureWidth(int texid);

// �e�N�X�`���̍���
unsigned int GetTextureHeight(int texid);

#endif //TEXTURE_H