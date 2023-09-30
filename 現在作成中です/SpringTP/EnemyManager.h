#pragma once
#include<vector>
#include"DxLib.h"
#include"Meteor.h"
#include"Needle.h"
class EnemyManager
{
public:
	EnemyManager();
	virtual ~EnemyManager();
	void Update(float deltaTime);

private:
	std::vector<EnemyBase*> enemy;
	float spawnTimer;
	void Entry();
	void Delete();
};

