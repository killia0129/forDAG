//----------------------------------------
// @file TimeCount.cpp
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// ヘッダーファイルのインクルード
#include "TimeCount.h"

// using宣言
using std::chrono::duration_cast;
using std::chrono::microseconds;
using std::chrono::system_clock;

// コンストラクタ
TimeCount::TimeCount()
{
	isCount = false;
	start = end = system_clock::now();
}

// デストラクタ
TimeCount::~TimeCount()
{
}

// 更新
void TimeCount::Update()
{
	if (isCount)
	{
		end = system_clock::now();
	}
}

// カウントを開始する
void TimeCount::StartCount()
{
	start = end = system_clock::now();
	isCount = true;
}

void TimeCount::RestCount()
{
	isCount = false;
}

bool TimeCount::CheckIsCount()
{
	return isCount;
}


// カウントを確認する
double TimeCount::CheckCount()
{
	// カウントを開始していないとき計算しないようにする
	if (!isCount) { return -1.0; }

	double time = static_cast<double>(duration_cast<microseconds>(end - start).count() / 1000000.0);
	return time;
}
