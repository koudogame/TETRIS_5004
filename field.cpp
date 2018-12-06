#include "field.h"



Field::Field()
{
    pos = 0;
    speed = 10;
    texture_ = NULL;
}

bool Field::init()
{
    texture_ = Texture::load(L"Tetris01_Single.png");
    speed = 10;

    if (texture_ == NULL)
    {
        Error::showDialog("field1.pngが読み込めません");

        return false;
    }

    return true;
}

void Field::update(bool oba)
{
    cnt++;

    if (cnt % 20 == 0)
    {
        if (oba)
        {
            speed += 2;
        }
        else
        {
            speed++;
        }

        cnt = 0;
    }

    bicycle += 10;
    pos += speed; //座標にスピード分を追加

    if (pos > 1230)
    {
        pos = 0;
    }

    if (bicycle > 1230)
    {
        bicycle = 0;
    }
    if (oba)
    {
        if (speed > 150)
        {
            speed = 150;
        }
    }
    else
    {
        if (speed > 15)
        {
            speed = 15;
        }
    }

}

void Field::draw()
{

    RECT rect;

    rect.top = 0;
    rect.left = 0 + pos;
    rect.right = rect.left + 650;
    rect.bottom = rect.top + 720;

    Sprite::draw(texture_, Vector2::Zero, &rect);

}

void Field::draw2()
{

    RECT rect;

    rect.top =0 ;
    rect.left = 1280 - bicycle;
    rect.right = rect.left + 650;
    rect.bottom = rect.top + 720;

    Sprite::draw(texture_, Vector2(650.0F,0.0F), &rect);

}

void Field::destroy()
{
    SAFE_RELEASE(texture_);

}


