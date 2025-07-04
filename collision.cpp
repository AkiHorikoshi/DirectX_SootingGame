/*━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
┃															┃
┃		コリジョン判定[collision.cpp]							┃
┃															┃
┣━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┫
┃							Author: aki hoeikoshi			┃
┃							  data: 2025.7.3				┃
┃															┃
┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━*/

#include "collision.h"
using namespace DirectX;


bool CollisionIsOverlapCircle(const Circle& a, const Circle& b)
{
    // 2つの円の中心座標の差を求める
    float x1 = b.center.x - a.center.x;
    float y1 = b.center.y - a.center.y;
    
    // ２つの円の中心座標の差の2乗 と ２つの円の半径の和の2乗を 比較する。
    return (x1 * x1 + y1 * y1) < ((a.radius + b.radius) * (a.radius + b.radius));

    // 同じ事をDirectXNathを使ってやった場合
    //XMVECTOR ac = XMLoadFloat2(&a.center);
    //XMVECTOR bc = XMLoadFloat2(&b.center);
    //XMVECTOR lensq = XMVector2LengthSq(bc - ac);
    //
    //return XMVectorGetX(lensq) > ((a.radius + b.radius) * (a.radius + b.radius));
}

bool CollisionIsOverlapBox(const Box& a, const Box& b)
{
    float at = a.center.y;
    float ab = a.center.y + a.height;
    float al = a.center.x;
    float ar = a.center.x + a.width;
    float bt = b.center.y;
    float bb = b.center.y + b.height;
    float bl = b.center.x;
    float br = b.center.x + b.width;

    return (at < bb && ab > bt && al < br && ar > bl) ;
}