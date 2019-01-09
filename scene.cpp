#include "scene.h"

bool Scene::init()
{
    if (!(texture_ = Texture::load(L"Tetris19_CRIWARE.png")))
    {
        Error::showDialog("CRIWARE.png‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s");

        return false;

    }

    if (!(texture2_ = Texture::load(L"Tetris20_TeamLogo.png")))
    {
        Error::showDialog("Tetris20_TeamLogo.png‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s");

        return false;

    }
    cri = true;


    return true;
}

bool Scene::update()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();
    if (!koudo)
    {
        cnt++;

    }

    if (cnt > 50||state.Enter||pad.buttons.a)
    {
        koudo = true;
    }

    if (koudo)
    {
        cnt2++;
    }

    if (cnt2 > 50 || state.Enter || pad.buttons.a)
    {
        return false;
    }

    return true;
}

void Scene::draw()
{
    if (cri)
        Sprite::draw(texture_, Vector2::Zero);
    if (koudo)
        Sprite::draw(texture2_, Vector2::Zero);
}

void Scene::destroy()
{
    SAFE_RELEASE(texture_);
    SAFE_RELEASE(texture2_);
}
