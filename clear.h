#pragma once

#include"key.h"
#include"pad.h"
#include"sprite.h"
#include"texture.h"
#include"release.h"

class Clear
{
private:
    ID3D11ShaderResourceView* texture_;

public:
    Clear();
    bool init();
    void update(int menu_type);
    void draw();
    void destroy();

    //メニューウィンドウの種類
    int mode = 0;

    //名前入力配列(ファイル出力に変える)
    int name[3] = { 0 };

    //何の文字を入力したか見るよう
    int num = 0;
    int digit = 0;
    
    //入力終了
    bool end = false;

};
