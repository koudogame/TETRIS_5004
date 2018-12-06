#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include"release.h"

using namespace DirectX;
using namespace SimpleMath;

class TimeLimit
{
private:
    ID3D11ShaderResourceView* texture_;     //テクスチャ
    Vector2 position_;
    DWORD rimit_time_, dif_;
    DWORD start_time_, now_time_;
    static long remaining_;
public:
    TimeLimit();
    ~TimeLimit();

    bool init(const wchar_t* FileName);
    bool update();
    void draw();
    void destroy();

    static int getResultTime() { return remaining_; }
};