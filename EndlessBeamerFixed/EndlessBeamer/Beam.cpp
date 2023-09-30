#include "Beam.h"


const float DefaultPosX = -15.f;
const float BeamPosDiffX = 10.f;
const float BeamPosY = 25.f;
const float BeamPosZ = 25.f;
const float BeamR = 5.f;
const float BlinkFirstFase = 0.3f;
const float BlinkSecondFase = 0.45f;
const float OnFireTime = 2.f;
const float EndTime = 4.f;
const float BeamSpeed = 1000.f;
const float BeamEndSpeed = 100.f;
const int AnnounceLineDiffX = 480;
const unsigned int AnnounceColor = GetColor(255, 0, 0);
const int AnnounceLineThickness = 3;
const int AnnounceFontSize = 100;
const int ExclamationMarkDiffX = 10;
const int ExclamationMarkHeight = 530;
const int OnFireAlfaBlend = 144;
const int CooldownAlfaBlend = 169;
const int BeamDivNum = 8;
const unsigned int BeamFrameColor = GetColor(42, 255, 255);
const float LaneStart = -20.f;
const float LaneLeftDiffX = 10.f;
const int WindowHeight = 1080;
const float PlayerR = 1.5f;

Beam::Beam(int laneNum)
{
    pos = VGet(DefaultPosX + BeamPosDiffX * (float)laneNum, BeamPosY, BeamPosZ);
    beamLast = pos;
    phase = READY;
    count = 0.0f;
    lane = laneNum;
    blinkController = 0.0f;
    blinkFlag = true;
    beamR = BeamR;
    hitFlag = false;
}

Beam::~Beam()
{
}

void Beam::Update(float deltaTime)
{
    if (phase != READY)
    {
        count += deltaTime;
    }
    if (phase == ANNOUNCE)
    {
        blinkController += deltaTime;
        if (blinkController <= BlinkFirstFase)
        {
            blinkFlag = true;
        }
        else if (blinkController <= BlinkSecondFase)
        {
            blinkFlag = false;
        }
        else
        {
            blinkController = 0.0f;
        }
        if (count >= OnFireTime)
        {
            phase = ONFIRE;
        }
    }
    if (phase == ONFIRE)
    {
        beamLast = VGet(beamLast.x, beamLast.y - (BeamSpeed * deltaTime), beamLast.z);
        if (count >= EndTime)
        {
            phase = COOLDOWN;
        }
    }
    if (phase == COOLDOWN)
    {
        beamR -= BeamEndSpeed * deltaTime;
        if (beamR <= 0.0f)
        {
            phase = READY;
        }
    }
}


void Beam::Draw()
{
    if (phase != READY)
    {
        switch (phase)
        {
        case ANNOUNCE:
            if (blinkFlag)
            {
                DrawLine(lane * AnnounceLineDiffX, 0, lane * AnnounceLineDiffX, WindowHeight, AnnounceColor, AnnounceLineThickness);
                DrawLine((lane + 1) * AnnounceLineDiffX, 0, (lane + 1) * AnnounceLineDiffX, WindowHeight, AnnounceColor, AnnounceLineThickness);
                SetFontSize(AnnounceFontSize);
                DrawString(ExclamationMarkDiffX + lane * AnnounceLineDiffX, ExclamationMarkHeight, "!!!!!!", AnnounceColor);
            }
            break;

        case ONFIRE:
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, OnFireAlfaBlend);
            DrawCapsule3D(pos, beamLast, beamR, BeamDivNum, AnnounceColor, AnnounceColor, true);
            DrawCapsule3D(pos, beamLast, beamR, BeamDivNum, BeamFrameColor, BeamFrameColor, false);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;

        case COOLDOWN:
            SetDrawBlendMode(DX_BLENDMODE_ALPHA, CooldownAlfaBlend);
            DrawCapsule3D(pos, beamLast, beamR, BeamDivNum, AnnounceColor, AnnounceColor, true);
            DrawCapsule3D(pos, beamLast, beamR, BeamDivNum, BeamFrameColor, BeamFrameColor, false);
            SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
            break;

        default:
            break;
        }
    }
}

void Beam::Start()
{
    phase = ANNOUNCE;
    count = 0.0f;
    blinkController = 0.0f;
    beamLast = pos;
    beamR = BeamR;
    hitFlag = false;
}

bool Beam::HitCheck(VECTOR pPos)
{
    if (!hitFlag)
    {
        if (phase == ONFIRE)
        {
            if (pPos.x >= LaneStart + (LaneLeftDiffX * lane) - PlayerR && pPos.x <= LaneStart + (LaneLeftDiffX * (lane + 1)) + PlayerR)
            {
                hitFlag = true;
                return true;
            }
        }
    }
    return false;
}
