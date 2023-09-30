#include "DxLib.h"
#include "Shark.h"
#include "Common.h"
#include <math.h>

Shark::Shark()
{
	image = LoadGraph("Textures/Shark/Shark.png");
	LoadDivGraph("Textures/Shark/effect.png", effectXNum * effectYNum, effectXNum, effectYNum, effectXSize, effectYSize, effectImg);

	Init();
}

void Shark::Init()
{
	x = playerX + cosf(0.0f) * playerSize;
	y = playerY + sinf(0.0f) * playerSize;
	iangle = 0.0f;
	imageAngle = 0;
	effectHandle = 0;
	endFlag = false;
	isThrow = false;
	isLandsOnWater = false;
	stateType = PlayerRound;
}

void Shark::Update(float deltaTime)
{	
	switch (stateType)
	{
	case Shark::PlayerRound:
		UpdatePlayerRound(deltaTime);
		break;
	case Shark::Turn:
		UpdateTurn(deltaTime);
	case Shark::SharkRound:
		UpdateSharkRound(deltaTime);
		break;
	case Shark::End:
		break;
	default:
		break;
	}
}

void Shark::Draw()
{
	if (stateType == SharkRound) //エフェクトはSharkRのみ描画
	{
		DrawRotaGraph3((SCREEN_WIDTH / 2) - 300, y,effectXSize / 2,effectYSize / 2,
			effectMagnification, effectMagnification,eAngle, effectImg[effectHandle], true);
	}

	DrawRotaGraph(x, y, sharkMagnification, iangle, image, true, true);
}

Shark::~Shark()
{
	DeleteGraph(image);
	for (int i = 0; i < effectXNum * effectYNum; i++)
	{
		DeleteGraph(effectImg[i]);
	}
}

void Shark::UpdatePlayerRound(float deltaTime)
{
	//プレイヤーの角度に基づいて回転する(とりあえず仮で設定する)
	/*imageAngle++;
	if (imageAngle == 24)
	{
		imageAngle = 0;//画像の角度(仮)
	}
	iangle = (DX_PI_F / 6) * imageAngle;*/

	iangle = playerAngle;

	//プレイヤーの大きさをもとに画像の表示する位置を補正
	float pxValue = cosf(iangle) * playerSize;
	float pyValue = sinf(iangle) * playerSize;

	x = playerX + pxValue;
	y = playerY + pyValue;

	//プレイヤーが手を話したらサメの初速等を設定する
	if (isThrow)
	{
		InitTurn();
	}
}

void Shark::InitTurn()
{
	stateType = Turn;
}

void Shark::UpdateTurn(float deltaTime)
{
	//回転
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	iangle = (DX_PI_F / 6) * imageAngle;

	//移動
	x += 10;
	y += -7;

	if (x >= SCREEN_WIDTH)
	{
		endFlag = true;
	}
}

void Shark::InitSharkRound()
{
	stateType = SharkRound;
	x = (SCREEN_WIDTH / 2) - 300;
	y = SCREEN_HEIGHT - (SCREEN_HEIGHT / 3);

	//スコアから飛ぶ時間計算
	score = maxScore;
	float allTime = score / maxScore * maxTime;
	if (allTime > 6.0f)
	{
		upTime = 3.0f;
		stayTime = allTime - 6.0f;
		downTime = 3.0f;
	}
	else
	{
		upTime = allTime / 2;
		downTime = allTime - upTime;
	}
	ModeChange(Up);
	effectAngle = -45;
}

void Shark::UpdateSharkRound(float deltaTime)
{
	//モード返還（今は距離で調整）
	switch (mode)
	{
	case Shark::Up:
		upTime -= deltaTime;
		if (upTime <= 0)
		{
			ModeChange(Stay);
		}
		break;
	case Shark::Stay:
		stayTime -= deltaTime;
		if (upTime <= 0)
		{
			ModeChange(Down);
		}
		break;
	case Shark::Down:
		downTime -= deltaTime;
		if (downTime <= 0)
		{
			isLandsOnWater = true;
		}
		break;
	default:
		break;
	}

	//移動
	y += flyY;

	//回転させる
	imageAngle++;
	if (imageAngle == 12)
	{
		imageAngle = 0;
	}
	iangle = (DX_PI_F / 6) * imageAngle;

	//エフェクトの添え字番号を変更
	if (effectHandle == 17)
	{
		effectHandle = 0;
	}
	else
	{
		effectHandle++;
	}

	//エフェクトのアングル調整
	effectAngle += eAValue * deltaTime;

	eAngle = DX_PI_F / 180 * effectAngle;	
}

void Shark::ModeChange(Mode mode)
{
	switch (mode)
	{
	case Shark::Up:
		flyY = -3;
		eAValue = 45 / upTime;
		this->mode = Up;
		break;
	case Shark::Stay:
		flyY = 0.1;
		eAValue = 0;
		this->mode = Stay;
		break;
	case Shark::Down:
		flyY = 3;
		eAValue = 45 / downTime;
		this->mode = Down;
		break;
	default:
		break;
	}
}