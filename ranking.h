#pragma once

#include<d3d11.h>
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
};