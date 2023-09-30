#include "Player.h"
#include"game.h"

const float KeybordSpeedAdjust = 0.01f;

Player::Player()
{
	pos = VGet(0, 0, 30);
	HP = 10;
	for (int i = 0; i < 16; i++)
	{
		prevPos[i] = pos;
	}
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	for (int i = 15; i >= 1; i--)
	{
		prevPos[i] = prevPos[i - 1];
	}
	prevPos[0] = pos;
	int keyInput = input.Input();
	XINPUT_STATE padInput;
	GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
	pos.x += playerSpeed * deltaTime * ((float)padInput.ThumbLX / 32768.0f);
	pos.y += playerSpeed * deltaTime * ((float)padInput.ThumbLY / 32768.0f);

	switch (keyInput)
	{
	case DIR::AHEAD:
		pos.y += playerSpeed * KeybordSpeedAdjust;
		break;

	case DIR::BACK:
		pos.y -= playerSpeed * KeybordSpeedAdjust;
		break;

	case DIR::LEFT:
		pos.x -= playerSpeed * KeybordSpeedAdjust;
		break;

	case DIR::RIGHT:
		pos.x += playerSpeed * KeybordSpeedAdjust;
		break;

	default:
		break;
	}
	if (pos.x < (stageWidth / 2) * (-1)+ playerR)
	{
		pos.x = (stageWidth / 2) * (-1) + playerR;
	}
	if (pos.x > (stageWidth / 2) - playerR)
	{
		pos.x = (stageWidth / 2) - playerR;
	}
	if (pos.y < (stageWidth / 2) * (-1) + playerR)
	{
		pos.y = (stageWidth / 2) * (-1) + playerR;
	}
	if (pos.y > (stageWidth / 2) - playerR)
	{
		pos.y = (stageWidth / 2) - playerR;
	}

	
}

void Player::HPGetter()
{
}

VECTOR Player::posGetter()
{
	return Player::pos;
}

void Player::Draw()
{
	for (int i = 0; i < 16; i++)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, (128 - 8 * i));
		SetDrawPoint(prevPos[i]);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	VECTOR pos1, pos2;
	pos1 = pos;
	pos2 = pos;
	pos1.z += playerSize / 2.0f;
	pos2.z -= playerSize / 2.0f;
	DrawCapsule3D(pos1, pos2, playerR, 4, GetColor(42, 255, 255), GetColor(42, 255, 255), false);
}

void Player::SetDrawPoint(VECTOR _pos)
{
	VECTOR pos1, pos2;
	pos1 = _pos;
	pos2 = _pos;
	pos1.z += playerSize / 2.0f;
	pos2.z -= playerSize / 2.0f;
	DrawCapsule3D(pos1, pos2, playerR, 4, GetColor(10, 10, 128), GetColor(10, 10, 128), false);
}
