/*==============================================================================

	�X�v���C�g�`�� [sprite.cpp]
														 Author : Youhei Sato
														 Date   : 2025/05/15
--------------------------------------------------------------------------------

==============================================================================*/
#include <d3d11.h>
#include <DirectXMath.h>
using namespace DirectX;
#include "direct3d.h"
#include "shader.h"
#include "debug_ostream.h"
#include "sprite.h"
#include "texture.h"

static constexpr int NUM_VERTEX = 4; // ���_��


static ID3D11Buffer* g_pVertexBuffer = nullptr; // ���_�o�b�t�@
static ID3D11ShaderResourceView* g_pTexture = nullptr; //�e�N�X�`��

// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


// ���_�\����
struct Vertex
{
	XMFLOAT3 position; // ���_���W
	XMFLOAT4 color;	   //���_�J���[
	XMFLOAT2 texcoord; //�e�N�X�`�����W
};


void Sprite_Initialize(ID3D11Device* pDevice, ID3D11DeviceContext* pContext)
{
	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̃`�F�b�N
	if (!pDevice || !pContext) {
		hal::dout << "Polygon_Initialize() : �^����ꂽ�f�o�C�X���R���e�L�X�g���s���ł�" << std::endl;
		return;
	}

	// �f�o�C�X�ƃf�o�C�X�R���e�L�X�g�̕ۑ�
	g_pDevice = pDevice;
	g_pContext = pContext;

	// ���_�o�b�t�@����
	D3D11_BUFFER_DESC bd = {};
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(Vertex) * NUM_VERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	g_pDevice->CreateBuffer(&bd, NULL, &g_pVertexBuffer);
}

void Sprite_Finalize(void)
{
	SAFE_RELEASE(g_pTexture);
	SAFE_RELEASE(g_pVertexBuffer);
}

void Sprite_Begin()
{
	// ���_������������
	const float SCREEN_WIDTH = (float)Direct3D_GetBackBufferWidth();
	const float SCREEN_HEIGHT = (float)Direct3D_GetBackBufferHeight();

	// ���_�V�F�[�_�[�ɕϊ��s���ݒ�
	Shader_SetProjectionMatrix(XMMatrixOrthographicOffCenterLH(0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 0.0f, 0.0f, 1.0f));
}

void Sprite_Updata()
{
}

void Sprite_Draw(int texid, const XMFLOAT2& dPos, const XMFLOAT4& color)
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	unsigned int dw = GetTextureWidth(texid);
	unsigned int dh = GetTextureHeight(texid);

	// �|���S�����_
	v[0].position = { dPos.x     , dPos.y     , 0.0f };
	v[1].position = { dPos.x + dw, dPos.y     , 0.0f };
	v[2].position = { dPos.x     , dPos.y + dh, 0.0f };
	v[3].position = { dPos.x + dw, dPos.y + dh, 0.0f };

	//���_�J���[
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	// uv���W
	v[0].texcoord = { 0.0f, 0.0f };
	v[1].texcoord = { 1.0f, 0.0f };
	v[2].texcoord = { 0.0f, 1.0f };
	v[3].texcoord = { 1.0f, 1.0f };

	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���[���h�ϊ��s���ݒ�
	Shader_SetWorldMatrix(XMMatrixIdentity());

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���̐ݒ�
	TextureSetTexture(texid);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(NUM_VERTEX, 0);
}
							
void Sprite_Draw(int texid, const XMFLOAT2& dPos, const XMFLOAT2& dSize, const XMFLOAT4& color)
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// �|���S�����_
	v[0].position = { dPos.x          , dPos.y          , 0.0f };
	v[1].position = { dPos.x + dSize.x, dPos.y          , 0.0f };
	v[2].position = { dPos.x          , dPos.y + dSize.y, 0.0f };
	v[3].position = { dPos.x + dSize.y, dPos.y + dSize.y, 0.0f };

	//���_�J���[
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	// uv���W
	v[0].texcoord = { 0.0f, 0.0f };
	v[1].texcoord = { 1.0f, 0.0f };
	v[2].texcoord = { 0.0f, 1.0f };
	v[3].texcoord = { 1.0f, 1.0f };

	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���[���h�ϊ��s���ݒ�
	Shader_SetWorldMatrix(XMMatrixIdentity());

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���̐ݒ�
	TextureSetTexture(texid);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(NUM_VERTEX, 0);
}

//// tw th�͂���?
//void Sprite_Draw(int texid, float dx, float dy, float tx, float, float tw, float th, const XMFLOAT4& color)
//{
//	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
//	Shader_Begin();
//
//	// ���_�o�b�t�@�����b�N����
//	D3D11_MAPPED_SUBRESOURCE msr;
//	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
//
//	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
//	Vertex* v = (Vertex*)msr.pData;
//
//	unsigned int dw = tw;
//	unsigned int dh = th;
//
//	// �|���S�����_
//	v[0].position = { dx     , dy     , 0.0f };
//	v[1].position = { dx + dw, dy     , 0.0f };
//	v[2].position = { dx     , dy + dh, 0.0f };
//	v[3].position = { dx + dw, dy + dh, 0.0f };
//
//	//���_�J���[
//	v[0].color = color;
//	v[1].color = color;
//	v[2].color = color;
//	v[3].color = color;
//
//	float tw = (float)GetTextureWidth(texid);
//	float th = (float)GetTextureHeight(texid);
//
//	float u0 = tx / 512.0f;
//	float v0 = tx / 512.0f;
//	float u1 = tx / 512.0f + tw;
//	float v1 = tx / 512.0f + th;
//
//	// uv���W
//	v[0].texcoord = { u0, v0 };
//	v[1].texcoord = { u1, v0 };
//	v[2].texcoord = { u0, v1 };
//	v[3].texcoord = { u1, v1 };
//
//	// ���_�o�b�t�@�̃��b�N������
//	g_pContext->Unmap(g_pVertexBuffer, 0);
//
// 	// ���[���h�ϊ��s���ݒ�
//  Shader_SetWorldMatrix(XMMatrixIdentity());
// 
//	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
//	UINT stride = sizeof(Vertex);
//	UINT offset = 0;
//	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);
//
//	// �v���~�e�B�u�g�|���W�ݒ�
//	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
//
//	// �e�N�X�`���̐ݒ�
//	TextureSetTexture(texid);
//
//	// �|���S���`�施�ߔ��s
//	g_pContext->Draw(NUM_VERTEX, 0);
//}					

void Sprite_Draw(int texid, const XMFLOAT2& dPos, const XMFLOAT2& dSize, const XMUINT2& pPos, const XMUINT2& pSize, const XMFLOAT4& color)
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// �|���S�����_
	v[0].position = { dPos.x          , dPos.y          , 0.0f };
	v[1].position = { dPos.x + dSize.x, dPos.y          , 0.0f };
	v[2].position = { dPos.x          , dPos.y + dSize.y, 0.0f };
	v[3].position = { dPos.x + dSize.y, dPos.y + dSize.y, 0.0f };

	//���_�J���[
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	float tw = (float)GetTextureWidth(texid);
	float th = (float)GetTextureHeight(texid);

	float u0 = pPos.x / tw;
	float v0 = pPos.y / th;
	float u1 = (pPos.x + pSize.x) / tw;
	float v1 = (pPos.y + pSize.y) / th;

	// uv���W
	v[0].texcoord = { u0, v0 };
	v[1].texcoord = { u1, v0 };
	v[2].texcoord = { u0, v1 };
	v[3].texcoord = { u1, v1 };

	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ���[���h�ϊ��s���ݒ�
	Shader_SetWorldMatrix(XMMatrixIdentity());

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	TextureSetTexture(texid);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(NUM_VERTEX, 0);
}

void Sprite_Draw(int texid, const XMFLOAT2& dPos, const XMFLOAT2& dSize, const XMUINT2& pPos, const XMUINT2& pSize, float angle, const XMFLOAT4& color)
{
	// �V�F�[�_�[��`��p�C�v���C���ɐݒ�
	Shader_Begin();

	// ���_�o�b�t�@�����b�N����
	D3D11_MAPPED_SUBRESOURCE msr;
	g_pContext->Map(g_pVertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);

	// ���_�o�b�t�@�ւ̉��z�|�C���^���擾
	Vertex* v = (Vertex*)msr.pData;

	// �|���S�����_
	v[0].position = { -0.5f, -0.5f, 0.0f };
	v[1].position = {  0.5f, -0.5f, 0.0f };
	v[2].position = { -0.5f,  0.5f, 0.0f };
	v[3].position = {  0.5f,  0.5f, 0.0f };

	//���_�J���[
	v[0].color = color;
	v[1].color = color;
	v[2].color = color;
	v[3].color = color;

	float tw = (float)GetTextureWidth(texid);
	float th = (float)GetTextureHeight(texid);

	float u0 = pPos.x / tw;
	float v0 = pPos.y / th;
	float u1 = (pPos.x + pSize.x) / tw;
	float v1 = (pPos.y + pSize.y) / th;

	// uv���W
	v[0].texcoord = { u0, v0 };
	v[1].texcoord = { u1, v0 };
	v[2].texcoord = { u0, v1 };
	v[3].texcoord = { u1, v1 };

	// ���_�o�b�t�@�̃��b�N������
	g_pContext->Unmap(g_pVertexBuffer, 0);

	// ��]�s����V�F�[�_�[�ɐݒ�
	XMMATRIX scale = XMMatrixScaling(dSize.x, dSize.y, 1.0f);
	XMMATRIX rotation = XMMatrixRotationZ(angle);
	XMMATRIX translation = XMMatrixTranslation(dPos.x + dSize.x * 0.5f, dPos.y + dSize.y * 0.5f, 0.0f);

	Shader_SetWorldMatrix(scale * rotation * translation);

	// ���_�o�b�t�@��`��p�C�v���C���ɐݒ�
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_pContext->IASetVertexBuffers(0, 1, &g_pVertexBuffer, &stride, &offset);

	// �v���~�e�B�u�g�|���W�ݒ�
	g_pContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	// �e�N�X�`���ݒ�
	TextureSetTexture(texid);

	// �|���S���`�施�ߔ��s
	g_pContext->Draw(NUM_VERTEX, 0);
}
