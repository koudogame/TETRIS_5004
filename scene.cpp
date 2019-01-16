#include "scene.h"

bool Scene::init()
{
    if (!(texture_ = Texture::load(L"Tetris19_CRIWARE.png")))
    {
        Error::showDialog("CRIWARE.png‚Ì“Ç‚İ‚İ‚É¸”s");

        return false;

    }

    if (!(texture2_ = Texture::load(L"Tetris20_TeamLogo.png")))
    {
        Error::showDialog("Tetris20_TeamLogo.png‚Ì“Ç‚İ‚İ‚É¸”s");

        return false;

    }


    return true;
}

bool Scene::update()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();
    if (koudo)
    {
        cnt++;

        if (!flip)
        {
            if (cnt >= 5)
            {
                koudotrans += 0.03F;
                cnt = 0;
            }

            if (koudotrans >= 1.0F)
            {
                flip = true;
            }

        }
        else
        {
            koudotrans -= 0.03F;

            if (koudotrans <= 0.0F)
            {

                koudo = false;
                cri = true;
                flip = false;

            }
        }
    }

    if (cri)
    {
        cnt2++;

        if (!flip)
        {
            if (cnt2 >= 5)
            {
                critrans += 0.03F;
                cnt2 = 0;
            }

            if (critrans >= 1.0F)
            {
                flip = true;
            }

        }
        else
        {
            if (cnt2 >= 5)
            {
                critrans -= 0.03F;
                cnt2 = 0;
            }

            if (critrans < 0.0F)
            {
                cri = false;
                end = true;
            }
        }
    }


    if (cri && (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || end))
    {
        return false;
    }

    if (!cri&&(key_tracker.pressed.Enter||pad_tracker.a ==GamePad::ButtonStateTracker::PRESSED))
    {
        cri = true;
        critrans = 1.0F;
    }


    return true;
}

void Scene::draw()
{
    RECT rect;
    Color koudocolor = Color(1.0F, 1.0F, 1.0F, koudotrans);
    Color cricolor = Color(1.0F, 1.0F, 1.0F, critrans);
    rect.top = 0;
    rect.left = 0;
    rect.bottom = rect.top + 720;
    rect.right = rect.left + 1280;

    if (cri)
        Sprite::draw(texture_, Vector2::Zero,&rect,cricolor);
    if (koudo)
        Sprite::draw(texture2_, Vector2::Zero,&rect,koudocolor);
}

void Scene::destroy()
{
    SAFE_RELEASE(texture_);
    SAFE_RELEASE(texture2_);
}
