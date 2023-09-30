#include "PlayScene.h"

PlayScene::PlayScene()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cell[i][j] = VGet(-15.0+10.0f * (float)i, -15.0 + 10.0f* (float)j, 500.0f);
        }
    }
    seed = 0;
    nowTime = GetNowCount();
    previousTime = GetNowCount();
    count = 0.0f;
    obsCool = 0.0f;
    beamCool = 0.0f;
    lineCool = 0.0f;
    deltaTime = 0.0f;
    deleteCount = 0;
    time = 60.0f;
    plusSec = 0;
    plusSecX = 0;
    plusSecY = 0;
    fase = NORMAL;
    faseMoving = false;
    for (int i = 0; i < 4; i++)
    {
        Beam* tmp = new Beam(i);
        beam[i] = tmp;
    }
    colorScreen = MakeScreen(1920, 1080, false);
    DownScaleScreen = MakeScreen(1920 / 2, 1080 / 2, false);
    gaussScreen = MakeScreen(1920 / 2, 1080 / 2, false);
    blinkRad = 0.0f;
    howTo = new HowToPlay();

    /*BossScene* boss = new BossScene(VGet(0, 0, 500));
    obstructs.emplace_back(boss);*/

}

PlayScene::~PlayScene()
{
}

float PlayScene::ALL()
{
    while (1)
    {
        SetDrawScreen(colorScreen);

        ClearDrawScreen();

        nowTime = GetNowCount();
        deltaTime = (float)(nowTime - previousTime) / 1000.0f;
        count += deltaTime;
        obsCool += deltaTime;
        lineCool += deltaTime;
        time -= deltaTime;
        if (deleteCount >= 10)
        {
            beamCool += deltaTime;
        }
        //AddSpeed(deltaTime);

        SetCameraNearFar(1.0f, 499.0f);
        SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));

        srand(seed);

        if (lineCool >= 0.3f)
        {
            for (int i = 0; i < 50; i++)
            {
                EntryLine();
            }
            lineCool = 0.0f;
        }

        if (fase == NORMAL)
        {
            if (howTo->isEnd())
            {
                if (obsCool > 3.0f)
                {
                    Entry();
                    obsCool = 0.0f;
                }
            }
        }
        if (fase == SETBOSS)
        {
            if (faseMoving)
            {
                for (auto ptr : obstructs)
                {
                    ptr->setDead(true);
                }
                std::vector<ObstructBase*>deadObs;
                for (auto ptr : obstructs)
                {
                    if (ptr->isDead())
                    {
                        EntryExp(ptr->posGetter());
                        deadObs.emplace_back(ptr);
                    }
                }
                for (auto ptr : deadObs)
                {
                    ObsDelete(ptr);
                }
                if (expro.size() <= 0)
                {
                    faseMoving = false;
                }
            }
            if (!faseMoving)
            {
                fase = BOSS;
                BossScene* boss = new BossScene(VGet(0.0f, 0.0f, 550.0f));
                obstructs.emplace_back(boss);
            }
        }

        if (beamCool >= 6.0f)
        {
            if (deleteCount < 20)
            {
                beam[rand() % 4]->Start();
            }
            else
            {
                int tmp1 = rand() % 4;
                int tmp2;
                do
                {
                    tmp2 = rand() % 4;
                } while (tmp1 == tmp2);
                beam[tmp1]->Start();
                beam[tmp2]->Start();
            }
            beamCool = 0.0f;
        }
        seed++;
        if (seed > 100000)
        {
            seed = 0;
        }
        


        
        //Update
        if (!howTo->isEnd())
        {
            howTo->Update(deltaTime);
        }
        for (auto ptr : obstructs)
        {
            ptr->Update(deltaTime);
        }
        stage->Update(deltaTime);
        player->Update(deltaTime);
        aim->Update(deltaTime, player->posGetter());
        for (auto ptr : beam)
        {
            ptr->Update(deltaTime);
        }
        for (auto ptr : obstructs)
        {
            if (ptr->posGetter().z < -10.0f)
            {
                ptr->setDead(true);
            }
        }
        for (auto ptr : lineEff)
        {
            ptr->Update(deltaTime);
        }
        if (plusSec == 1)
        {
            if (plusSecY > 20)
            {
                plusSecY -= 1000 * deltaTime;
            }
            else
            {
                plusSecY = 20;
                plusSec = 2;
            }
        }
        if (plusSec == 2)
        {
            if (plusSecX <= 1910)
            {
                plusSecX += 1000 * deltaTime;
            }
            else
            {
                plusSec = 0;
            }
        }

        if (time < 20.0f)
        {
            blinkRad += 1.0 * deltaTime;
            if (time < 10.0f)
            {
                blinkRad += 1.0 * deltaTime;
            }
            if (blinkRad >= 2.0f)
            {
                blinkRad = 0.0f;
            }
        }
        else
        {
            blinkRad = 0.0f;
        }

        //Hit
        VECTOR mark = aim->MarkGetter();
        for (auto ptr : obstructs)
        {
            float obsZ = ptr->posGetter().z;
            float ratio = (obsZ - 3.0f) / (mark.z - 3.0f);
            float moveX = player->posGetter().x + ((mark.x - player->posGetter().x) * ratio);
            float moveY = player->posGetter().y + ((mark.y - player->posGetter().y) * ratio);
            VECTOR markMoved = VGet(moveX, moveY, ptr->posGetter().z);
            float dis = (ptr->posGetter().x - markMoved.x) * (ptr->posGetter().x - markMoved.x) +  (ptr->posGetter().y - markMoved.y) * (ptr->posGetter().y - markMoved.y);
            dis = sqrtf(dis);
            if (fase == NORMAL)
            {
                if (dis < 4.0f && ptr->posGetter().z>10.0f)
                {
                    ptr->GivenDmg(deltaTime);
                    Particle* newEffect = new Particle(ptr->posGetter());
                    particle.emplace_back(newEffect);
                    if (ptr->isDead())
                    {
                        if (ptr->TypeGetter() == ObstructBase::TYPE::METEOR)
                        {
                            time += 10.0f;
                            if (time > 60.0f)
                            {
                                time = 60.0f;
                            }
                            if (plusSec == 0)
                            {
                                plusSec = 1;
                                plusSecX = ConvWorldPosToScreenPos(ptr->posGetter()).x;
                                plusSecY = ConvWorldPosToScreenPos(ptr->posGetter()).y;
                            }
                        }
                        deleteCount++;
                    }
                }
            }
            if (fase == BOSS)
            {
                if (dis <= 8.5f)
                {
                    ptr->GivenDmg(deltaTime);
                    Particle* newEffect = new Particle(ptr->posGetter());
                    particle.emplace_back(newEffect);
                }
                if (ptr->isDead())
                {
                    deleteCount++;
                }
            }
        }
        for (auto ptr : beam)
        {
            if (ptr->HitCheck(player->posGetter()))
            {
                time -= 3.0f;
            }
        }
        for (auto ptr : particle)
        {
            ptr->Update(deltaTime);
        }
        for (auto ptr : expro)
        {
            ptr->Update(deltaTime);
        }

        ui->Update(time, deleteCount);

        //Delete
        std::vector<ObstructBase*>deadObs;
        for (auto ptr : obstructs)
        {
            if (ptr->isDead())
            {
                if (ptr->posGetter().z > 10.0f)
                {
                    EntryExp(ptr->posGetter());
                }
                deadObs.emplace_back(ptr);
            }
        }

        std::vector<Exprosion*>deadExp;
        for (auto ptr : expro)
        {
            if (ptr->isEnd())
            {
                deadExp.emplace_back(ptr);
            }
        }
        std::vector<Particle*>deadPart;
        for (auto ptr : particle)
        {
            if (ptr->isEnd())
            {
                deadPart.emplace_back(ptr);
            }
        }
        std::vector<LineEffect*>deadLine;
        for (auto ptr : lineEff)
        {
            if (ptr->IsEnd())
            {
                deadLine.emplace_back(ptr);
            }
        }


        for (auto ptr : deadObs)
        {
            ObsDelete(ptr);
        }
        for (auto ptr : deadExp)
        {
            ExpDelete(ptr);
        }
        for (auto ptr : deadPart)
        {
            PartDelete(ptr);
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
        aim->Draw(false);
        for (auto ptr : expro)
        {
            ptr->Draw();
        }
        player->Draw();
        if (!howTo->isEnd())
        {
            howTo->Draw();
        }
        for (auto ptr : obstructs)
        {
            ptr->Draw();
        }
        
        for (auto ptr : particle)
        {
            ptr->Draw();
        }

        if (plusSec != 0)
        {
            SetFontSize(20);
            DrawString(plusSecX, plusSecY, "+10.0s", GetColor(255, 255, 255));
            SetFontSize(40);
        }

        for (auto ptr : beam)
        {
            ptr->Draw();
        }

        ui->Draw();


        if (deleteCount == 29&&fase==NORMAL)
        {
            fase = SETBOSS;
            faseMoving = true;
        }



        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            return -1.0f;
        }

        GraphFilterBlt(colorScreen, DownScaleScreen, DX_GRAPH_FILTER_DOWN_SCALE, 2);
        GraphFilterBlt(DownScaleScreen, gaussScreen, DX_GRAPH_FILTER_GAUSS, 32, 1500);
        SetDrawScreen(gaussScreen);
        DrawBox(0, 0, 1920 / 2, 12, GetColor(0, 0, 0), true);
        SetDrawScreen(DX_SCREEN_BACK);
        DrawGraph(0, 0, colorScreen, false);
        SetDrawMode(DX_DRAWMODE_ANISOTROPIC);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 255 * (fabs(cosf(blinkRad*DX_PI_F))));
        DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);
        SetDrawBlendMode(DX_BLENDMODE_ADD, 128*(fabs(cosf(blinkRad * DX_PI_F))));
        DrawExtendGraph(0, 0, 1920, 1080, gaussScreen, false);

        SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
        SetDrawMode(DX_DRAWMODE_ANISOTROPIC);


        if (deleteCount >= 30)
        {
            float num = 0.0f;
            float _nowCount;

            SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));
            float _previousCount = GetNowCount();
            while (num <= 2.0f)
            {
                ClearDrawScreen();
                _nowCount = GetNowCount();

                if (num <= 1.0f)
                {
                    for (auto ptr : lineEff)
                    {
                        ptr->Draw();
                    }
                    stage->Draw();
                    aim->Draw(false);
                    for (auto ptr : expro)
                    {
                        ptr->Draw();
                    }
                    player->Draw();
                    for (auto ptr : obstructs)
                    {
                        ptr->Draw();
                    }

                    for (auto ptr : particle)
                    {
                        ptr->Draw();
                    }

                    if (plusSec != 0)
                    {
                        SetFontSize(20);
                        DrawString(plusSecX, plusSecY, "+10.0s", GetColor(255, 255, 255));
                        SetFontSize(40);
                    }

                    for (auto ptr : beam)
                    {
                        ptr->Draw();
                    }

                    ui->Draw();
                    
                    num += (float)(_nowCount - _previousCount) / 100.0f;
                    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * num / 1.0f);
                    DrawBox(0, 0, 1920, 1080, GetColor(42, 255, 255), true);
                }
                else
                {
                    num += (float)(_nowCount - _previousCount) / 1000.0f;
                    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (2.0f-num) / 1.0f);
                    DrawBox(0, 0, 1920, 1080, GetColor(42, 255, 255), true);
                   
                }
                _previousCount = GetNowCount();
                ScreenFlip();
            }
            //WaitTimer(1000);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
            return count;
        }

        if (time < 0)
        {
            float num = 0.0f;
            float _nowCount;
            SetCameraPositionAndTarget_UpVecY(VGet(0, 0, 0), VGet(0.0f, 0.0f, 250.0f));
            float _previousCount = GetNowCount();
            while (num <= 2.0f)
            {
                ClearDrawScreen();
                _nowCount = GetNowCount();

                if (num <= 1.0f)
                {
                    for (auto ptr : lineEff)
                    {
                        ptr->Draw();
                    }
                    stage->Draw();
                    aim->Draw(false);
                    for (auto ptr : expro)
                    {
                        ptr->Draw();
                    }
                    player->Draw();
                    for (auto ptr : obstructs)
                    {
                        ptr->Draw();
                    }

                    for (auto ptr : particle)
                    {
                        ptr->Draw();
                    }

                    if (plusSec != 0)
                    {
                        SetFontSize(20);
                        DrawString(plusSecX, plusSecY, "+10.0s", GetColor(255, 255, 255));
                        SetFontSize(40);
                    }

                    for (auto ptr : beam)
                    {
                        ptr->Draw();
                    }

                    ui->Draw();

                    num += (float)(_nowCount - _previousCount) / 1000.0f;
                    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * num / 1.0f);
                    DrawBox(0, 0, 1920, 1080, GetColor(255, 0, 0), true);
                }
                else
                {
                    num += (float)(_nowCount - _previousCount) / 1000.0f;
                    SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 * (2.0f - num) / 1.0f);
                    DrawBox(0, 0, 1920, 1080, GetColor(255, 0, 0), true);

                }
                _previousCount = GetNowCount();
                ScreenFlip();
            }
            //WaitTimer(1000);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
            //WaitTimer(1000);
            return -4.0f;
        }

        previousTime = nowTime;

        ScreenFlip();
    }
}

