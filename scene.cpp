#include "scene.h"

bool Scene::init()
{
    if (!(texture_ = Texture::load(L"Tetris19_CRIWARE.png")))
    {
        Error::showDialog("CRIWARE.png�̓ǂݍ��݂Ɏ��s");

        return false;

    }

    if (!(texture2_ = Texture::load(L"Tetris20_TeamLogo.png")))
    {
        Error::showDialog("Tetris20_TeamLogo.png�̓ǂݍ��݂Ɏ��s");

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
            koudotrans += 0.01F; //�s�����x���C���N�������g

            if (koudotrans >= 1.5F)
            {
                flip = true; //�s�����x���f�N�������g
            }

        }
        else
        {

            koudotrans -= 0.01F;

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
            critrans += 0.01F; //�s�����x����


            if (critrans >= 1.5F)
            {
                flip = true;
            }

        }
        else
        {
            critrans -= 0.01F;

            if (critrans < 0.0F)
            {
                cri = false;
                end = true;
            }
        }
    }


    if ((cri && (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || end))||end)
    {
        return false; //�t�F�[�h�A�E�g�I���Ń^�C�g����
    }

    if (!cri&&(key_tracker.pressed.Enter||pad_tracker.a ==GamePad::ButtonStateTracker::PRESSED))
    {
        koudo = false;
        cri = true; //�{�^���������ꂽ��t�F�[�h���X�L�b�v
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
