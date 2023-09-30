#pragma once
#include "SceneBase.h"
#include "ObjectController.h"
#include"Meteor.h"
#include"Needle.h"
#include"Boss.h"
#include"Player.h"
#include"PlayerBeam.h"
#include"BackEffect.h"
#include"UI.h";
#include"Beam.h"
class GameScene :
    public SceneBase
{
public:
    GameScene();
    virtual ~GameScene();
    void Update()override;

private:
    enum PHASE
    {
        TUTORIAL,NORMAL,BEAM_ONE,BEAM_TWO,BOSS,CHANGE_BOSS
    };


    ObjectController* obj = new ObjectController();
    UI* ui = new UI();
    VECTOR cell[4][4];
    Beam* beam[4];
    float count;
    float obsCool;
    float backCool;
    float beamCool;
    int deleteCount;
    float time;
    float blinkRad;
    PHASE phase;
    void TutorialUpdate();
    void NormalUpdate();
    void BeamOneUpdate();
    void BeamTwoUpdate();
    void ChangeBossUpdate();
    void BossUpdate();

};

