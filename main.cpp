#include <sdkddkver.h>
#define WIN32_LEANAND_MEAN
#include <Windows.h>
#include <sstream>
#include "game_window.h"
#include "direct3d.h"
#include "sprite.h"
#include "shader.h"
#include "texture.h"
#include "sprite_anim.h"
#include "debug_text.h"
#include "system_timer.h"
#include "key_logger.h"
#include <Xinput.h>
#pragma comment(lib, "xinput.lib")
#include "mouse.h"
#include "game.h"


/* メイン */
int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPSTR, _In_ int nCmdShow)
{
	(void)CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

	HWND hWnd = GameWindow_Create(hInstance);

	/*===============================　　初期化　　==================================*/
	SystemTimer_Initialize();
	KeyLoggerInitialize();
	Mouse_Initialize(hWnd);

	Direct3D_Initialize(hWnd);
	Shader_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	TextureInitialize(Direct3D_GetDevice(), Direct3D_GetContext());
	Sprite_Initialize(Direct3D_GetDevice(), Direct3D_GetContext());
	SpriteAnimInitialize();

	// デバッグテキスト用画像読み込み
	hal::DebugText dt(Direct3D_GetDevice(), Direct3D_GetContext(), L"resource/texture/consolab_ascii_512.png", Direct3D_GetBackBufferWidth(), Direct3D_GetBackBufferHeight(), 0.0f, 0.0f, 0, 0, 0.0f, 14.0f);
	

	Mouse_SetVisible(true);		// マウス表示ONOFF;

	GameInitialize();

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);


	/* fps・実行フレーム計測用 */
	double exec_last_time = SystemTimer_GetTime();
	double fps_last_time = exec_last_time;
	double current_time = 0.0;
	ULONG flame_count = 0;
	double fps = 0.0;


	/*====================　　ゲームループ & メッセ―ジループ　　=======================*/
	MSG msg;
	do
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{ // ウィンドウメッセージが来ていたら
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{ // ゲームの処理

			/* fps計測 */
			current_time = SystemTimer_GetTime();
			double elapsed_time = current_time - fps_last_time;

			if (elapsed_time >= 1.0)
			{
				fps = flame_count / elapsed_time;
				fps_last_time = current_time;
				flame_count = 0;
			}

			elapsed_time = current_time - exec_last_time;
			if (elapsed_time >= (1.0 / 60.0))
			{
				exec_last_time = current_time;

				// ゲームの更新
				KeyLoggerUpdate();
				GameUpdate(elapsed_time);
				SpriteAnimUpdate(elapsed_time);


				// ゲームの描画
				Direct3D_Clear();

				Sprite_Begin();

				GameDraw();

#ifdef _DEBUG
				std::stringstream ss;
				ss << "fps:" << fps;
				dt.SetText(ss.str().c_str());
				dt.Draw();
				dt.Clear();
#endif


				Direct3D_Present();


				flame_count++;
			}

		}

	} while (msg.message != WM_QUIT);


	/*===============================　　終了　　==================================*/
	GameFinalize();
	SpriteAnimFinalize();
	Sprite_Finalize();
	TextureFinalize();
	Shader_Finalize();
	Direct3D_Finalize();
	Mouse_Finalize();

	return (int)msg.wParam;
}