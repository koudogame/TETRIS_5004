#pragma once
#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include<ctime>

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
    int back[22][12]; //流すよう配列

    int nowtime = 0;
    int oldtime = 0;

    //方向キー
    int right = 0;
    int left = 0;
    int up = 0;
    int down = 0;
    int pos = 0;

    //カウント
    int cnt = 0;
    int acnt = 0;
    int bcnt = 0;
    int ccnt = 0;
};