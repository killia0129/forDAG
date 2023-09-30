//----------------------------------------
// @file StopWatch.h
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_11_04
//----------------------------------------

// 多重インクルード防止
#pragma once
// ヘッダーファイルのインクルード
#include <time.h>

/// <summary>
/// 時間をはかるクラス
/// </summary>
class StopWatch
{
public:
	// 初期化
	void Initialize();

	// 更新
	void Update();

	// カウントを開始する
	void StartCount();

	// 停止
	void StopCount();

	// リセット
	void ResetCount();

	// カウントを確認する
	double GetSeconds();

private:
	clock_t begin; // カウントを開始した時間
	clock_t elapsed; // 経過時間
	clock_t stopTime; // 止まった時間
	clock_t end; // 今の計測した時間

	bool isRunning; // カウントをするか否か
};