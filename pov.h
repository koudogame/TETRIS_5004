#pragma once
#include<d3d11.h>
#include"release.h"
#include"key.h"
#include"pad.h"
#include"Error.h"
#include"sprite.h"


enum              //�\���L�[���͕\���p
{
    NOINPUT,
    UP,
    UPPER_RIGHT,
    RIGHT,
    BOTTOM_RIGHT,
    DOWN,
    BOTTOM_LEFT,
    LEFT,
    UPPER_LEFT
};

class Pov
{
private:

public:
    int update();

    int pov = NOINPUT;                          //�\���L�[�̓��͏��

};