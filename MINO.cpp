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
        Error::showDialog("Tetris11_singleT.png���ǂݍ��߂܂���");

        //�G���[
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

    //��
    if (pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Down)
    {
        down++;
    }
    //��
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {
        //�n�[�h�h���b�v
        while (main[down + 1][pos + 1] == 0)
        {
            down++;
        }
    }
    //��
    if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
    {
        pos--;
    }
    //�E
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





    //�����Ԃŗ��Ƃ�
    if (nowtime - oldtime >= 500)
    {
        down++;
        oldtime = nowtime;
    }

    if (down > 21)
    {
        down = 0;
    }

 
    //�u���b�N����������
    for (int i = 0; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (main[i][j] == 0)
            {
                clearlinepos[i] = 1;  //�󗓂��m�F 
                break;  //�󗓂��������玟�̍s��
            }
            else
            {
                clearlinepos[i] = 0;    //�u���b�N������Ƃ���0
            }
        }

    }

    for (int i = 1; i < 20; i++)
    {
        if (clearlinepos[i] == 0)
        {
            for (int j = 1; j < 11; j++)
            {
                main[i][j] = 0;
            }
            clearlinepos[i] = 0;
        }
    }

    //�ςݏグ
    if (main[down + 1][pos + 1] != 0)
    {
        main[down][pos + 1] = 1;
        down = 0;
    }

    //�ړ�����
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
    acnt = 0;

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

    //x510
    //y246
}

void Mino::maindraw()
{
    //�ς݂�������

    //�g
    RECT rect;
    rect.top = 955;
    rect.left = 687+(25*8);
    rect.bottom = rect.top + 28;
    rect.right = rect.left + 26;

    //��
    RECT trim;
    trim.top = 955;
    trim.left = 687;
    trim.bottom = trim.top + 28;
    trim.right = trim.left + 26;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
         if(main[i][j]>=9)
            Sprite::draw(texture_, Vector2(510 + (25 * j)-25, 246 + (25 * i) - 75), &rect);
         else if (main[i][j] >= 1)
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &trim);
        }
    }
}

void Mino::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}
