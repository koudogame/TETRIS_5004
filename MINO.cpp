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
        Error::showDialog("Tetris11_singleT.pngÇ™ì«Ç›çûÇﬂÇ‹ÇπÇÒ");

        //ÉGÉâÅ[
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

    //â∫
    if (pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Down)
    {
        down++;
    }
    //è„
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {
        down--;
    }
    //ç∂
    if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
    {
        pos--;
    }
    //âE
    if (pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
    {
        pos++;
    }

    if (state.Down)
    {
        cnt++;
    }
    else
    {
        cnt = 0;
    }

 

    //é¿éûä‘Ç≈óéÇ∆Ç∑
    if (nowtime - oldtime >= 500)
    {
        down++;
        oldtime = nowtime;
    }

    if (down > 21)
    {
        down = 0;
    }
    
    //êœÇ›è„Ç∞
    if (main[down+1][pos+1]!=0)
    {
        main[down][pos+1] = 1;
        down = 0;
    }

    //à⁄ìÆêßå¿
    if (down < 0)
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

    Sprite::draw(texture_, Vector2(510 + (25 * pos), 246 + (25 * down) - (25 * up) - 75), &rect);

/*
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            Sprite::draw(texture_, Vector2(510 + (25 * pos)+(j*25), 246 + (25 * down) - (25 * up) - 75+(i*25)), &rect);
        }

    }*/

    //x510
    //y246
}

void Mino::maindraw()
{
    //êœÇ›Ç†Ç™ÇÈÇ‚Ç¬

    RECT rect;
    rect.top = 955;
    rect.left = 687;
    rect.bottom = rect.top + 28;
    rect.right = rect.left + 26;
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            if(main[i][j]!=0)
            Sprite::draw(texture_, Vector2(510 + (25 * j)-25, 246 + (25 * i) - 75), &rect);

        }
    }

}

void Mino::destroy()
{
    //îjä¸
    SAFE_RELEASE(texture_);
}
