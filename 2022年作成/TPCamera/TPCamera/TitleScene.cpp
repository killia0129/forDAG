#include "TitleScene.h"

TitleScene::TitleScene()
{
    nowTime = 0;
    deltaTime = 0.0f;
    previousTime = 0;
    obsCool = 2.5f;
    lineCool = 0.0f;
    seed = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cell[i][j] = VGet(-15.0 + 10.0f * (float)i, -15.0 + 10.0f * (float)j, 500.0f);
        }
    }
    colorScreen = MakeScreen(1920, 1080, false);
    DownScaleScreen = MakeScreen(1920 / 2, 1080 / 2, false);
    gaussScreen = MakeScreen(1920 / 2, 1080 / 2, false);
}

TitleScene::~TitleScene()
{
}

float TitleScene::ALL()
{
    XINPUT_STATE padInput;
    while (1)
    {
        SetDrawScreen(colorScreen);

        ClearDrawScreen();

        nowTime = GetNowCount();
        deltaTime = (float)(nowTime - previousTime) / 1000.0f;
        obsCool += deltaTime;
        lineCool += deltaTime;
        //AddSpeed(deltaTime);

        GetJoypadXInputState(DX_INPUT_KEY_PAD1, &padInput);

        srand(seed);

        SetCameraNearFar(1.0f, 499.0f);
        SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));


        if (lineCool > 0.3f)
        {
            for (int i = 0; i < 100; i++)
            {
                EntryLine();
            }
            lineCool = 0.0f;
        }
        if (obsCool > 2.5f)
        {
            Entry();
            obsCool = 0.0f;
        }
        seed++;
        if (seed > 100000)
        {
            seed = 0;
        }




        //Update
        for (auto ptr : obstructs)
        {
            ptr->Update(deltaTime);
        }
        stage->Update(deltaTime);

        for (auto ptr : obstructs)
        {
            if (ptr->posGetter().z < 0.0f)
            {
                ptr->setDead(true);
            }
        }
        for (auto ptr : lineEff)
        {
            ptr->Update(deltaTime);
        }

       


        //Delete
        std::vector<ObstructBase*>deadObs;
        for (auto ptr : obstructs)
        {
            if (ptr->isDead())
            {
                deadObs.emplace_back(ptr);
            }
        }
        for (auto ptr : deadObs)
        {
            ObsDelete(ptr);
        }

        std::vector<LineEffect*>deadLine;
        for (auto ptr : lineEff)
        {
            if (ptr->IsEnd())
            {
                deadLine.emplace_back(ptr);
            }
        }
        for (auto ptr : deadLine)
        {
            LineDelete(ptr);
        }




        for (auto ptr : lineEff)
        {
            ptr->Draw();
        }
        stage->Draw();
        for (auto ptr : obstructs)
        {
            ptr->Draw();
        }

        DrawFormatString(740, 50, GetColor(0, 255, 0), "Press   to Start");
        DrawFormatString(735, 50, GetColor(255, 0, 0), "      B ");
        SetFontSize(125);
        DrawFormatString(350, 175, GetColor(0, 255, 0), "EndLess BEAMer");
        SetFontSize(40);
        DrawFormatString(570, 400, GetColor(0, 255, 0), "L-Stick : MOVE  R-Stick : Aim");


        GraphFilterBlt(colorScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 2);
        GraphFilterBlt(DownScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 32, 1500);
        SetDrawScreen(gaussScreen);
        //DrawBox(0, 0, 1920 / 2, 12, GetColor(0, 0, 0), true);
        SetDrawScreen(DX_SCREEN_BACK);
        DrawGraph(0, 0, colorScreen, false);
        SetDrawMode(DX_DRAWMODE_BILINEAR);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 255);
        DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
        DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);
        //SetDrawBlendMode(DX_BLENDMODE_ADD, 169);
        //DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        SetDrawMode(DX_DRAWMODE_ANISOTROPIC);

        //DrawFormatString(10, 10, GetColor(255, 255, 255), "%3.2f", 1.0f / deltaTime);

        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            return -2.0f;
        }

        if (CheckHitKey(KEY_INPUT_RETURN) || padInput.Buttons[XINPUT_BUTTON_B] != 0)
        {
            return -1.0f;
        }

        previousTime = nowTime;

        ScreenFlip();
    }
}

void TitleScene::Entry()
{
    int type = rand() % 2;
    int cellX, cellY;

    if (type == 0)
    {
        cellY = rand() % 4;
        int wave = rand() % 2;
        if (wave == 0)
        {
            cellX = rand() % 2 + 1;
            Meteor* newObj = new Meteor(cell[cellX][cellY], true);
            obstructs.emplace_back(newObj);
        }
        else
        {
            cellX = rand() % 4;
            Meteor* newObj = new Meteor(cell[cellX][cellY], false);
            obstructs.emplace_back(newObj);
        }
    }
    else
    {
        cellX = rand() % 4;
        cellY = rand() % 4;
        Needle* newObj = new Needle(cell[cellX][cellY]);
        obstructs.emplace_back(newObj);
    }
}

void TitleScene::ObsDelete(ObstructBase* deleteObs)
{
    auto iter = std::find(obstructs.begin(), obstructs.end(), deleteObs);
    if (iter != obstructs.end())
    {
        std::iter_swap(iter, obstructs.end() - 1);
        obstructs.pop_back();
    }
}

void TitleScene::EntryLine()
{
    LineEffect* newObj = new LineEffect();
    lineEff.emplace_back(newObj);
}

void TitleScene::LineDelete(LineEffect* deleteLine)
{
    auto iter = std::find(lineEff.begin(), lineEff.end(), deleteLine);
    if (iter != lineEff.end())
    {
        std::iter_swap(iter, lineEff.end() - 1);
        lineEff.pop_back();
    }
}
