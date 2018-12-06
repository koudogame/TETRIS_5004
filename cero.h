#pragma once
#include"game.h"

class Cero
{
private:
    ID3D11ShaderResourceView* texture_;     // レーティング
    
public:
    bool init();
    bool update();
    void draw();
    void destroy();

    int cnt = 0; //レーティング画面の描画時間
};