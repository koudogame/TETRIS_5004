#include "option.h"

bool Option::init()
{
    //テクスチャの読み込み
    if (!(texture_ = Texture::load(L"Tetris16_Option.png")))
    {

        Error::showDialog("Tetris16_Option.pngの読み込みに失敗");

        //エラー
        return false;
    }

    return true;
}

bool Option::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (pad.buttons.start)
    {
        pstart = 1;
        return false;
    }
    else
    {
        pstart = 0;
    }

    if (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)
    {
    }

    return true;
}

void Option::draw()
{
    RECT rect;
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    Sprite::draw(texture_, Vector2::Zero);
}

void Option::buttondraw()
{


    RECT btrim;
    btrim.top = 463;
    btrim.left = 1536;
    btrim.bottom = btrim.top + 129;
    btrim.right = btrim.left + 128;


    Sprite::draw(texture_, Vector2(1002, 519), &btrim);

    //STARTボタン
    RECT strim;
    strim.top = 336 + (pstart * 64);
    strim.left = 1920;
    strim.bottom = strim.top + 64;
    strim.right = strim.left + 128;

    Sprite::draw(texture_, Vector2(1063, 82), &strim);
}

void Option::dpaddraw()
{
    RECT trim;

    trim.top = 725;
    trim.left = 5;
    trim.bottom = trim.top + 220;
    trim.right = trim.left + 220;


    Sprite::draw(texture_, Vector2(49, 425), &trim);

}

void Option::destroy()
{

    SAFE_RELEASE(texture_);
}
