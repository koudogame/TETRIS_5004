#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include"key.h"
#include"pad.h"
#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"Error.h"

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
    void meterdraw();         //メーター描画
    void partitiondraw();     //仕切り描画
    void destroy();           //破棄

    int cnt = 0;            //押された瞬間取得用
    int Bcnt = 0;           //押された瞬間取得用
    int carmeter = 0;       //連打メーター(車)
    int bicyclemeter = 0;   //連打メーター(自転車)
    int tmp = 0;            //自動車減算カウント
};