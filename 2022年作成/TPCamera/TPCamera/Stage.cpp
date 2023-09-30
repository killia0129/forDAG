#include "Stage.h"

Stage::Stage()
{
    for (int i = 0; i < 3; i++)
    {
        reftArrow[i] = VGet(20.0f, 0.0f, (250.0f * (float)i));
        lightArrow[i] = VGet(-20.0f, 0.0f, (250.0f * (float)i));
    }
}

Stage::~Stage()
{
}

void Stage::Update(float deltaTime)
{
    for (int i = 0; i < 3; i++)
    {
        lightArrow[i].z -= 300.0f * deltaTime;
        reftArrow[i].z -= 300.0f * deltaTime;

        if (lightArrow[i].z < 0.0f)
        {
            switch (i)
            {
            case 0:
                lightArrow[i].z = lightArrow[2].z + 250.0f;
                reftArrow[i].z = reftArrow[2].z + 250.0f;
                break;

            case 1:
                lightArrow[i].z = lightArrow[0].z + 250.0f;
                reftArrow[i].z = reftArrow[0].z + 250.0f;
                break;

            case 2:
                lightArrow[i].z = lightArrow[1].z + 250.0f;
                reftArrow[i].z = reftArrow[1].z + 250.0f;
                break;

            default:
                break;
            }
        }
    }
}

void Stage::Draw()
{
    DrawCube3D(VGet(-20.0f, -20.0f, -20.0f), VGet(20.0f, 20.0f, 500.0f), GetColor(0, 255, 0), GetColor(0, 255, 0), false);
    for (int i = 0; i < 3; i++)
    {
        DrawTriangle3D(lightArrow[i], VGet(lightArrow[i].x, lightArrow[i].y - 10.0f, lightArrow[i].z + 10.0f), VGet(lightArrow[i].x, lightArrow[i].y + 10.0f, lightArrow[i].z + 10.0f), GetColor(0, 255, 0), true);
        DrawTriangle3D(reftArrow[i], VGet(reftArrow[i].x, reftArrow[i].y - 10.0f, reftArrow[i].z + 10.0f), VGet(reftArrow[i].x, reftArrow[i].y + 10.0f, reftArrow[i].z + 10.0f), GetColor(0, 255, 0), true);
    }

}
