#include "ObstructBase.h"


void ObstructBase::ColorCanger()
{
	redColorValue = MaxColorValue * (1 - (hp / maxHp));//HP�̊������Ԃ𑝉�
	color = GetColor(redColorValue, MaxColorValue - redColorValue, 0);
}
