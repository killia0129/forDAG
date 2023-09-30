#pragma once
#include<vector>
#include"Stage.h"
#include"Meteor.h"
#include"Needle.h"
#include"Player.h"
#include"Aim.h"
#include"Exprosion.h"
#include"Particle.h"
#include"UI.h"
#include"Beam.h"
#include"BossScene.h"
#include"LineEffect.h"
#include"HowToPlay.h"

class PlayScene
{
public:
	PlayScene();
	virtual ~PlayScene();
	float ALL();
	int DeleteCountGetter() { return deleteCount; }

private:
	Stage* stage = new Stage;
	Player* player = new Player();
	Aim* aim = new Aim();
	UI* ui = new UI();
	Beam* beam[4];
	HowToPlay* howTo;
	std::vector<ObstructBase*>obstructs;
	std::vector<Exprosion*>expro;
	std::vector<Particle*>particle;
	std::vector<LineEffect*>lineEff;
	int nowTime;
	int previousTime;
	void Entry();
	void EntryExp(VECTOR _pos);
	void EntryLine();
	void ObsDelete(ObstructBase* deleteObs);
	void ExpDelete(Exprosion* deleteExp);
	void PartDelete(Particle* deletePart);
	void LineDelete(LineEffect* deleteLine);
	VECTOR cell[4][4];
	unsigned int seed;
	float count;
	float obsCool;
	float beamCool;
	float lineCool;
	float deltaTime;
	int deleteCount;
	float time;
	int plusSec;
	int plusSecX;
	int plusSecY;
	
	int fase;
	bool faseMoving;

	int colorScreen;
	int DownScaleScreen;
	int gaussScreen;
	float blinkRad;

	enum FASE
	{
		NORMAL,SETBOSS,BOSS
	};
};

