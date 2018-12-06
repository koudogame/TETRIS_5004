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
        //�G���[
        return false;
    }

    rimit_time_ = 25000UL; //���Ԑ���
    start_time_ = timeGetTime();

    return true;
}

bool TimeLimit::update()
{
    now_time_ = timeGetTime();          // ���݂̎���
    dif_ = now_time_ - start_time_;     // �O��̍X�V����̍������v�Z

    remaining_ = rimit_time_ - dif_;    // �c�莞��

    // �^�C�����~�b�g�𒴉߂����ꍇ
    if (dif_ >= rimit_time_)
    {
        return false;
    }

    return true;
}

void TimeLimit::draw()
{
    RECT rect;  // �����̕`��͈�

    rect.top = 0;
    rect.left = 0;
    rect.right = rect.left + 32;
    rect.bottom = rect.top + 64;

    unsigned digit = 0;     // �c�莞�Ԃ̌���
    long tmp = remaining_;
    // �����̎Z�o
    while (tmp != 0) {
        tmp /= 10;
        digit++;
    }

    tmp = remaining_;

    XMVECTORF32 color = Colors::White;
    // �^�C�����~�b�g�𒴉߂����ꍇ
    if (dif_ >= rimit_time_)
    {

    }

    for (int i = digit; i > 0; i--)
    {
        rect.left = labs(tmp) % 10 * 32;    // 10�Ŋ������]��i���ꌅ�j
        rect.right = rect.left + 32;

        Sprite::draw(texture_, Vector2(position_.x + i * 32 - digit * 16, position_.y), &rect);
        tmp /= 10;
    }
}

//�j��
void TimeLimit::destroy()
{
    SAFE_RELEASE(texture_);
}