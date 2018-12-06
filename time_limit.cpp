#include"time_limit.h"
#include<ctime>
#include<cstdio>
#include"texture.h"
#include"sprite.h"

long TimeLimit::remaining_;

TimeLimit::TimeLimit()
{
    texture_ = NULL;
    rimit_time_ = 0UL;
    start_time_ = 0UL;

    position_.x = 608.0F;
    position_.y = 0.0F;
}

TimeLimit::~TimeLimit()
{
}

bool TimeLimit::init(const wchar_t* FileName)
{
    Texture tex;
    texture_ = tex.load(FileName);

    if (texture_ == NULL)
    {
        //エラー
        return false;
    }

    rimit_time_ = 25000UL; //時間制限
    start_time_ = timeGetTime();

    return true;
}

bool TimeLimit::update()
{
    now_time_ = timeGetTime();          // 現在の時間
    dif_ = now_time_ - start_time_;     // 前回の更新からの差分を計算

    remaining_ = rimit_time_ - dif_;    // 残り時間

    // タイムリミットを超過した場合
    if (dif_ >= rimit_time_)
    {
        return false;
    }

    return true;
}

void TimeLimit::draw()
{
    RECT rect;  // 数字の描画範囲

    rect.top = 0;
    rect.left = 0;
    rect.right = rect.left + 32;
    rect.bottom = rect.top + 64;

    unsigned digit = 0;     // 残り時間の桁数
    long tmp = remaining_;
    // 桁数の算出
    while (tmp != 0) {
        tmp /= 10;
        digit++;
    }

    tmp = remaining_;

    XMVECTORF32 color = Colors::White;
    // タイムリミットを超過した場合
    if (dif_ >= rimit_time_)
    {

    }

    for (int i = digit; i > 0; i--)
    {
        rect.left = labs(tmp) % 10 * 32;    // 10で割った余り（下一桁）
        rect.right = rect.left + 32;

        Sprite::draw(texture_, Vector2(position_.x + i * 32 - digit * 16, position_.y), &rect);
        tmp /= 10;
    }
}

//破棄
void TimeLimit::destroy()
{
    SAFE_RELEASE(texture_);
}