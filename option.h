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

class Option
{
private:
    ID3D11ShaderResourceView* texture_; //テクスチャ
    RECT trim;

public:
    //コンストラクタ
    Option() { texture_ = NULL; }

    bool init();        //初期化
    bool update();       //更新
    void draw();        //描画
    void buttondraw();
    void dpaddraw();
    void destroy();     //破棄

};