#include "clear.h"

Clear::Clear()
{
}

bool Clear::init()
{

    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_SingleT.png���ǂݍ��߂܂���");

        //�G���[
        return false;
    }

    return true;
}

void Clear::update(int menu_type)
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (!end)
    {
        //�I�[�����x���N���A
        if (mode == 1)
        {
            if ((pad_tracker.a || pad_tracker.b) == GamePad::ButtonStateTracker::PRESSED)
            {
                //���̍��ڂ�
                mode = 2;
            }
        }
        else if (mode == 2) //���O����
        {
            if (!end)
            {
                if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
                {
                    num--;
                }

                if (num < 0)
                {
                    num = 27;
                }
                else if (num > 27)
                {
                    num = 0;
                }

                if (num == 27 && pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)
                {

                    //���̍��ڂ�
                    end = true;
                }
                else if (!num == 27 && pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)
                {
                    name[digit] = num;

                    //���̕�����
                    digit++;
                }

            }
        }
    }
}

void Clear::draw()
{
    RECT rect;
    for (int i = 0; i < 4; i++)
    {

        rect.top = 0;
        rect.left = 1280 + 153;
        rect.bottom = rect.top + 153;
        rect.right = rect.left + 153;

        Sprite::draw(texture_, Vector2(558, 274), &rect);
    }

}

void Clear::destroy()
{
    SAFE_RELEASE(texture_);
}
