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
	m_Time = 999;
	m_DrawTimePos = TIME_POSITION;
	m_Point = 0;
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
	m_Time += -elapsed_time;
}

void UI::UiDraw()
{
	// タイム表示　一桁ずつ表示
	XMUINT2 time[3] = {};
	time[0].x = (int)(m_Time / 100);
	time[1].x = (int)((m_Time - time[0].x * 100) / 10);
	time[2].x = (int)(m_Time - (time[0].x * 100 + time[1].x * 10));

	for (int i = 0; i < 3; i++)
	{
		//if (time[i].x != 0)
		//{
		//	time[i].y = 1;
		//}
		time[i].y = 1;
		Sprite_Draw(m_UiTexid, { m_DrawTimePos.x + 17.0f * i, m_DrawTimePos.y }, { 32.0f, 32.0f }, { 32 * time[i].x, 32 * time[i].y}, {32, 32});
	}

	// タイム表示　一桁ずつ表示
	XMUINT2 point[4] = {};
	point[0].x = m_Point / 1000;
	point[1].x = (m_Point - point[0].x * 1000) / 100;
	point[2].x = (m_Point - point[0].x * 1000 - point[1].x * 100) / 10;
	point[3].x = m_Point - (point[0].x * 1000 + point[1].x * 100 + point[2].x * 10);

	for (int i = 0; i < 4; i++)
	{
		//if (point[i].x != 0)
		//{
		//	point[i].y = 1;
		//}
		point[i].y = 1;
		Sprite_Draw(m_UiTexid, { m_DrawPointPos.x + 17.0f * i, m_DrawPointPos.y + 20.0f }, { 32.0f, 32.0f }, { 32 * point[i].x, 32 * point[i].y }, { 32, 32 });
	}
}

void UI::AddPoint(int point)
{
	m_Point += point;
}

int UI::GetPosint()
{
	return 0;
}
