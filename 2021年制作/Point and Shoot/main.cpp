#include<math.h>
#include "DxLib.h"
#include"function.h"
#define windowSize 1080
#define title 0x00
#define inGame 0x01
#define reset 0x02
const double pV = 8;
const double pSV = 10;
const double mSV = 7;
const double LBSV = 13;
const int roadWidth = 540;
const int pSize = 30;
const int pHP = 30;
const int minionSize = 10;
const int LBSize = 40;
const int wallWidth = 20;
const int wallHeight = 400;
const int ShotSize = 10;
//const int pLaserWidth = 20;
//const int pLaserGage = 60;
const int eLaserHeight = 5;
const int eLaserNoticeHeight = 3;
const int stageWallWidth = 10;
const int stageWallHeight = 500;
const int roadright = 810;
const int roadleft = 271;
const int minionUpTime = 3;
const int minionMoveTime = 3;
const int tarretSize = 100;
const double oneFrame = 1000 / 60;




int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR lpCmdLine, int nCmdShow)
{
	//基本設定
	DxLib_Init();
	ChangeWindowMode(FALSE);
	SetDrawScreen(DX_SCREEN_BACK);
	SetMainWindowText("よけろ");
	SetGraphMode(windowSize, windowSize, 32);
	SetFontSize(42);

	//自機変数
	double px=windowSize/2, py=windowSize-(pSize*2);
	double pVector;
	double pvx = 0, pvy = 0;
	//int lazerGage = pLaserGage;
	int pShotx[20], pShoty[20];
	int pShotFlag[20] = { 0 };
	int pShotCounter = 0;
	int pShotvy = 20;
	int pHitpoint = pHP;
	int pDmgCount = 0;
	int pDmgFlag = 0;

	//ミニオン変数
	int mx[5], my[5];
	int mShotx[5], mShoty[5];
	int mShotFlag[5] = { 0 };
	int mShotvy = 4;
	int mvy = 3;
	int mFlag[5] = { 0 };
	int nextMTime[5] = { 2 * 60,3 * 60,4 * 60,5 * 60,6 * 60 };
	int nextM;
	int mDcount = 0;
	int mHitFlag[5] = { 0 };
	int mShotHitFlag[5] = { 0 };


	//ラスボス
	int LBFlag = 0;
	int LBx, LBy;
	int LBvx = 5, LBvy = 5;
	int LBMode = 0;
	int LBHitPoint = 20;
	int LBtarretx[6]={0}, LBtarrety[6]={0};
	int LBLaserCount = 0;
	int laserFlag[3] = { 0 };
	int laserNum;
	int LBDmgFlag = 0;
	int LBDmgCount = 0;
	int bShotX, bShotY, bShotFlag = 0, bShotBoundCounter = 0, bShotHitFlag = 0;
	double bSvx, bSvy;

	//マウス座標
	int moucex, moucey;
	int mouceClickedx=windowSize / 2, mouceClickedy = windowSize - (pSize * 2);
	int Click;

	//壁用変数
	int swRx = 1050, swRy[4] = { 25,575,-525,-1075 };
	int swLx = 10, swLy[4] = { 25,575,-525,-1075 };

	//その他変数
	int gameCounter = 0;
	int gameMode = title;
	int i, j;
	int gamefase = 0;






	while (1)//メインループ
	{
		ClearDrawScreen();

		if (gameMode == title)
		{
			DrawString(300, 500, "Press SPACE to Start", GetColor(66, 255, 255));
			DrawOval(200, 700, 30, 40, GetColor(255, 255, 255), TRUE);
			DrawBox(200, 700, 150, 640, GetColor(0, 0, 0), TRUE);
			DrawOval(200, 700, 30, 40, GetColor(255, 255, 255), FALSE);
			DrawOval(200, 685, 5, 8, GetColor(255, 255, 255), TRUE);
			DrawString(300, 675, "Click to Set Destination", GetColor(255, 255, 255));
			DrawBox(150, 800, 315, 850, GetColor(255, 255, 255), FALSE);
			DrawString(175, 805, "SPACE", GetColor(255, 255, 255));
			DrawString(385, 805, "SPACE to Shot", GetColor(255, 255, 255));
			if (CheckHitKey(KEY_INPUT_SPACE))gameMode = inGame;
		}
		else if (gameMode == inGame)
		{
			//カウンター関連
			gameCounter++;

			//自機移動
			GetMousePoint(&moucex, &moucey);
			Click = GetMouseInput();

			//~lastboss
			if (gamefase == 0)
			{
				if (Click & MOUSE_INPUT_LEFT)
				{
					mouceClickedx = moucex;
					mouceClickedy = moucey;
					pVector = sqrt(((px - (double)mouceClickedx) * (px - (double)mouceClickedx)) + ((py - (double)mouceClickedy) * (py - (double)mouceClickedy)));
					pvx = ((double)mouceClickedx - px) * (pV / pVector);
					pvy = ((double)mouceClickedy - py) * (pV / pVector);
					//DrawFormatString(10, 10, GetColor(255, 255, 255), "%f/%f/%f/%d/%d/%d", pVector, pvx, pvy, gameCounter, nextMTime[0], my[0]);

				}
				if ((px <= (double)mouceClickedx + 4 && px >= mouceClickedx - 4) && (py <= (double)mouceClickedy + 4 && py >= mouceClickedy - 4))
				{
					pvx = 0;
					pvy = 0;
				}
				px += pvx;
				py += pvy;
				if (px > (roadright - pSize))
				{
					px = roadright - pSize;
					pvx = 0;
					pvy = 0;
				}
				if (px < (roadleft + pSize))
				{
					px = roadleft + pSize;
					pvx = 0;
					pvy = 0;
				}
				if (py < pSize)
				{
					py = pSize;
					pvx = 0;
					pvy = 0;
				}
				if (py > windowSize - pSize)
				{
					py = windowSize - pSize;
					pvx = 0;
					pvy = 0;
				}

				//自機ショット
				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && pShotCounter < 20)
				{
					for (i = 0; i < 20; i++)
					{
						if (pShotFlag[i] == 0)
						{
							pShotx[i] = px - (ShotSize / 2);
							pShoty[i] = py;
							pShotCounter++;
							pShotFlag[i] = 1;
							break;
						}
					}
				}
				for (i = 0; i < 20; i++)
				{
					if (pShotFlag[i] == 1)
					{
						pShoty[i] -= pShotvy;
						if (pShoty[i] < (-1 * ShotSize))
						{
							pShotFlag[i] = 0;
							pShotCounter--;
						}
					}
				}
				//ミニオン出現&処理
				for (i = 0; i < 5; i++)
				{
					if (mFlag[i] == 0 && nextMTime[i] <= gameCounter)
					{
						mx[i] = px - (pSize * 2) + (rand() % (pSize * 4));
						if (mx[i] < roadleft + minionSize)mx[i] = roadleft + minionSize;
						if (mx[i] > roadright - minionSize)mx[i] = roadright - minionSize;
						my[i] = rand() % 300 + 10;
						nextMTime[i] = gameCounter + (60 * (minionMoveTime / 2));
						mFlag[i] = 1;
					}
					else if (mFlag[i] == 1 && nextMTime[i] <= gameCounter)
					{
						mShotFlag[i] = 1;
						mShotx[i] = mx[i] - (ShotSize / 2);
						mShoty[i] = my[i];
						nextMTime[i] = gameCounter + (60 * (minionMoveTime / 2));
						mFlag[i] = 2;
					}
					else if (mFlag[i] == 2 && nextMTime[i] <= gameCounter)
					{
						my[i] += mvy;
					}
					if (mShotFlag[i] == 1)mShoty[i] += mShotvy;
					if (mShoty[i] > windowSize)mShotFlag[i] = 0;
					if (my[i] > windowSize + minionSize && mFlag[i] == 2)
					{
						mFlag[i] = 0;
						mHitFlag[i] = 0;
						mShotHitFlag[i] = 0;
						nextMTime[i] = gameCounter + (minionUpTime * 60);
					}
				}
				//壁
				for (i = 0; i < 4; i++)
				{
					swRy[i] += 2*mvy;
					swLy[i] += 2*mvy;
					if (swRy[i] > 1080)
					{
						swRy[i] = -720;
					}
					if (swLy[i] > 1080)
					{
						swLy[i] = -720;
					}
				}
				if (gameCounter > 1800)
				{
					gamefase = 1;
				}
			}
			//boss
			else if (gamefase == 1)
			{
				//自機移動
				if (Click & MOUSE_INPUT_LEFT)
				{
					mouceClickedx = moucex;
					mouceClickedy = moucey;
					pVector = sqrt(((px - (double)mouceClickedx) * (px - (double)mouceClickedx)) + ((py - (double)mouceClickedy) * (py - (double)mouceClickedy)));
					pvx = ((double)mouceClickedx - px) * (pV / pVector);
					pvy = ((double)mouceClickedy - py) * (pV / pVector);

				}
				if ((px <= (double)mouceClickedx + 4 && px >= mouceClickedx - 4) && (py <= (double)mouceClickedy + 4 && py >= mouceClickedy - 4))
				{
					pvx = 0;
					pvy = 0;
				}
				px += pvx;
				py += pvy;
				if (px > (roadright - pSize))
				{
					px = roadright - pSize;
					pvx = 0;
					pvy = 0;
				}
				if (px < (roadleft + pSize))
				{
					px = roadleft + pSize;
					pvx = 0;
					pvy = 0;
				}
				if (py < pSize)
				{
					py = pSize;
					pvx = 0;
					pvy = 0;
				}
				if (py > windowSize - pSize)
				{
					py = windowSize - pSize;
					pvx = 0;
					pvy = 0;
				}

				//自機ショット
				if (CheckHitKey(KEY_INPUT_SPACE) == 1 && pShotCounter < 20)
				{
					for (i = 0; i < 20; i++)
					{
						if (pShotFlag[i] == 0)
						{
							pShotx[i] = px - (ShotSize / 2);
							pShoty[i] = py;
							pShotCounter++;
							pShotFlag[i] = 1;
							break;
						}
					}
				}
				for (i = 0; i < 20; i++)
				{
					if (pShotFlag[i] == 1)
					{
						pShoty[i] -= pShotvy;
						if (pShoty[i] < (-1 * ShotSize))
						{
							pShotFlag[i] = 0;
							pShotCounter--;
						}
					}
				}
				//ミニオン停止処理
				for (i = 0; i < 5; i++)
				{
					if (my[i] <= windowSize + minionSize)
					{
						my[i] += mvy;
					}
					else if (my[i] >= windowSize + minionSize)
					{
						mFlag[i] = -1;
						mHitFlag[i] = -1;
						mShotHitFlag[i] = -1;
					}
					if (mShotFlag[i] == 1)mShoty[i] += mShotvy;
					if (mShoty[i] > windowSize)mShotFlag[i] = 0;
				}

				//ミニオンがいなくなったか
				if (LBMode == 0)
				{
					for (i = 0; i < 5; i++)
					{
						if (mFlag[i] == 1)
						{
							LBFlag = 0;
						}
						else
						{
							LBFlag++;
						}
						if (LBFlag == 5)
						{
							break;
						}
						else if (i == 4)
						{
							LBFlag = 0;;
						}
					}
				}


				if (LBFlag == 5&&LBMode==0)
				{
					LBMode=1;
					LBx=windowSize/2;
					LBy=-1*LBSize;
				}
				
				if(LBMode==1)
				{
					LBy+=2;
					if(LBy>(LBSize*2)+10)
					{
						LBMode = 2;
					}
				}
				if(LBMode==2)
				{
					for (i = 0; i < 3; i++)
					{
						LBtarretx[i] = roadleft - 10;
						LBtarrety[i] = -10;
					}
					for (i = 3; i < 6; i++)
					{
						LBtarretx[i] = roadright + 10;
						LBtarrety[i] = -10;
					}
					LBMode = 3;
				}
				if (LBMode == 3)
				{
					for (i = 0; i < 6; i++)
					{
						if (LBtarrety[i] + 5 <= 100 + (i % 3) * 400)
						{
							LBtarrety[i] += 5;
						}
					}
					if (LBtarrety[5] == 100 + 2 * 400)
					{
						LBMode = 4;
					}
				}
				if (LBMode == 4)
				{
					LBx += LBvx;
					LBy += LBvy;
					if (LBx<roadleft+LBSize || LBx>roadright-LBSize)LBvx *= -1;
					if (LBy > windowSize-LBSize || LBy < LBSize)LBvy *= -1;

					if (laserFlag[0] == 0 && laserFlag[1] == 0 && laserFlag[2] == 0)
					{
						laserNum = rand() % 3;
						laserFlag[laserNum] = 1;
					}
					for (i = 0; i < 3; i++)
					{
						if (laserFlag[i] == 1)
						{
							LBLaserCount++;
							if (LBLaserCount > 30)
							{
								laserFlag[i] = 2;
							}
						}
						if (laserFlag[i] == 2)
						{
							LBLaserCount++;
							if (py > LBtarrety[i] - tarretSize / 2 && py < LBtarrety[i] + tarretSize / 2)
							{
								pHitpoint -= 5;
								laserFlag[i] = 3;
							}
						}
						if (laserFlag[i] == 2 || laserFlag[i] == 3)
						{
							LBLaserCount++;
							if (LBLaserCount > 60)
							{
								laserFlag[i] = 0;
								LBLaserCount = 0;
							}
						}
						if (bShotFlag == 1)
						{
							double tmp;
							tmp = sqrt((px - LBx) * (px - LBx) + (py - LBy) * (py - LBy));
							tmp = 5 / tmp;
							bSvx = (px - LBx) * tmp;
							bSvy = (py - LBy) * tmp;
							bShotFlag = 2;
						}
						if (bShotFlag == 2)
						{
							bShotX += bSvx;
							bShotY += bSvy;
							if (bShotX+bSvx > roadright - ShotSize || bShotX+bSvx < roadleft + ShotSize)
							{
								bSvx = (-1)*bSvx;
								bShotBoundCounter++;
								bShotHitFlag = 0;
							}
							if (bShotY+ bSvy > 1080 - ShotSize || bShotY+ bSvy < ShotSize)
							{
								bSvy = (-1)*bSvy;
								bShotBoundCounter++;
								bShotHitFlag = 0;
							}
							if (bShotBoundCounter == 7)
							{
								bShotBoundCounter = 0;
								bShotHitFlag = 0;
								bShotFlag = 0;
							}
						}

					}
				}

				if (pHitpoint <= 0)gamefase = 2;
				if (LBHitPoint <= 0)gamefase = 3;
			}

			//ミニオン当たり判定
			for (i = 0; i < 5; i++)
			{
				if (mHitFlag[i] == 0)
				{
					pHitpoint -= collision(px, py, pSize, mx[i], my[i], minionSize);
					if (collision(px, py, pSize, mx[i], my[i], minionSize))
					{
						mHitFlag[i] = 1;
					}
				}
				if (mShotHitFlag[i] == 0)
				{
					pHitpoint -= collision(px, py, pSize, mShotx[i] + ShotSize / 2, mShoty[i] + ShotSize / 2, ShotSize / 2);
					if (collision(px, py, pSize, mShotx[i] + ShotSize / 2, mShoty[i] + ShotSize / 2, ShotSize / 2))
					{
						mShotHitFlag[i] = 1;
					}
				}

			}

			//自機→ミニオン当たり判定
			for (i = 0; i < 20; i++)
			{
				if (pShotFlag[i] == 1)
				{
					for (j = 0; j < 5; j++)
					{
						if (mFlag[j] == 1||mFlag[j]==2)
						{
							if (collision(mx[j], my[j], minionSize, pShotx[i] + ShotSize / 2, pShoty[i] + ShotSize / 2, ShotSize / 2) == 1)
							{
								mFlag[j] = 0;
								mHitFlag[j] = 0;
								nextMTime[j] = gameCounter + (minionUpTime * 60);
							}
						}
					}
				}
			}

			
			if (LBMode == 4)
			{
				//自機→ボス当たり判定
				if (LBDmgFlag == 1)
				{
					LBDmgCount++;
					if (LBDmgCount > 20)
					{
						LBDmgFlag = 0;
						LBDmgCount = 0;
						if (bShotFlag == 0)
						{
							bShotFlag = 1;
							bShotX = LBx - ShotSize;
							bShotY = LBy - ShotSize;
						}
						
					}
				}
				for (i = 0; i < 20; i++)
				{
					if (pShotFlag[i] == 1)
					{
						if (LBDmgFlag == 0)
						{
							if (collision(LBx, LBy, LBSize, pShotx[i] + ShotSize / 2, pShoty[i] + ShotSize / 2, ShotSize / 2) == 1)
							{
								LBHitPoint--;
								LBDmgFlag = 1;
							}
						}
					}
				}
				//ボス→自機当たり判定
				if (pDmgFlag == 1)
				{
					pDmgCount++;
					if (pDmgCount > 30)
					{
						pDmgFlag = 0;
						pDmgCount = 0;
					}
				}
				if (pDmgFlag == 0)
				{
					if (collision(px, py, pSize, LBx, LBy, LBSize) == 1)
					{
							pHitpoint--;
							pDmgFlag = 1;
					}
					
				}
				if (bShotFlag != 0&&bShotHitFlag==0)
				{
					if (collision(px, py, pSize, bShotX + ShotSize, bShotY + ShotSize, ShotSize) == 1)
					{
						pHitpoint -= 2;
						bShotHitFlag = 1;
					}
				}
			}
			


			//描画
			DrawBox(0, 0, 1080, 1080, GetColor(0, 0, 0), TRUE);
			DrawBox(roadleft, 0, roadright, 1080, GetColor(255, 255, 255), TRUE);
			DrawBox(0, 0, 1080, 1080, GetColor(255, 0, 0), FALSE);
			DrawBox(5, 5, 1075, 1075, GetColor(66, 255, 255), FALSE);
			
			for (i = 0; i < 4; i++)
			{
				DrawBox(swRx, swRy[i], swRx + wallWidth, swRy[i] + wallHeight, GetColor(255, 255, 255), TRUE);
				DrawBox(swLx, swLy[i], swLx + wallWidth, swLy[i] + wallHeight, GetColor(255, 255, 255), TRUE);
			}

			for (i = 0; i < 5; i++)
			{
				if (mFlag[i] != 0)
				{
					DrawCircle(mx[i], my[i], minionSize, GetColor(255, 0, 0), 1);
				}
				if (mShotFlag[i] == 1)
				{
					DrawBox(mShotx[i], mShoty[i], mShotx[i] + ShotSize, mShoty[i] + ShotSize, GetColor(0, 255, 0), 1);
				}
			}

			for (i = 0; i < 20; i++)
			{
				if (pShotFlag[i] == 1)
				{
					DrawBox(pShotx[i], pShoty[i], pShotx[i] + ShotSize, pShoty[i] + ShotSize, GetColor(0, 0, 255), TRUE);
				}
			}
			if (LBFlag != 0 && LBFlag != -1)
			{
				if (LBDmgFlag == 0)
				{
					DrawCircle(LBx, LBy, LBSize, GetColor(0, 0, 0), true);
				}
				if (LBDmgFlag == 1)
				{
					DrawCircle(LBx, LBy, LBSize, GetColor(255, 0, 0), true);
				}
			}
			if (LBMode >= 2)
			{
				for (i = 0; i < 3; i++)
				{
					DrawTriangle(LBtarretx[i], LBtarrety[i], LBtarretx[i] - tarretSize, LBtarrety[i] + (tarretSize / 2), LBtarretx[i] - tarretSize, LBtarrety[i] - (tarretSize / 2), GetColor(255, 255, 255), true);
					if (laserFlag[i] == 1)
					{
						DrawBox(LBtarretx[i], LBtarrety[i] + 5, LBtarretx[i + 3], LBtarrety[i] - 5, GetColor(0, 0, 0), true);
					}
					if (laserFlag[i] == 2 || laserFlag[i] == 3)
					{
						DrawBox(LBtarretx[i], LBtarrety[i] + tarretSize/2 , LBtarretx[i + 3], LBtarrety[i] - tarretSize/2, GetColor(0, 0, 0), true);
					}
				}
				for (i = 3; i < 6; i++)
				{
					DrawTriangle(LBtarretx[i], LBtarrety[i], LBtarretx[i] + tarretSize, LBtarrety[i] + (tarretSize / 2), LBtarretx[i] + tarretSize, LBtarrety[i] - (tarretSize / 2), GetColor(255, 255, 255), true);
				}
				if (LBMode == 4)
				{
					if (bShotFlag != 0)
					{
						DrawBox(bShotX, bShotY, bShotX + (2 * ShotSize), bShotY + (2 * ShotSize), GetColor(0, 255, 255), TRUE);
					}
				}
				
			}
			DrawCircle(px, py, pSize, GetColor(66, 255, 255), 1);


			if (gamefase == 2)
			{
				DrawBox(0, 0, windowSize, windowSize, GetColor(0, 0, 0), true);
				DrawString(300, 500, " GAME OVER\n\npress R to Title", GetColor(255, 255, 255));
				if (CheckHitKey(KEY_INPUT_R) == 1)
				{
					gameMode = reset;
				}
			}

			if (gamefase == 3)
			{
				DrawBox(0, 0, windowSize, windowSize, GetColor(255,255,255), true);
				DrawString(300, 500, " GAME CLEAR!\n\npress R to Title", GetColor(0, 0, 0));
				if (CheckHitKey(KEY_INPUT_R) == 1)
				{
					gameMode = reset;
				}
			}



			DrawCircle(moucex, moucey, 5, GetColor(255, 255, 255), 1);
			DrawTriangle(moucex, moucey, moucex + (gameCounter % 20), moucey-30, moucex - (gameCounter % 20), moucey-30, GetColor( 10, 10, 10), TRUE);
			DrawCircle(mouceClickedx, mouceClickedy, 5, GetColor(127, 0, 255), TRUE);
			//DrawFormatString(10, 10, GetColor(255, 255, 255), "%d\nHP:%d\nLBFlag:%d\nLBMode:%d\nLBHP:%d", gameCounter,pHitpoint,LBFlag,LBMode,LBHitPoint);
			if (pHitpoint < 0)pHitpoint = 0;
			DrawFormatString(20, 20, GetColor(66, 255, 255), "HP : %d", pHitpoint);
		}
		if (gameMode == reset)
		{
			px = windowSize / 2;
			py = windowSize - (pSize * 2);
			pvx = 0; pvy = 0;
			for (i = 0; i < 20; i++)
			{
				pShotFlag[i] = 0;
			}
			pShotCounter = 0;
			pHitpoint = pHP;
			pDmgCount = 0;
			pDmgFlag = 0;
			for (i = 0; i < 5; i++)
			{
				mShotFlag[i] = 0;
				mFlag[i] = 0;
				mHitFlag[i] = 0;
				mShotHitFlag[i] = 0;
				nextMTime[i] = (i + 2) * 60;
			}
			mDcount = 0;
			LBFlag = 0;
			LBMode = 0;
			LBHitPoint = 20;
			for (i = 0; i < 6; i++)
			{
				LBtarretx[i] = 0;
				LBtarrety[i] = 0;
			}
			for (i = 0; i < 3; i++)
			{
				laserFlag[i] = 0;
			}
			LBDmgFlag = 0;
			LBDmgCount = 0;
			gameCounter = 0;
			gamefase = 0;

			gameMode = title;
		}
		
		

		WaitTimer(oneFrame);
		ScreenFlip();



		if (CheckHitKey(KEY_INPUT_ESCAPE) == 1)break;


	}


	DxLib_End();
	return 0;
}
