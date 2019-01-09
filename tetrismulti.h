#pragma once
#include"player.h"
#include"key.h"
#include"release.h"
#include"title.h"
#include"start.h"
#include"MINO.h"
#include"pause.h"
#include"start.h"
#include"game.h"

class Tetrismulti
{
private:
    ID3D11ShaderResourceView* texture_;  // UIテクスチャ
public:
    Tetrismulti();
    bool init();
    int update();
    void draw();
    void destroy();

};