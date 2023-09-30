#pragma once

class ScoreDraw {
private:
	int fontHandle;
	float score;
public:
	ScoreDraw();
	~ScoreDraw();
	void Initialize();
	void Update();
	void Draw();
	float GetScore() const
	{
		return score;
	}
};