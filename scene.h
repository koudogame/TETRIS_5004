#pragma once
#include"release.h"
#include"player.h"
#include"key.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"player.h"
#include"adx.h"
#include"Error.h"

class Scene
{
private:
    ID3D11ShaderResourceView* texture_;         //テクスチャ
    ID3D11ShaderResourceView* texture2_;         //テクスチャ
public:
    bool init();
    bool update();
    void draw();
    void destroy();

    int cnt = 0;
    int cnt2 = 0;
    bool max = false;

    bool cri = false;
    bool koudo = true;
    bool flip = false;
    bool end = false;
    float critrans = 0.0F;
    float koudotrans = 0.0F;

    int nowtime;
    int oldtime;



};