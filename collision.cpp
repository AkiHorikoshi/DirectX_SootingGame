/*„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„­
„«															„«
„«		ƒRƒŠƒWƒ‡ƒ“”»’è[collision.cpp]							„«
„«															„«
„°„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„²
„«							Author: aki hoeikoshi			„«
„«							  data: 2025.7.3				„«
„«															„«
„¯„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª„ª*/

#include "collision.h"
using namespace DirectX;


bool CollisionIsOverlapCircle(const Circle& a, const Circle& b)
{
    // 2‚Â‚Ì‰~‚Ì’†SÀ•W‚Ì·‚ð‹‚ß‚é
    float x1 = b.center.x - a.center.x;
    float y1 = b.center.y - a.center.y;
    
    // ‚Q‚Â‚Ì‰~‚Ì’†SÀ•W‚Ì·‚Ì2æ ‚Æ ‚Q‚Â‚Ì‰~‚Ì”¼Œa‚Ì˜a‚Ì2æ‚ð ”äŠr‚·‚éB
    return (x1 * x1 + y1 * y1) > ((a.radius + b.radius) * (a.radius + b.radius));

    // “¯‚¶Ž–‚ðDirectXNath‚ðŽg‚Á‚Ä‚â‚Á‚½ê‡
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