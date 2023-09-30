#include "EnemyBase.h"

const VECTOR firstAheadVec = VGet(1, 0, 0);

EnemyBase::EnemyBase()
{
	pos = ZERO_POS;
	tag = ZERO_I;
	aheadVec = firstAheadVec;
	isLocked = false;
	isAlive = true;
	HP = ZERO_I;
}

EnemyBase::~EnemyBase()
{
}
