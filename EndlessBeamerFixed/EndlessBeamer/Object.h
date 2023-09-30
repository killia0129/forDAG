#pragma once
#include"game.h"
class Object
{
public:
	Object();
	virtual ~Object();
	virtual void Update(float deltaTime) = 0;//毎フレーム呼び出す
	virtual void Draw() = 0;//描画
	ObjectType TypeGetter();//オブジェクトの種類を返す
	bool IsEnd();
	VECTOR PosGetter();
	void GivenDmg(float dmg);
	void SetDead();
	void SetPlayerpos(VECTOR pPos);


protected:
	VECTOR pos;//座標
	ObjectType type;//オブジェクト名
	bool deadFlag;//消去する際にtrue
	float hp;//HP
	VECTOR playerPos;
};

