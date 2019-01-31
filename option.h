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
    void cursordraw();  //上下のカーソル
    void opdraw();      //オプションの矢印
    void destroy();     //破棄

    int pstart = 0;

    int opmenu = 0;

    int difficulty;
    int hold; 
    int next;
    int hidden;
    int vs;
    int reverse;
    int score;

    int option[7];
};