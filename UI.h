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
enum
{
    NOT_FOUND,
    Title_,          //タイトル
    rank_credit,    //ランキング・クレジット
    result_option,  //リザルトオプション
    tetoris_s,      //テトリスシングル
    puyopuyo,       //ぷよぷよ
    tetris_multi    //テトリスマルチ
};

class UI
{
private:
    ID3D11ShaderResourceView* texture_;  // UIテクスチャ

public:
    UI();                     //コンストラクタ
    bool init();              //初期化
    void update();            //更新
    void draw(int type);              //描画
    void inputdraw(int type);
    void Hiddendraw();
    void destroy();           //破棄

    //入力状態
    int uipov = 0; //十字入力状態描画
    int penter = 0; //A入力状態描画
    int pspace = 0; //B入力状態
    int plb = 0;   //LB入力状態
    int pstart = 0; //start入力状態
};