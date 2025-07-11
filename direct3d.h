/*==============================================================================

   Direct3Dの初期化関連 [direct3d.cpp]
														 Author : Youhei Sato
														 Date   : 2025/05/12
--------------------------------------------------------------------------------

==============================================================================*/
#ifndef DIRECT3D_H
#define DIRECT3D_H


#include <Windows.h>
#include <d3d11.h>

// セーフリリースマクロ
#define SAFE_RELEASE(o) if (o) { (o)->Release(); o = NULL; }

bool Direct3D_Initialize(HWND hWnd); // Direct3Dの初期化
void Direct3D_Finalize(); // Direct3Dの終了処理

void Direct3D_Clear(); // バックバッファのクリア
void Direct3D_Present(); // バックバッファの表示

//バックバッファの大きさの取得
unsigned int Direct3D_GetBackBufferWidth();			//幅
unsigned int Direct3D_GetBackBufferHeight();		//高さ

//各種デバイスの取得
ID3D11Device* Direct3D_GetDevice();
ID3D11DeviceContext* Direct3D_GetContext();

#endif // DIRECT3D_H
