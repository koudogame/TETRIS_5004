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
        Error::showDialog("Tetris11_singleT.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ");

        //ƒGƒ‰[
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
    //”jŠü
    SAFE_RELEASE(texture_);
}
