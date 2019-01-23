#pragma once
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include"texture.h"
#include"release.h"

class Gameover
{
private:
    ID3D11ShaderResourceView* texture_;
public:
    bool init();
    void update();
    void draw();
    void destroy();

    int menucnt = 0;
};
