
#pragma once

#include "GameTimer.hpp"

class Game
{
public:
    void Tick();

private:
    GameTimer m_timer;
};