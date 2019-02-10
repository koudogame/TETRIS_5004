#pragma once
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include"texture.h"
#include"release.h"
#include"adx.h"

class Gameover
{
private:
    ID3D11ShaderResourceView* texture_;
public:
    Gameover();
    bool init();
    int update();
    void draw();
    void destroy();

    int menu = 0;
};
