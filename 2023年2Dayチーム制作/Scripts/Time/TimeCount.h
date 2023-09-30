//----------------------------------------
// @file TimeCount.h
// @brief 時間を計測する
// @author shiihara_kiyosumi
// @date 2022_09_01
//----------------------------------------

// 多重インクルード防止
#pragma once
// ヘッダーファイルのインクルード
#include <chrono>

// using宣言
using std::chrono::system_clock;

/// <summary>
/// カウントダウンクラス
/// </summary>
class TimeCount
{
public:
	// コンストラクタ
	TimeCount();
	// デストラクタ
	~TimeCount();

	// 更新
	void Update();

	// カウントを開始する
	void StartCount();

	// 休憩
	void RestCount();

	bool CheckIsCount();

	// カウントを確認する
	double CheckCount();

private:
	system_clock::time_point start; // カウントを開始した時間
	system_clock::time_point end; // 今のカウント時間

	bool isCount; // カウントをするか否か
};