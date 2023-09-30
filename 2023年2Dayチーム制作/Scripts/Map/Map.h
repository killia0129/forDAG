#pragma once
#include<vector>
#include"DxLib.h"
#include"Star.h"

class Map
{
public:
	Map();
	virtual ~Map();

	void Update(float deltaTime);
	void Draw();
	void SetSpeed(float _speed);
	void Initialize();
	void DrawBeach();
	void DrawWaterSprash();
	void SprashUpdate(float deltaTime);
	bool GetSprashEndFlag() { return sprashEndFlag; }

private:
	struct POS
	{
		float x, y;
	};

	POS normalImagePos[3];
	POS normalSeaImagePos[3];
	POS darkerImagePos[3];
	POS UFOPos;
	float UFOrad;
	int UFOImage;
	int normalImage[3];
	int normalSeaImage[3];
	int darkerImage[3];
	int sunahamImage;
	int sprashImage;
	float alpha;
	float time;
	float speed;
	float speedRatio;
	float addStarTimer;
	float UFODis;

	bool downFlag;
	float maxTime;
	float downStartTime;
	float waterY;
	bool sprashEndFlag;

	std::vector<Star*>stars;

	int colorScreen;
	int downScaleScreen;
	int gaussScreen;

	bool sprashDownFlag = false;

	const float NORMAL_TIME = 1.5f;
	const float DARKER_TIME = 3.f;
	const int IMAGE_WIDTH = 1920;
	const int IMAGE_HEIGHT = 1080;
	const float DARKER_MIN_SPEED = 100.f;
	const float SPACE_MIN_SPEED = 200.f;
	const float MAX_SPEED = 500.f;
	const float MAX_TIME = 10.f;
};

