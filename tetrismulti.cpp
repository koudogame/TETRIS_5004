#include "tetrismulti.h"

Tetrismulti::Tetrismulti()
{
    texture_ = NULL;
}

bool Tetrismulti::init()
{

    texture_ = Texture::load(L"Tetris14_Versus.png");


    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_Versus.png‚ª“Ç‚İ‚ß‚Ü‚¹‚ñ");

        //ƒGƒ‰[
        return false;
    }

    return true;
}

int Tetrismulti::update()
{
    for (int i = 0; i < 4; i++)
    {
    }



    return 1;
}

//”wŒi
void Tetrismulti::draw()
{
    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_,Vector2::Zero, &rect);

}

void Tetrismulti::destroy()
{
    SAFE_RELEASE(texture_);
}
