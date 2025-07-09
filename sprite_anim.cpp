/*����������������������������������������������������������������������������������������������������������������������
��															��
��		�X�v���g�A�j���[�V�����`��[sprite_anim.cpp]				��
��															��
��������������������������������������������������������������������������������������������������������������������������
��							Author: aki hoeikoshi			��
��							  data: 2025.6.17				��
��															��
����������������������������������������������������������������������������������������������������������������������*/

#include <DirectXMath.h>
using namespace DirectX;
#include "sprite_anim.h"
#include "sprite.h"
#include "texture.h"
#include "game_window.h"


struct AnimPatternData
{
	int m_TextureId = -1;					// �e�N�X�`��ID

	int		 m_PatternMax = 0;				// �p�^�[������
	int		 m_hPatternMax = 0;				// ���ɕ���ł�p�^�[���ő吔
	double   m_SecondsParPatrern = 0.1;		// �P�p�^�[����\�����Ă����b��
	XMUINT2  m_StartPosition{};				// �A�j���[�V�����X�^�[�gX,Y���W
	XMUINT2  m_PatternSize{};				// �P�p�^�[���̕�,����
	bool	 m_IsLooped = true;				// ���[�v�Đ����邩
};

struct AnimPlayData
{
	int		m_PatternId = -1;				// �A�j���[�V�����p�^�[��ID
	int		m_PatternCount = 0;				// ���݂̃p�^�[���ԍ�
	double  m_Accumulated_time = 0;			// �ݐώ���
	bool    m_IsStopped = false;			// �A�j���[�V�������I������
};


static constexpr int ANIM_PATTERN_MAX = 6;
static AnimPatternData g_AnimPattern[ANIM_PATTERN_MAX];
static constexpr int ANIM_PLAY_MAX = 256;
static AnimPlayData g_AnimPlay[ANIM_PLAY_MAX];


void SpriteAnimInitialize()
{
	// �A�j���\�V�����p�^�[���Ǘ������������i���ׂĎg���ĂȂ���Ԃɂ���j
	for (AnimPatternData& data : g_AnimPattern)
	{
		// m_TextureId ���[�P�Ȃ�g���ĂȂ�
		data.m_TextureId = -1;
	}

	for (AnimPlayData& data : g_AnimPlay)
	{
		data.m_PatternId = -1;
		data.m_IsStopped = false;
	}


	/*
	g_AnimPattern[0].m_TextureId = TextureLoad(L"kokosozai.png");
	g_AnimPattern[0].m_PatternMax = 13;
	g_AnimPattern[0].m_StartPosition = {32 * 0, 32 * 0};
	g_AnimPattern[0].m_PatternSize = {32, 32};
	g_AnimPattern[0].m_IsLooped = true;
	g_AnimPlay[0].m_PatternId = 0;
	*/
}

void SpriteAnimFinalize()
{
}

void SpriteAnimUpdate(double elpsed_time)
{
	for (int i = 0; i < ANIM_PLAY_MAX; i++)
	{
		if (g_AnimPlay[i].m_PatternId < 0)
		{
			continue;
		}

		if (g_AnimPlay[i].m_Accumulated_time >= g_AnimPattern[i].m_SecondsParPatrern)
		{
			g_AnimPlay[i].m_PatternCount++;


			if (g_AnimPlay[i].m_PatternCount >= g_AnimPattern[g_AnimPlay[i].m_PatternId].m_PatternMax)
			{
				if (g_AnimPattern[g_AnimPlay[i].m_PatternId].m_IsLooped)
				{
					g_AnimPlay[i].m_PatternCount = 0;
				}
				else
				{
					g_AnimPlay[i].m_PatternCount = g_AnimPattern[g_AnimPlay[i].m_PatternId].m_PatternMax - 1;
				}

				g_AnimPlay[i].m_IsStopped = true;
			}
			g_AnimPlay[i].m_Accumulated_time -= g_AnimPattern[i].m_SecondsParPatrern;

		}

		g_AnimPlay[i].m_Accumulated_time += elpsed_time;
	}
}

void SpriteAnimDraw(int playid, const DirectX::XMFLOAT2& dPosition, const DirectX::XMFLOAT2& dSize)
{
	int a_patt_id = g_AnimPlay[playid].m_PatternId;
	AnimPatternData* pAPattD = &g_AnimPattern[a_patt_id];

	XMUINT2 pPos = { (pAPattD->m_StartPosition.x + pAPattD->m_PatternSize.x * (g_AnimPlay[playid].m_PatternCount % g_AnimPattern[playid].m_hPatternMax)),
					  (pAPattD->m_StartPosition.y + pAPattD->m_PatternSize.y * (g_AnimPlay[playid].m_PatternCount / g_AnimPattern[playid].m_hPatternMax)) };
	XMUINT2 pSize = { pAPattD->m_PatternSize.x, pAPattD->m_PatternSize.y };


	Sprite_Draw(g_AnimPattern[a_patt_id].m_TextureId,
		dPosition,
		dSize,
		pPos,
		pSize);
}

int SpriteAnimRefisterPattern(int texId, int pattMax, int hPattMax, double pattSeco, const DirectX::XMUINT2& pattPos, const DirectX::XMUINT2& pattSize, bool isLooped)
{
	for (int i = 0; i < ANIM_PATTERN_MAX; i++)
	{
		// �󂢂Ă�z���T��
		if (g_AnimPattern[i].m_TextureId >= 0)
		{
			continue;
		}

		g_AnimPattern[i].m_TextureId = texId;
		g_AnimPattern[i].m_PatternMax = pattMax;
		g_AnimPattern[i].m_hPatternMax = hPattMax;
		g_AnimPattern[i].m_SecondsParPatrern = pattSeco;
		g_AnimPattern[i].m_StartPosition = pattPos;
		g_AnimPattern[i].m_PatternSize = pattSize;
		g_AnimPattern[i].m_IsLooped = isLooped;

		return i;
	}

	return -1;
}

int SpriteAnimCreatePlayer(int anim_pattern_id)
{
	for (int i = 0; i < ANIM_PLAY_MAX; i++)
	{
		if (g_AnimPlay[i].m_PatternId >= 0)
		{
			continue;
		}

		g_AnimPlay[i].m_PatternId = anim_pattern_id;
		g_AnimPlay[i].m_Accumulated_time = 0.0;
		g_AnimPlay[i].m_PatternCount = 0;
		g_AnimPlay[i].m_IsStopped = false;

		return i;
	}


	return -1;
}

void SpriteAnimDestroyPlayer(int index)
{
	g_AnimPlay[index].m_PatternId = -1;
}

bool SpriteAnim_IsStopped(int index)
{
	return g_AnimPlay[index].m_IsStopped;
}