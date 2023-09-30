#pragma once
#include<math.h>
#include"DxLib.h"
class Star
{
public:
	Star();
	virtual ~Star();
	void Update(float deltaTime);
	void Draw(float _alpha);
	bool IsEnd() { return deadFlag; }

private:
	float x;
	float y;
	float r;
	float biggerRRatio;
	float rad;
	float speedRatio;
	bool deadFlag;
};

