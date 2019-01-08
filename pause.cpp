#include "pause.h"

Pause::Pause()
{
    texture_ = NULL;
}

bool Pause::init()
{
    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ = NULL)
    {
        Error::showDialog("Tetris11_singleT.pngÇ™ì«Ç›çûÇﬂÇ‹ÇπÇÒ");
   
        //ÉGÉâÅ[
        return false;

    }

    return true;
}

int Pause::update()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();


    if (pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt++;
    }
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt--;
    }

    if (menucnt < 0)
    {
        menucnt = 2;
    }
    else if (menucnt > 2)
    {
        menucnt = 0;
    }



    return 1;
}

void Pause::draw()
{

    RECT rect;
    rect.top = 303;
    rect.left = 1280;
    rect.bottom = rect.top + 155;
    rect.right = rect.left + 135;

    Sprite::draw(texture_, Vector2(558+menucnt, 274), &rect);

}

void Pause::cursordraw()
{

    RECT trim;

    trim.top = 957;
    trim.left = 1550;
    trim.bottom = trim.top + 67.5;
    trim.right = trim.left + 498;

    Sprite::draw(texture_, Vector2(400, 108 ), &trim);


}

void Pause::destroy()
{

    SAFE_RELEASE(texture_);

}
