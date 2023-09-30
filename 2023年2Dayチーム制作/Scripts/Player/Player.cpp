#include <math.h>

#include "Common.h"
#include "Player.h"
#include "Input/Input.h"

// コンストラクタ
Player::Player()
{
	// 座標の初期化
	position = VGet(SCREEN_WIDTH / 6, SCREEN_HEIGHT / 2, 0);

	// 画像の読み込み
	graphHandle = LoadGraph("Textures/Player/Player.png");

	// ゲージ画像
	gauseGraph = LoadGraph("Textures/Player/Gauge.png");

	graphHandle2 = LoadGraph("Textures/UI/AButton.png");

	// デッドゾーン設定
	SetJoypadDeadZone(DX_INPUT_PAD1, 0.9);
}

// 初期化
void Player::Initialize()
{
	// アナログスティック入力初期化
	inputX = 0;
	inputY = 0;

	// パワー初期化
	power = 0;

	// 角度初期化
	inputAngle = 0;

	angleBetween = 0;

	playerAngle = 0;

	playerAngleAdd = 0;

	rotationSum = 0;

	velocity = 0;

	timer = 10;

	angle=0;

	powerAdd = 0;

	isStartTimer = false;

	prevTimer = 0;

	// フラグ初期化
	prevFrameInput = false;

	pushFlg = false;
}

// 状態の更新
void Player::Update(float deltaTime)
{
	//// スタートタイマーフラグが立っていたら タイマーを開始させる
	//if (isStartTimer)
	//{
	//	// 一秒の経過を判定
	//	if (GetNowCount() - prevTimer >= 1000)
	//	{
	//		// タイマーの減少
	//		timer--;

	//		// タイマー計測のための 前フレームの時間保存
	//		prevTimer = GetNowCount();
	//	}
	//}

	// タイマーが0より下 かつ ボタンが押されていないなら
	if (power>100 && !pushFlg)
	{
		// ボタンが押されたか 
		if (Input::IsPress1P(ButtonID::BUTTON_ID_A))
		{
			pushFlg = true;
		}

		if (pushFlg)
		{
			if (angle >= DX_PI_F / 180 * 82.5 &&
				angle <= DX_PI_F / 180 * 97.5)
				powerAdd = 2;
			else if (angle >= DX_PI_F / 180 * 55 &&
				angle <= DX_PI_F / 180 * 125)
				powerAdd = 1.5;
			else if (angle >= DX_PI_F / 180 * 22.5 &&
				angle <= DX_PI_F / 180 * 157.5)
				powerAdd = 1;

			velocity = power * powerAdd;
		}
	}

	float x = acos(playerAngle);
	float y = asin(playerAngle);

	if (timer >= 0)
	{

		// ゲームパッドのアナログスティックの入力量を取得
		GetJoypadAnalogInput(&inputX, &inputY, DX_INPUT_PAD1);

		// スティックの入力から角度を算出
		inputAngle = atan2(inputY, inputX);

		// スティックの角度を 0 ~ 2π にする
		if (inputAngle < 0)
		{
			inputAngle = DX_PI_F * 2 + inputAngle;
		}

		// 前フレーム で スティックを入力しているなら 前のフレームとの 角度の差 を出す
		if (prevFrameInput)
		{
			// 前フレーム と 現在のフレーム の 角度の差の絶対値 を 求める
			angleBetween = fabs(prevInputAngle - inputAngle);
		}
		// 前フレームでの入力がなければ差は 0 とする
		else
		{
			angleBetween = 0.0;
		}

		// 角度の差の絶対値が 0 なら 入力無し として パワー と 回転合計量 を 減らす
		if (fabs(angleBetween) == 0.0)
		{
			// パワーがあるなら減らす
			if (power > 0) {
				// パワー減衰
				power -= 0.1;

				// 回転合計量 減衰 
				rotationSum -= (rotationSum / fabs(rotationSum))*0.1;
			}
			// パワーがないなら 0 にセット
			else {

				// パワーリセット
				power = 0;

				// 回転合計量 リセット
				rotationSum = 0;
			}

		}

		// 前フレームで、入力があったなら、前フレームの角度と現在フレームの角度とのなす角を、内積で求める
		if (prevFrameInput)
		{
			v1 = VTransform(VNorm(VGet(prevInputX, prevInputY, 0)), MGetRotZ(DX_PI_F / 2));
			VECTOR v2 = VNorm(VGet(inputX, inputY, 0));
			angleBetween = VDot(v1, v2) / (VSize(v1) * VSize(v2));
		}
		else
		{
			angleBetween = 0.0f;
		}

		if (prevFrameInput && angleBetween != 0.0f)
		{
			rotationSum += angleBetween;
			power = fabs(rotationSum);
		}

		playerAngle += DX_PI_F / 180 * (rotationSum / 10);

		if (fabs(inputX) + fabs(inputY) > 0)
		{
			prevFrameInput = true;
			prevInputAngle = inputAngle;
			prevInputX = inputX;
			prevInputY = inputY;

			if (!isStartTimer)
			{
				isStartTimer = true;
				prevTimer = GetNowCount();
			}
		}
		else
		{
			prevFrameInput = false;
		}
	}
}

void Player::Draw()
{
	DrawRotaGraph(position.x, position.y, 0.5, playerAngle, graphHandle, TRUE);

	if (power>100)
	{
		DrawGraph(position.x, position.y - 128, gauseGraph, TRUE);
		DrawGraph(position.x + 150, position.y - 200, graphHandle2, TRUE);

	}

	//VECTOR rotationVector = VTransform(VGet(0, 50, 0), MGetRotZ(playerAngle));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(255, 255, 255));
	//rotationVector = VTransform(VGet(100, 0, 0), MGetRotZ(DX_PI_F / 180.0 * 7.5));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(255, 255, 0));
	//rotationVector = VTransform(VGet(100, 0, 0), MGetRotZ(-DX_PI_F / 180.0 * 7.5));
	//DrawLine(position.x, position.y, position.x + rotationVector.x, position.y + rotationVector.y, GetColor(0, 255, 0));


	/*printfDx("\nTimer : %d", timer);
	printfDx("\nplayerAngle %f", playerAngle);
	printfDx("\nangle %f", angle);*/
	//printfDx("X %d Y %d", inputX, inputY);
	//printfDx("\nangle %f", inputAngle);
	//printfDx("\nangleBetween %f", angleBetween);
	/*printfDx("\npower %f", power);
	printfDx("\npowerAdd %f", powerAdd);
	printfDx("\nvelocity %f", velocity);*/
	//printfDx("\nprevFrameInput %s", prevFrameInput ? "true" : "false");
}

