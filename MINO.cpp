#include "MINO.h"

Mino::Mino()
{
    texture_ = NULL;
}

bool Mino::init()
{

    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_singleT.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }
    return true;
}

bool Mino::update()
{
    return true;
}

void Mino::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Mino::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}
