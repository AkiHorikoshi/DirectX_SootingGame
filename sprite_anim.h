/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		スプラトアニメーション描画[sprite_anim.h]			┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.6.17				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#ifndef SPRITE_ANIM_H
#define SPRITE_ANIM_H


#include <DirectXMath.h>

void SpriteAnimInitialize();
void SpriteAnimFinalize();

void SpriteAnimUpdate(double elapsed_time);
void SpriteAnimDraw(int playid, const DirectX::XMFLOAT2& dPosition, const DirectX::XMFLOAT2& dSize);

int SpriteAnimRefisterPattern(int texId, int pattMax, int hPattMax, double pattSeco, const DirectX::XMUINT2& pattPos, const DirectX::XMUINT2& pattSize, bool isLooped);

int SpriteAnimCreatePlayer(int anim_pattern_id);
void SpriteAnimDestroyPlayer(int index);
bool SpriteAnim_IsStopped(int index);

#endif //SPRITE_ANIM_H