void PlayScene::Entry()
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

void PlayScene::EntryExp(VECTOR pos)
{
    Exprosion* newObj = new Exprosion(pos);
    expro.emplace_back(newObj);
}

void PlayScene::EntryLine()
{
    LineEffect* newObj = new LineEffect();
    lineEff.emplace_back(newObj);
}

void PlayScene::ObsDelete(ObstructBase* deleteObs)
{
    auto iter = std::find(obstructs.begin(), obstructs.end(), deleteObs);
    if (iter != obstructs.end())
    {
        std::iter_swap(iter, obstructs.end() - 1);
        obstructs.pop_back();
    }
}

void PlayScene::ExpDelete(Exprosion* deleteExp)
{
    auto iter = std::find(expro.begin(), expro.end(), deleteExp);
    if (iter != expro.end())
    {
        std::iter_swap(iter, expro.end() - 1);
        expro.pop_back();
    }
}

void PlayScene::PartDelete(Particle* deletePart)
{
    auto iter = std::find(particle.begin(), particle.end(), deletePart);
    if (iter != particle.end())
    {
        std::iter_swap(iter, particle.end() - 1);
        particle.pop_back();
    }
}

void PlayScene::LineDelete(LineEffect* deleteLine)
{
    auto iter = std::find(lineEff.begin(), lineEff.end(), deleteLine);
    if (iter != lineEff.end())
    {
        std::iter_swap(iter, lineEff.end() - 1);
        lineEff.pop_back();
    }
}
