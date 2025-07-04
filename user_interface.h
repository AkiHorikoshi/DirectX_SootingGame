/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		UI作成[user_interface.h]								┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.4				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef USER_INTERFACE_H
#define USER_INTERFACE_H


#include <DirectXMath.h>
#include "game_window.h"


class UI
{
private:
	static constexpr DirectX::XMFLOAT2 TIME_POSITION = { SCREEN_WIDTH - 96.0f, 8.0f };
	static constexpr DirectX::XMFLOAT2 POINT_POSITION = { SCREEN_WIDTH - 96.0f, 8.0f };

	int m_UiTexid;							// UIで使うテクスチャ管理ID
	double m_Time;							// 経過時間
	DirectX::XMFLOAT2 m_DrawTimePos;		// 時間表示場所
	int m_Pointo;							// 獲得ポイント
	DirectX::XMFLOAT2 m_DrawPointPos;		// 獲得ポイント表示場所

public:
	UI();
	void UiInitialize();
	void UiFinalize();
	void UiUppdate(double elapsed_time);
	void UiDraw();

	// ポイントを引数の値分加算
	void AddPoint(int point);

	/* ゲッター */
	int GetPosint();
};

#endif //USER_INTERFACE_H