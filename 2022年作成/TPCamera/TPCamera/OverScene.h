#pragma once
#include<string>
class OverScene
{
public:
    OverScene();
    virtual ~OverScene();
    float ALL(float time);

private:
    int FileHandle;
    std::string sScores[10];
    float fScores[10];
};

