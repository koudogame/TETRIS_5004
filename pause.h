#pragma once

#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"

class Pause
{
private :
    ID3D11ShaderResourceView* texture_;

public:
    Pause();
    bool init();
    int update();
    void draw();
    void cursordraw();
    void destroy();

    int menucnt = 0;

};