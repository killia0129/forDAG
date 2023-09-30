#pragma once

struct InitializeData
{
    InitializeData()
        : shark(nullptr)
        , player(nullptr)
        , map(nullptr)
        , stopWatch(nullptr)
        , countDownUI(nullptr)
        , pressAUI(nullptr)
    {
        // èàóùñ≥Çµ
    }
    class Shark* shark;
    class Player* player;
    class Map* map;
    class StopWatch* stopWatch;
    class CountDownUI* countDownUI;
    class PressAUI* pressAUI;
    class ResultScoreUI* resultScoreUI;
    class ScoreDraw* scoreDraw;
    class UI* ui;
};