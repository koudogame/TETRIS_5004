#pragma once

#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"adx.h"
#include"Error.h"
#include"UI.h"

class Ranking
{
private:
    ID3D11ShaderResourceView* texture_;
public:
    Ranking();
    bool init();
    bool update();
    void draw();
    void destroy();

    int num = 0;
    int rankcntx = 0;
    int rankcnty = 0;
};