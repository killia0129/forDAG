#pragma once
#include "Object.h"
class Stage
{
public:
    Stage();
    virtual ~Stage();
    void Update(float deltaTime);
    void Draw();

private:
    VECTOR reftArrow[3];
    VECTOR lightArrow[3];
};

