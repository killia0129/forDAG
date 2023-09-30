#pragma once
#include"DxLib.h"

//シーン名
enum GameScenes
{
	TITLE,GAME,CLEAR,OVER,END
};

//オブジェクト名
enum ObjectType
{
	NEEDLE,METEOR,PLAYER,PLAYER_BEAM,BACK_GROUND,BOSS,TUTORIAL,EXPROSION
};

const int MaxAlphaRatio = 255;
const int MaxColorRatio = 255;
const float MaxRad = 2.f;
const int HalfRad = 1.f;
const float StageWidth = 40.f;