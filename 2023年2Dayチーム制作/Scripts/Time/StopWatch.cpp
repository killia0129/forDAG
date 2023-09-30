//----------------------------------------
// @file StopWatch.cpp
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_11_04
//----------------------------------------

// ヘッダーファイルのインクルード
#include "StopWatch.h"

void StopWatch::Initialize()
{
	isRunning = false;
	begin = 0;
	elapsed = 0;
	stopTime = 0;
	end = 0;
}

void StopWatch::Update()
{
	if (isRunning)
	{
		end = clock() + stopTime;
		elapsed = end - begin;
	}
}

void StopWatch::StartCount()
{
	if (isRunning) { return; }
	isRunning = true;
	begin = clock();
	end = clock() + stopTime;
}

void StopWatch::StopCount()
{
	isRunning = false;
	stopTime = elapsed;
}

void StopWatch::ResetCount()
{
	begin = clock();
	end = clock();
	elapsed = 0;
	stopTime = 0;
}

double StopWatch::GetSeconds()
{
	return elapsed / 1000.0;
}
