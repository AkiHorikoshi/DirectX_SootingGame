/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		UI作成[user_interface.cpp]							┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.4				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "user_interface.h"
#include <DirectXMath.h>
using namespace DirectX;
#include "texture.h"
#include "sprite.h"


UI::UI()
{
	m_UiTexid = -1;
	m_Time = 1;
	m_DrawTimePos = TIME_POSITION;
	m_Pointo = 0;
	m_DrawPointPos = POINT_POSITION;
}

void UI::UiInitialize()
{
	m_UiTexid = TextureLoad(L"resource/texture/consolab_ascii_512.png");
}

void UI::UiFinalize()
{
}

void UI::UiUppdate(double elapsed_time)
{
	m_Time += elapsed_time;
}

void UI::UiDraw()
{
	// タイム表示　一桁ずつ表示
	XMUINT2 keta[4] = {};
	keta[0].x = (int)(m_Time / 1000);
	keta[1].x = (int)((m_Time - keta[0].x * 1000) / 100);
	keta[2].x = (int)((m_Time - keta[0].x * 1000 - keta[1].x * 100) / 10);
	keta[3].x = (int)(m_Time - (keta[0].x * 1000 + keta[1].x * 100 + keta[2].x * 10));

	for (int i = 0; i < 4; i++)
	{
		if (keta[i].x != 0)
		{
			keta[i].y = 1;
		}
		Sprite_Draw(m_UiTexid, { m_DrawTimePos.x + 17.0f * i, m_DrawTimePos.y }, { 32.0f, 32.0f }, { 32 * keta[i].x, 32 * keta[i].y}, {32, 32});
	}
}

void UI::AddPoint(int point)
{
	m_Pointo += point;
}

int UI::GetPosint()
{
	return 0;
}
