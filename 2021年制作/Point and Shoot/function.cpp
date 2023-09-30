#include<math.h>
#include"DxLib.h"

int collision(double px, double py, int pr, int ex, int ey, int er)
{
	if (sqrt(((px - ex) * (px - ex)) + (py - ey) * (py - ey)) < (pr + er))
	{
		return 1;
	}
	else
	{
		return 0;
	}
}