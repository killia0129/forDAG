#include "Ranking.h"

Ranking::Ranking()
{
	rankingTxt.open("Ranking/Ranking.txt",std::ios::in);
}

Ranking::~Ranking()
{
}

void Ranking::CheckRanking(float score)
{
	int i = 0;
	while (i < 10)
	{
		std::getline(rankingTxt, rankingS[i]);
		i++;
	}
	rankingTxt.close();

	for (int i = 0; i < 10; i++)
	{
		rankingF[i] = std::stof(rankingS[i]);
	}

	float thisScore = score;
	for (int i = 0; i < 10; i++)
	{
		if (thisScore < rankingF[i])
		{
			float tmp;
			tmp = rankingF[i];
			rankingF[i] = thisScore;
			thisScore = tmp;
		}
	}
}

void Ranking::saveRanking()
{
	saveTxt.open("Ranking/Ranking.txt", std::ios::out);

	for (int i = 0; i < 10; i++)
	{
		saveTxt << std::to_string(rankingF[i]) << std::endl;
	}
	saveTxt.close();
}

void Ranking::Draw()
{
	SetFontSize(60);
	DrawString(1300, 30, "Ranking", GetColor(0, 255, 0));
	SetFontSize(40);
	for (int i = 0; i < 9; i++)
	{
		DrawFormatString(1300, 100 + (40 * i), GetColor( 0, 255, 0), "Rank %d  %f s", i + 1, rankingF[i]);
	}
	DrawFormatString(1300, 100 + (40 * 9), GetColor(0, 255, 0), "Rank %d %f s", 10, rankingF[9]);
}
