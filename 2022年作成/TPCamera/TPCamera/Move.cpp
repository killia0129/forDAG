#include "Move.h"

VECTOR Move::MovePos(VECTOR pos, float speed, float ang)
{
    return VGet(pos.x + speed * cos(ang * DX_PI), pos.y, pos.z + speed * sin(ang * DX_PI));
}
