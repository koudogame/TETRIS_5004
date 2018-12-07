#pragma once

#include<d3d11.h>
#include"release.h"
#include"player.h"
#include"key.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"Error.h"
#include"pov.h"


class Title
{
private:

    ID3D11ShaderResourceView* texture_;         //テクスチャ
    

    Vector2 position_;                                                                                                                                           // 移動速度

public:

    Title();
    ~Title();


    //初期化
    bool init();                                // 初期化
    int update();                               // 更新
    void draw();                                // 背景描画
    void dpaddraw();                            // 十字キー描画
    void buttondraw();                          // ボタン描画
    void cursordraw();                          //カーソル描画
    void destroy();                             // 破棄
    int menu = 0;

    bool tmp = false;                           //モード切替時のフラグ判定用
    int penter = 0;                             //決定が押された
    int pov = 0;

};