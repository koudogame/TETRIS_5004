#pragma once
#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //テクスチャ
public:
    Mino();

    bool init();
    bool update();
    void draw();
    void destroy();

};