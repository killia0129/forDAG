#pragma once

#include "Common.h"

class Shark
{
public:
	Shark();
	~Shark();
	void Update(float deltaTime);
	void UpdatePlayerRound(float deltaTime);
	void UpdateTurn(float deltaTime);
	void UpdateSharkRound(float deltaTime);
	void Draw();
	
	void InitSharkRound();
	void Init();

	void SetplayerAngle(const float playerAngle)
	{
		this->playerAngle = playerAngle;
	}

	void SetScore(const float score)
	{
		this->score = score;
	}

	void SetisThrow(const float isThrow)
	{
		this->isThrow = isThrow;
	}

	bool GetEndFlag() const
	{
		return endFlag;
	}

	bool GetisLandsOnWater() const
	{
		return isLandsOnWater;
	}
private:
	enum StateType
	{
		PlayerRound,
		Turn,
		SharkRound,
		End
	};

	enum Mode
	{
		Up,
		Stay,
		Down
	};

	

	void InitTurn();

	void ModeChange(Mode mode);
	

	float x;
	float y;

	int image;
	float imageAngle;
	const double sharkMagnification = 0.3;

	float flyY;
	float iangle;	//イメージのアングルのラジアン
	const float playerX = SCREEN_WIDTH / 6;
	const float playerY = SCREEN_HEIGHT / 2;
	const float playerSize = 250;
	float playerAngle;
	bool isThrow;	//投げたかどうか
	float score;
	const float maxScore = 500.0f;
	const float maxTime = 10;
	float upTime;
	float stayTime;
	float downTime;
	
	StateType stateType;
	Mode mode;

	int effectImg[18];
	const int effectXSize = 750;
	const int effectYSize = 500;
	const int effectXNum = 6;
	const int effectYNum = 3;
	const double effectMagnification = 2.5;
	float effectAngle;	//エフェクトのアングル
	float eAngle;	//エフェクトのアングルのラジアン
	float eAValue; //エフェアングルの調整値
	int effectHandle;

	bool endFlag;
	bool isLandsOnWater;
};