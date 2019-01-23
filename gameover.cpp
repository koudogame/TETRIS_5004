#include "gameover.h"

bool Gameover::init()
{

    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_singleT.pngÇ™ì«Ç›çûÇﬂÇ‹ÇπÇÒ");

        //ÉGÉâÅ[
        return false;
    }

    return true;
}

void Gameover::update()
{
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (key_tracker.pressed.A || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        menucnt++;
    }
}

void Gameover::draw()
{
    if (menucnt == 1)
    {
        RECT rect;
        rect.top = 0;
        rect.left = 1739;
        rect.bottom = rect.top + 153;
        rect.right = rect.left + 153;
    }

}

void Gameover::destroy()
{
    SAFE_RELEASE(texture_);
}
