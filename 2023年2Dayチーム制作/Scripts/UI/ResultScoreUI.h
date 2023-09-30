#pragma once
#include "Common.h"

class ResultScoreUI
{
public:
	ResultScoreUI(Pos position);
	~ResultScoreUI();

	void Initialize(int score);

	void Draw();

private:
	int font;
	int score;
	Pos position;
};