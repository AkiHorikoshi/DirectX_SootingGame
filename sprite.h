/*================================================

		�X�v���C�g�\��[sprite.h]

					Author: aki hoeikoshi
					  data: 2025.6.12

================================================*/
#ifndef SPRITE_H
#define SPRITE_H

#include <d3d11.h>
#include <DirectXMath.h>

void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext);
void Sprite_Finalize(void);
void Sprite_Begin();
void Sprite_Updata(void);
// �e�N�X�`���S�\��
// ���� : �e�N�X�`��ID  �|���S�����゘  �|���S������y  ���_�J���[(�f�t�H���g��)
void Sprite_Draw(int texid, const DirectX::XMFLOAT2& dPos, const DirectX::XMFLOAT4& color = {1.0f, 1.0f, 1.0f, 1.0f});

// �e�N�X�`���S�\�� �T�C�Y�ύX��
// ���� : �e�N�X�`��ID  �|���S�����゘  �|���S������y  �|���S��wigth  �|���S��height  ���_�J���[(�f�t�H���g��)
void Sprite_Draw(int texid, const DirectX::XMFLOAT2& dPos, const DirectX::XMFLOAT2& dSize, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

//// UV�J�b�g
//// ���� : �e�N�X�`��ID  �|���S�����゘  �|���S������y�@UV���W����x  UV���W����y   UV�T�C�Ywigth  UV�T�C�Yheight  ���_�J���[(�f�t�H���g��)
//void Sprite_Draw(int texid, float dx, float dy, int tx, int ty, int tw, int th, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

// UV�J�b�g  �T�C�Y�ύX��
// ���� : �e�N�X�`��ID  �|���S�����゘  �|���S������y  �|���S��wigth  �|���S��height�@UV���W����x  UV���W����y   UV�T�C�Ywigth  UV�T�C�Yheight  ���_�J���[(�f�t�H���g��)
void Sprite_Draw(int texid, const DirectX::XMFLOAT2& dPos, const DirectX::XMFLOAT2& dSize, const DirectX::XMUINT2& pPos, const DirectX::XMUINT2& pSize, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

// UV�J�b�g  �T�C�Y�ύX�� ��]��
// ���� : �e�N�X�`��ID  �|���S�����゘  �|���S������y  �|���S��wigth  �|���S��height�@UV���W����x  UV���W����y   UV�T�C�Ywigth  UV�T�C�Yheight  ��]�ʁ@���_�J���[(�f�t�H���g��)
void Sprite_Draw(int texid, const DirectX::XMFLOAT2& dPos, const DirectX::XMFLOAT2& dSize, const DirectX::XMUINT2& pPos, const DirectX::XMUINT2& pSize, float angle, const DirectX::XMFLOAT4& color = { 1.0f, 1.0f, 1.0f, 1.0f });

#endif //SPRITE_H