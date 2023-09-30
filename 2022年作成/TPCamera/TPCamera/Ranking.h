#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include"DxLib.h"
class Ranking
{
public:
	Ranking();
	virtual ~Ranking();
	void CheckRanking(float score);
	void saveRanking();
	void Draw();

private:
	std::fstream rankingTxt;
	std::fstream saveTxt;
	float rankingF[10] = { 0 };
	std::string rankingS[10];
};

