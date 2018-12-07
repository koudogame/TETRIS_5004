#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include"key.h"
#include"pad.h"
#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"Error.h"
#include"pov.h"

#define SPEED 5

class UI
{
private:
    ID3D11ShaderResourceView* texture_;  // UIテクスチャ
    ID3D11ShaderResourceView* Mtexture_; //メーターのテクスチャ
    ID3D11ShaderResourceView* Ptexture_; //仕切りのテクスチャ
    Vector2 position;                    // メーターの座標
    RECT trim;                           //メーターのトリミング範囲

public:
    UI();                     //コンストラクタ
    bool init();              //初期化
    void update();            //更新
    void draw();              //描画
    void inputdraw();
    void destroy();           //破棄

    int uipov = 0; //十字入力状態描画
    int penter = 0; //A入力状態描画
    int pspace = 0; //B入力状態
    int plb = 0;   //LB入力状態
    int pstart = 0; //start入力状態
};