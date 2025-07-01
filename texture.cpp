/*������������������������������������������������
��												��
��		�e�N�X�`���\�Ǘ�[texture.cpp]			��
��												��
��������������������������������������������������
��					Author: aki hoeikoshi		��
��					  data: 2025.6.13			��
��												��
������������������������������������������������*/


#include <string>
#include "DirectXTex.h"
using namespace DirectX;
#include "texture.h"
#include "direct3d.h"


static constexpr int TEXTURE_MAX = 256;


struct Texture
{
	std::wstring filename;
	ID3D11ShaderResourceView* pTexture;
	unsigned int width;
	unsigned int height;
};


static Texture g_Textures[TEXTURE_MAX]{};
static int g_SetTextureIndex = -1;
// ���ӁI�������ŊO������ݒ肳�����́BRelease�s�v�B
static ID3D11Device* g_pDevice = nullptr;
static ID3D11DeviceContext* g_pContext = nullptr;


void TextureInitialize(ID3D11Device* pDevice, ID3D11DeviceContext* pDeviceContext)
{
	for (Texture& t : g_Textures)
	{
		t.pTexture = nullptr;
	}

	g_pDevice = pDevice;
	g_pContext = pDeviceContext;
}

void TextureFinalize()
{
	TextureAllRelease();
}

int TextureLoad(const wchar_t* pFilename)
{
	for (int i = 0; i < TEXTURE_MAX; i++)
	{
		// ���ɓǂݍ���ł���t�@�C���͓ǂݍ��܂Ȃ�
		// �ǂݍ���ł������ꍇ�ɂ͓����Ǘ��ԍ���Ԃ�
		for (int j = 0; j < TEXTURE_MAX; j++)
		{
			if (g_Textures[j].filename == pFilename)
			{
				return i;
			}
		}

		//�󂢂Ă���Ǘ��̈��T��
		if (g_Textures[i].pTexture) continue;		//�g�p��

		//�e�N�X�`���ǂݍ���
		TexMetadata metadata;
		ScratchImage image;

		HRESULT hr = LoadFromWICFile(pFilename, WIC_FLAGS_NONE, &metadata, image);
		if (FAILED(hr))
		{
			MessageBoxW(nullptr, L"�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", pFilename, MB_OK);
			return -1;
		}

		g_Textures[i].filename = pFilename;
		g_Textures[i].width  = (unsigned int)metadata.width;
		g_Textures[i].height = (unsigned int)metadata.height;

		hr = CreateShaderResourceView(g_pDevice, image.GetImages(), image.GetImageCount(), metadata, &g_Textures[i].pTexture);
		
		return i;
	}
	return -1;
}

void TextureAllRelease()
{
	for (Texture& t : g_Textures)
	{
		t.filename.clear();
		SAFE_RELEASE(t.pTexture);
	}
}

void TextureSetTexture(int texid)
{
	if (texid < 0) return;
	
	//if (g_SetTextureIndex == texid) return;
	
	g_SetTextureIndex = texid;
	
	//�@�e�N�X�`���ݒ�
	g_pContext->PSSetShaderResources(0, 1, &g_Textures[texid].pTexture);
}

unsigned int GetTextureWidth(int texid)
{
	if (texid < 0) return 0;
	return g_Textures[texid].width;
}

unsigned int GetTextureHeight(int texid)
{
	if (texid < 0) return 0;
	return g_Textures[texid].height;
}
