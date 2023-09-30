#pragma once
#include "Common.h"

class PressAUI
{
public:
	PressAUI(const char* fileNameTitle, const char* fileNameResult, Pos position);
	~PressAUI();

	void Initialize(bool isTitleUI);

	void Update(float deltaTime);

	void Draw();
private:
	int graphHandle[2];
	int alpha;
	float alphaCount;
	Pos position;
	Size size[2];
	bool isTitleUI;
};