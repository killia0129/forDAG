//行列はX→Y→Z順でかける
//回転について、軸の方向に左ねじ

#include"DxLib.h"
#include"Camera.h"
#include"SpringBase.h"
#include"Player.h"
#include"Map.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (DxLib_Init()==-1)
	{
		return -1;
	}
	ChangeWindowMode(false);
	SetUseLighting(false);
	SetGraphMode(1920, 1080, 32);
	SetDrawScreen(DX_SCREEN_BACK);
	SetCameraNearFar(1.0f, 499.0f);
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));

	//デバッグ用
	SpringBase* spring = new SpringBase(VGet(0, 0, 0), VGet(0, -1, 0), 30.f, 5.f, 0.0f, 0.0f, 0.0f);
	Camera* camera = new Camera(ZERO_POS);
	Player* player = new Player(ZERO_POS);
	Map* map = new Map;

	while (!CheckHitKey(KEY_INPUT_ESCAPE))
	{
		ClearDrawScreen();
		player->Move(camera->GetPitch(),0.16f);
		camera->Update(0.16f,player->GetPos());
		player->Update(0.16f);
		map->Draw();
		player->Draw();
		ScreenFlip();
	}

	DxLib_End();

	return 0;
}