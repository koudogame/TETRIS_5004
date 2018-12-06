#include "scene.h"

bool Scene::init()
{
    if (!(texture_ = Texture::load(L"Tetris19_CRIWARE.png")))
    {
        Error::showDialog("CRIWARE.png‚Ì“Ç‚Ýž‚Ý‚ÉŽ¸”s");

        return false;

    }


    return true;
}

bool Scene::update()
{
    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    cnt++;

    if (cnt > 70||state.Enter||pad.buttons.a)
    {
        return false;
    }

    return true;
}

void Scene::draw()
{
    Sprite::draw(texture_, Vector2::Zero);
}

void Scene::destroy()
{
    SAFE_RELEASE(texture_);
}
