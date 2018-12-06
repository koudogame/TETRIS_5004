#pragma once

#include<d3d11.h>
#include"Release.h"

class Credit
{
private:
    ID3D11ShaderResourceView* texture_; //テクスチャ
    ID3D11ShaderResourceView* Ctexture_; //テクスチャ
    RECT trim;

public:
    //コンストラクタ
    Credit() { texture_ = NULL; }

    bool init();        //初期化
    bool update();       //更新
    void draw();        //描画
    void buttondraw();
    void destroy();     //破棄

    int menu = 0; //ゲームを終わるときにtrue
    int cnt = 0;

};
