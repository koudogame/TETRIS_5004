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
        Error::showDialog("Tetris11_singleT.png‚ª“Ç‚Ýž‚ß‚Ü‚¹‚ñ");

        //ƒGƒ‰[
        return false;
    }

    oldtime = timeGetTime();
    return true;
}

bool Mino::update()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    nowtime = timeGetTime();

    if (nowtime - oldtime >= 500)
    {
        down++;
        oldtime = nowtime;
    }
    if (state.Left)
    {
        cnt++;
    }
    else
    {
        cnt = 0;
    }

    if (state.Down)
    {
        bcnt++;
    }
    else
    {
        bcnt = 0;
    }

    if (state.Up)
    {
        ccnt++;
    }
    else
    {
        ccnt = 0;
    }

    if (state.Right)
    {
        acnt++;
    }
    else
    {
        acnt = 0;
    }

    if (cnt == 1)
    {
        pos--;
    }
    if (acnt == 1)
    {
        pos++;
    }

    if (bcnt == 1)
    {
        down++;
    }

    if (ccnt == 1)
    {
        up++;
    }
    
    if (down >= 21)
    {
        down = 0;
    }

    if (pos < 0)
    {
        pos = 0;
    }
    if (pos > 9)
    {
        pos = 9;
    }
    return true;
}

void Mino::draw()
{

    RECT rect;
    rect.top = 955;
    rect.left = 687;
    rect.bottom = rect.top + 28;
    rect.right = rect.left + 26;

    Sprite::draw(texture_, Vector2(510+(25*pos),246+(25*down)-(25*up)-75),&rect);
    //x510
    //y246
}

void Mino::destroy()
{
    //”jŠü
    SAFE_RELEASE(texture_);
}
