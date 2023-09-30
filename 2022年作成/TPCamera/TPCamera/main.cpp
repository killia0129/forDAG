#include<DxLib.h>
#include "PlayScene.h"
#include"TitleScene.h"
#include"Ranking.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ChangeWindowMode(FALSE);

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return -1;	// エラーが起きたら直ちに終了
	}

	// 画面モードのセット
	SetUseLighting(false);
	SetGraphMode(1920, 1080, 32);
	SetDrawScreen(DX_SCREEN_BACK);
	/*SetLightDirection(VGet(0, 0, 1));
	SetLightPosition(VGet(0, 0, -30));*/
	
	bool loop = true;
	float score = -1.0f;
	int redValue = 0, greenValue = 255, blueValue = 0;

	SetCameraNearFar(1.0f, 499.0f);

	//(0,50,0)から(0,58,-20)を見る
	SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));

	//デバッグ用
	
	LPCSTR font = "font/ARCADE.TTF";
	AddFontResourceEx(font, FR_PRIVATE, NULL);
	ChangeFont("Arcade", DX_CHARSET_DEFAULT);

	XINPUT_STATE padInput;

	SetFontSize(40);

	while (loop)
	{
		TitleScene* titleScene = new TitleScene;

		score = titleScene->ALL();
		
		delete titleScene;

		if (score == -2.0f)
		{
			break;
		}
		PlayScene* playScene = new PlayScene();
		score = playScene->ALL();
		int deleted = playScene->DeleteCountGetter();
		if (score == -1.0f)
		{
			break;
		}
		delete playScene;
		GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
		Ranking* ranking = new Ranking();
		if (score > 0.0f)
		{
			ranking->CheckRanking(score);
			ranking->saveRanking();
		}
		while (!CheckHitKey(KEY_INPUT_SPACE))
		{
			ClearDrawScreen();
			GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
			if (score >= 0.0f)
			{
				if (redValue == 0)
				{
					greenValue -= 2;
					blueValue += 2;
					if (greenValue <= 0)
					{
						redValue = 1;
						greenValue = 0;
						blueValue = 254;
					}
				}
				if (greenValue == 0)
				{
					blueValue -= 2;
					redValue += 2;
					if (blueValue <= 0)
					{
						redValue = 254;
						greenValue = 1;
						blueValue = 0;
					}
				}
				if (blueValue == 0)
				{
					redValue -= 2;
					greenValue += 2;
					if (redValue <= 0)
					{
						redValue = 0;
						greenValue = 254;
						blueValue = 1;
					}
				}
				SetFontSize(100);
				DrawFormatString(750, 400, GetColor(redValue, greenValue, blueValue), "CLEAR!");
				DrawFormatString(200, 500, GetColor(0, 255, 0), "TIME : %4.3f seconds", score);
				SetFontSize(50);
				DrawFormatString(650, 600, GetColor(0, 255, 0), "Press A to Retry");
				ranking->Draw();
				SetFontSize(40);
			}

			if (score < 0.0f)
			{
				GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);
				SetFontSize(100);
				DrawFormatString(600, 300, GetColor(0, 255, 0), "GAME OVER!");
				DrawFormatString(250, 500, GetColor(0, 255, 0), " %d Objects Remaining", 30 - deleted);
				SetFontSize(50);
				DrawFormatString(650, 700, GetColor(0, 255, 0), "Press A to Retry");
				SetFontSize(40);
			}

			if (CheckHitKey(KEY_INPUT_ESCAPE))
			{
				loop = false;
				break;
			}
			if (padInput.Buttons[XINPUT_BUTTON_A] != 0)
			{
				break;
			}
			ScreenFlip();
		}
		score = -1.0f;
	}

	



	DxLib_End();
	return 0;
}