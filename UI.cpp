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
    cnt = 0;
    carmeter = 0;
    bicyclemeter = 0;

    texture_ = Texture::load(L"field1.png");

    Mtexture_ = Texture::load(L"メーター競合.png");

    Ptexture_ = Texture::load(L"しきり.png");

    if (texture_ == NULL)
    {
        Error::showDialog("ガイド.pngが読み込めません");

        //エラー
        return false;
    }

    if (Mtexture_ == NULL)
    {
        Error::showDialog("メーター競合.pngが読み込めません");

        //エラー
        return false;
    }

    if (Ptexture_ == NULL)
    {
        Error::showDialog("仕切り.pngが読み込めません");

        //エラー
        return false;
    }
    return true;
}

void UI::update()
{
    tmp++;
    const GamePad::State pad = Pad::getState();
    const GamePad::State pad2 = Pad::getState2();
    const Keyboard::State state = Key::getState();

    if (state.Enter || pad.buttons.a)
    {
       Bcnt++;
    }
    else
    {
        Bcnt = 0;
    }

    if (state.Space || pad2.buttons.a)
    {
       cnt++;
    }
    else
    {
        cnt = 0;
    }

    if (cnt == 1)
    {
        //デバック用
        carmeter += SPEED;
        bicyclemeter -= SPEED;
    }

    if (Bcnt == 1)
    {
        //デバック用
        bicyclemeter += SPEED;
        carmeter -= SPEED;
    }
    
    //自動車の過失割合メーターの限度
    if (carmeter > 639)
    {
        carmeter = 639;
    }

    //なおきの過失割合メーターの限度
    if (bicyclemeter > 639)
    {
        bicyclemeter = 639;
    }

}


void UI::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void UI::meterdraw()
{
    RECT rect;

    rect.top = 0;
    rect.left = 640+carmeter-bicyclemeter;
    rect.right = rect.left +1280;
    rect.bottom = rect.top + 100;

    Sprite::draw(Mtexture_, Vector2::Zero, &rect);
}

void UI::partitiondraw()
{
    Sprite::draw(Ptexture_, Vector2::Zero);
}

void UI::destroy()
{
    SAFE_RELEASE(texture_);
    SAFE_RELEASE(Mtexture_);
    SAFE_RELEASE(Ptexture_);
}