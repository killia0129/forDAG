#pragma once
#include <DxLib.h>

class Player {
public:

	/// <summary>
	/// コンストラクタ
	/// </summary>
	Player();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 状態の更新
	/// </summary>
	/// <param name="deltaTime">デルタタイム</param>
	void Update(float deltaTime);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// プレイヤーの回転角度
	/// </summary>
	/// <returns></returns>
	float GetRotationRad() const { return playerAngle; }

	/// <summary>
	/// 確定した最終速度 (値固定)
	/// </summary>
	/// <returns></returns>
	float GetVelocity() const { return 300; }

	/// <summary>
	/// ボタンを押したか
	/// </summary>
	/// <returns></returns>
	bool GetIsPushButton() const{ return pushFlg; }
private:

	VECTOR position;		// 座標ベクトル

	VECTOR v1;

	int inputX, inputY;		// パッドのアナログスティック入力

	int prevInputX, prevInputY;

	int graphHandle;		// 画像ハンドル

	int gauseGraph;			// ゲージ画像

	float power;			// 飛ばす力

	float inputAngle;		// スティックの入力角度

	float prevInputAngle;	// 前フレームでの入力角度

	float angleBetween;

	float playerAngle;

	float rotationSum;

	float playerAngleAdd;

	float prevTimer;

	float powerAdd;

	float velocity;

	float angle;

	int timer;

	bool prevFrameInput;	// 前のフレームで入力があったか

	bool isStartTimer;

	bool pushFlg;
	int graphHandle2;
};