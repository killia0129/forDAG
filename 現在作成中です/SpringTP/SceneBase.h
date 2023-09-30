#pragma once
class SceneBase
{
public:
    SceneBase();
    virtual ~SceneBase();
    virtual void Run() = 0;
    bool isEnd();

protected:
    bool endFlag;
};