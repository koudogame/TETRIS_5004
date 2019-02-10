#pragma once

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
    bool update();      //更新
    void draw();        //描画
    void namedraw();    //名前描画
    void datedraw();
    void destroy();     //破棄

    int menu = 0; //ゲームを終わるときにtrue
    int cnt = 0;

    int name[13] = {8,9,18,15,6,21,13,9,0,19,1,20,15}; //クレジットに描画する自分の名前
    int creation_date[12] = { 2,0,1,9,42,100,1,42,100,2,8 };
};
