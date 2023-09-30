#include "InputMove.h"

int InputMove::Input()
{
    if (CheckHitKey(KEY_INPUT_W))
    {
        return DIR::AHEAD;
    }
    else if (CheckHitKey(KEY_INPUT_A))
    { 
        return DIR::LEFT;
    }
    else if (CheckHitKey(KEY_INPUT_S))
    {
        return DIR::BACK;
    }
    else if (CheckHitKey(KEY_INPUT_D))
    {
        return DIR::RIGHT;
    }
    else
    {
        return DIR::NEUTRAL;
    }
}
