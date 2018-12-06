#pragma once
#include<d3d11.h>
#include<SimpleMath.h>
#include"key.h"
#include"pad.h"
#include"release.h"
#include"texture.h"
#include"sprite.h"
#include"Error.h"

class Field
{
private:
    ID3D11ShaderResourceView* texture_;  // 背景テクスチャ
    RECT trim;
public:
    Field();
    bool init();
    void update(bool oba);
    void draw();
    void draw2();
    void destroy();

    int speed = 10;
    int pos = 0;
    int bicycle = 0;
    int cnt = 0;
};