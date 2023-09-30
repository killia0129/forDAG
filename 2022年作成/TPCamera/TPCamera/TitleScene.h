#pragma once
#include<vector>
#include"Stage.h"
#include"Needle.h"
#include"Meteor.h"
#include"LineEffect.h"
class TitleScene
{
public:
    TitleScene();
    virtual ~TitleScene();
    float ALL();

private:
    Stage* stage = new Stage;
    std::vector<ObstructBase*>obstructs;
    std::vector<LineEffect*>lineEff;
    int nowTime;
    int previousTime;
    float deltaTime;
    float obsCool;
    float lineCool;
    int seed;
    void Entry();
    void ObsDelete(ObstructBase* deleteObs);
    void EntryLine();
    void LineDelete(LineEffect* deleteLine);
    VECTOR cell[4][4];
    int colorScreen;
    int DownScaleScreen;
    int gaussScreen;
};

