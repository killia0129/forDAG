#include "Object.h"

Object::Object()
{
    deadFlag = false;
}

Object::~Object()
{
}

ObjectType Object::TypeGetter()
{
    return type;
}

bool Object::IsEnd()
{
    return deadFlag;
}

VECTOR Object::PosGetter()
{
    return pos;
}

void Object::GivenDmg(float dmg)
{
    hp -= dmg;
}

void Object::SetDead()
{
    deadFlag = true;
}

void Object::SetPlayerpos(VECTOR pPos)
{
    playerPos = pPos;
}
