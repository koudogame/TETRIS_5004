#pragma once
#include<d3d11.h>
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

    bool cri = false;
    bool koudo = false;

};