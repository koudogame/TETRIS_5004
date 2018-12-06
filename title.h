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

class Title
{
private:

    ID3D11ShaderResourceView* texture_;         //テクスチャ
    ID3D11ShaderResourceView* texture2_;         //テクスチャ
    ID3D11ShaderResourceView* texture3_;         //テクスチャ
    

    Vector2 position_;                                                                                                                                           // 移動速度

public:

    Title();
    ~Title();


    //初期化
    bool init();                                // 初期化
    int update();                               // 更新
    void draw();                                // 描画
    void adraw();                               // 矢印描画
    void destroy();                             // 破棄
    int cnt = 0;                                //大場モード起動コマンドのカウント
    int subcnt = 0;                             //通常モード起動コマンドのカウント
    int menu = 0;

    bool oba = false;                           //大場先生出現
    bool tmp = false;                           //モード切替時のフラグ判定用
};