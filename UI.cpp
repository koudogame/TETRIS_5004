#include "UI.h"

UI::UI()
{
    cnt = 0;
    carmeter=0;
    bicyclemeter = 0;
    texture_ = NULL;
    Mtexture_ = NULL;
    Ptexture_ = NULL;
}

bool UI::init()
{
    //リトライ時の初期化に使用


    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_singleT.pngが読み込めません");

        //エラー
        return false;
    }

    return true;
}

void UI::update()
{
    tmp++;
    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    if (state.Enter || pad.buttons.a)
    {
       Bcnt++;
    }
    else
    {
        Bcnt = 0;
    }

}


void UI::draw()
{
    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_, Vector2::Zero);
}

void UI::destroy()
{
    SAFE_RELEASE(texture_);
}