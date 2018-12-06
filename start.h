#pragma once

#include<d3d11.h>
#include"release.h"
#include"player.h"

class Start
{
private:
    ID3D11ShaderResourceView* texture1_;         //1p準備完了
    ID3D11ShaderResourceView* texture2_;         //2p準備完了
    ID3D11ShaderResourceView* texture3_;         //両方準備中
    ID3D11ShaderResourceView* texture4_;         //両方準備完了

public:

    Start();
    ~Start();

    //初期化
    bool init();                                //初期化
    bool update();                              //更新
    void draw();                                //描画
    void destroy();                             //破棄

    //フラグ
    bool p1 = false;
    bool p2 = false;
	bool complete = false;

    //カウント
    int cnt = 0;
};