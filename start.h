#pragma once

#include"release.h"
#include"player.h"
#include"title.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"key.h"

class Start
{
private:
    ID3D11ShaderResourceView* texture_;         //1p€”õŠ®—¹


public:

    Start();
    ~Start();

    //‰Šú‰»
    bool init();                                //‰Šú‰»
    bool update();                              //XV
    void draw();                                //•`‰æ
    void cntdraw();                             //•b”•`‰æ
    void godraw();                              //GO!!•`‰æ
    void destroy();                             //”jŠü

    //•Ï”
    int nowtime = 0;
    int oldtime = 0;

    int starttimer = 3;

    //ƒtƒ‰ƒO
    bool goflag = false;

    //ƒJƒEƒ“ƒg
    int cnt = 0;
};