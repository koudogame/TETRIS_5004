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

    //�g�̐���
    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            main[i][0] = 9;
            main[i][11] = 9; 
            main[21][j] = 9;

        }
    }

    //�����̃~�m����
    for (int i = 0; i < 7; i++)
    {
        int j = rand() % 7;
        int t = next1[i];
        next1[i] = next1[j];
        next1[j] = t;
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

    //�l�N�X�g�u���b�N�̃p�^�[�����V���b�t��
    if (shuffle)
    {
        for (int i = 0; i < 7; i++)
        {
            next2[i] = next0[i];
        }

        for (int i = 0; i < 7; i++)
        {
            int j = rand() % 7;
            int t = next2[i];
            next2[i] = next2[j];
            next2[j] = t;
        }
        shuffle = false;
    }

    if (shift)
    {
        for (int i = 0; i < 7; i++)
        {
            next1[i] = next1[i+1];

        }
        next1[6] = next2[0];

        for (int i = 0; i < 7; i++)
        {
            next2[i] = next2[i + 1];

        }
        shift = false;
        
    }
    a = next1[0];

    //���݂̎��Ԃ��擾
    nowtime = timeGetTime();
    collision_down = false;
    collision_left = false;
    collision_right = false;

    if (nextblock)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                test[i][j] = mino[a][i][j];
            }
        }
        pos = 3;
        down = 0;
        nextblock = false;
    }

    if (holdf)
    {
        if (!holdbutton)
        {
            if (holdcheck)
            {
                //�z�[���h(2��ڈȍ~)
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        holdtmp[i][j] = test[i][j];
                        test[i][j] = hold[i][j];
                        hold[i][j] = holdtmp[i][j];
                    }
                }
                holdbutton = true;
                pos = 3;
                down = 0;

            }
            else if (!holdcheck)
            {
                //�z�[���h(����)
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        hold[i][j] = test[i][j];
                    }
                }

                shift = true;
                holdcheck = true;
                next++;
                holdbutton = true;

                a = next1[1];
                //���̃u���b�N���o��
                for (int i = 0; i < 4; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        test[i][j] = mino[a][i][j];
                    }
                }
                pos = 3;
                down = 0;
                nextblock = false;

            }
        }
    }

    if (!collision_down)
    {
        //��
        if (state.Down || pad.dpad.down)
        {
            downf = true;
        }
        else
        {
            downf = false;
        }

        if (downf)
        {
            time = 50;
        }
        else
        {
            time = 1;
        }
    }

    //�����蔻��
    //����
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[down + y][pos + (x - 1)] != 0) {
                    collision_left = true;
                }

            }
        }
    }
    //�E��
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[down + y][pos + (x + 1)] != 0) {
                    collision_right = true;
                }

            }
        }
    }
    //����
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[down + y][pos + x] != 0) {
                    collision_down = true;
                }
            }
        }
    }

    //�����������Ă�����ς�
    if (nowtime - oldtime >= 500 && collision_down)
    {
        Accumulate = true;
    }
    else
    {
        Accumulate = false;

    }

    if (!collision_down&&!Accumulate)
    {
        //�����Ԃŗ��Ƃ�
        if (nowtime - oldtime >= 500 / time)
        {
            down++;
            oldtime = nowtime;
        }

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
                clearlinepos[i] = 0;    //�u���b�N�Ŗ��܂��Ă���Ƃ���0
            }
        }
    }

    //�����ꂽ��̗��Ƃ�����
    for (int i = 0; i < 21; i++)
    {
        if (clearlinepos[i] == 0)
        {
            for (int j = 1; j < 11; j++)
            {
                //�z��̏�����
                main[i][j] = 0;
            }
            clearlinepos[i] = 0;

            for (int k = i; k > 0; k--)
            {
                for (int l = 1; l < 11; l++)
                {
                    //�~�m���Ƃ�
                    sub[k][l] = main[k][l];
                    main[k][l] = main[k - 1][l];
                    main[k - 1][l] = sub[k][l];
                }
            }
        }
    }

    if (Accumulate)
    {
        //�ςݏグ
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (test[i][j] != 0 && main[down + i - 1][pos + j] == 0)
                    main[down + i - 1][pos + j] = test[i][j];
            }
        }

        nextblock = true;
        next++;
        shift = true;
        holdbutton = false;
        holdf = false;

        if (next > 6)
        {
            shuffle = true;
            next = 0;
        }
    }

    //�~�m�̃z�[���h
    if (key_tracker.pressed.LeftShift || pad_tracker.leftShoulder == GamePad::ButtonStateTracker::PRESSED)
    {
        holdf = true;
    }

    //��
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {

    }
    if (!collision_left)
    {
        //��
        if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
        {
            pos--;
            Accumulate = false;
            oldtime = timeGetTime();
        }
    }
    if (!collision_right)
    {
        //�E
        if (pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
        {
            pos++;
            Accumulate = false;
            oldtime = timeGetTime();
        }
    }

    if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        rotation_a = true;
    }
    else
    {
        rotation_a = false;
    }

    if (key_tracker.pressed.RightShift || pad_tracker.b == GamePad::ButtonStateTracker::PRESSED)
    {
        rotation_b = true;
    }
    else
    {
        rotation_b = false;
    }

    //T�~�m�͗�O����ŉ�]�����炷
    //��]90
    if (rotation_a && !rotation_b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                test[i][3 - j] = tmp[i][j];
            }
        }

        //for (int i = 0; i < 4; i++)
        //{
        //    for (int j = 0; j < 4; j++)
        //    {
        //        test[i][4 - j] = tmp[i][j];
        //    }
        //}
    }

    //��]270
    if (!rotation_a && rotation_b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                test[3 - i][j] = tmp[i][j];
            }
        }

        //for (int i = 0; i < 4; i++)
        //{
        //    for (int j = 0; j < 4; j++)
        //    {
        //        test[4 - i][j] = tmp[i][j];
        //    }
        //}
    }

    return true;
}

void Mino::draw()
{
    //���F
    RECT rect;
    rect.top = 955;
    rect.left = 687;
    rect.bottom = rect.top + 26;
    rect.right = rect.left + 26;

    //�I�����W
    RECT Ltrim;
    Ltrim.top = 955;
    Ltrim.left = 687 + (25 * 1);
    Ltrim.bottom = Ltrim.top + 26;
    Ltrim.right = Ltrim.left + 26;

    //��
    RECT Strim;
    Strim.top = 955;
    Strim.left = 687 + (25 * 2);
    Strim.bottom = Strim.top + 26;
    Strim.right = Strim.left + 26;

    //��
    RECT Ztrim;
    Ztrim.top = 955;
    Ztrim.left = 687 + (25 * 3);
    Ztrim.bottom = Ztrim.top + 26;
    Ztrim.right = Ztrim.left + 26;

    //��
    RECT Jtrim;
    Jtrim.top = 955;
    Jtrim.left = 687 + (25 * 4);
    Jtrim.bottom = Jtrim.top + 26;
    Jtrim.right = Jtrim.left + 26;

    //���F
    RECT Otrim;
    Otrim.top = 955;
    Otrim.left = 687 + (25 * 5);
    Otrim.bottom = Otrim.top + 26;
    Otrim.right = Otrim.left + 26;

    //��
    RECT Ttrim;
    Ttrim.top = 955;
    Ttrim.left = 687 + (25 * 6);
    Ttrim.bottom = Ttrim.top + 26;
    Ttrim.right = Ttrim.left + 26;

    //�`��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (test[i][j] == 1)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &rect);
            else if (test[i][j] == 2)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Otrim);
            else if (test[i][j] == 3)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ttrim);
            else if (test[i][j] == 4)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Jtrim);
            else if (test[i][j] == 5)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ltrim);
            else if (test[i][j] == 6)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Strim);
            else if (test[i][j] == 7)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ztrim);
        }
    }
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
    rect.bottom = rect.top + 26;
    rect.right = rect.left + 26;

    //���F
    RECT trim;
    trim.top = 955;
    trim.left = 687;
    trim.bottom = trim.top + 26;
    trim.right = trim.left + 26;

    //�I�����W
    RECT Ltrim;
    Ltrim.top = 955;
    Ltrim.left = 687+(25 * 1);
    Ltrim.bottom = Ltrim.top + 26;
    Ltrim.right = Ltrim.left + 26;

    //��
    RECT Strim;
    Strim.top = 955;
    Strim.left = 687 + (25 * 2);
    Strim.bottom = Strim.top + 26;
    Strim.right = Strim.left + 26;

    //��
    RECT Ztrim;
    Ztrim.top = 955;
    Ztrim.left = 687 + (25 * 3);
    Ztrim.bottom = Ztrim.top + 26;
    Ztrim.right = Ztrim.left + 26;

    //��
    RECT Jtrim;
    Jtrim.top = 955;
    Jtrim.left = 687 + (25 * 4);
    Jtrim.bottom = Jtrim.top + 26;
    Jtrim.right = Jtrim.left + 26;

    //���F
    RECT Otrim;
    Otrim.top = 955;
    Otrim.left = 687 + (25 * 5);
    Otrim.bottom = Otrim.top + 26;
    Otrim.right = Otrim.left + 26;

    //��
    RECT Ttrim;
    Ttrim.top = 955;
    Ttrim.left = 687 + (25 * 6);
    Ttrim.bottom = Ttrim.top + 26;
    Ttrim.right = Ttrim.left + 26;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
         if(main[i][j]==9) //�g
            Sprite::draw(texture_, Vector2(510 + (25 * j)-25, 246 + (25 * i) - 75), &rect);
         else if (main[i][j] == 1) //���F
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &trim);
         else if (main[i][j] == 2 ) //���F
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Otrim);
         else if (main[i][j] == 3) //��
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ttrim);
         else if (main[i][j] == 4) //��
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Jtrim);
         else if (main[i][j] == 5) //�I�����W
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ltrim);
         else if (main[i][j] == 6) //��
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Strim);
         else if (main[i][j] == 7) //��
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ztrim);
        }
    }
}

//�l�N�X�g�u���b�N�̕\��
void Mino::nextdraw()
{
    //���F
    RECT trim;
    trim.top = 967;
    trim.left = 913;
    trim.bottom = trim.top + 14;
    trim.right = trim.left + 14;

    //�I�����W
    RECT Ltrim;
    Ltrim.top = 967;
    Ltrim.left = 928;
    Ltrim.bottom = Ltrim.top + 14;
    Ltrim.right = Ltrim.left + 14;

    //��
    RECT Strim;
    Strim.top = 967;
    Strim.left = 943;
    Strim.bottom = Strim.top + 14;
    Strim.right = Strim.left + 14;

    //��
    RECT Ztrim;
    Ztrim.top = 967;
    Ztrim.left = 958;
    Ztrim.bottom = Ztrim.top + 14;
    Ztrim.right = Ztrim.left + 14;

    //��
    RECT Jtrim;
    Jtrim.top = 967;
    Jtrim.left = 973;
    Jtrim.bottom = Jtrim.top + 14;
    Jtrim.right = Jtrim.left + 14;

    //���F
    RECT Otrim;
    Otrim.top = 967;
    Otrim.left = 988;
    Otrim.bottom = Otrim.top + 14;
    Otrim.right = Otrim.left + 14;

    //��
    RECT Ttrim;
    Ttrim.top = 967;
    Ttrim.left = 1003;
    Ttrim.bottom = Ttrim.top + 14;
    Ttrim.right = Ttrim.left + 14;

    //1��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mino[next1[1]][i][j]== 0+1) //���F
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &trim);
            else if (mino[next1[1]][i][j] == 1+1) //���F
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Otrim);
            else if (mino[next1[1]][i][j] == 2+1) //��
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Ttrim);
            else if (mino[next1[1]][i][j] == 3+1) //��
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Jtrim);
            else if (mino[next1[1]][i][j] == 4+1) //�I�����W
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Ltrim);
            else if (mino[next1[1]][i][j] == 5+1) //��
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Strim);
            else if (mino[next1[1]][i][j] == 6+1) //��
                Sprite::draw(texture_, Vector2(610 + (14 * j), 99 + (15 * i)), &Ztrim);
        }
    }

    //2��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mino[next1[2]][i][j] == 0 + 1) //���F
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &trim);
            else if (mino[next1[2]][i][j] == 1 + 1) //���F
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Otrim);
            else if (mino[next1[2]][i][j] == 2 + 1) //��
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Ttrim);
            else if (mino[next1[2]][i][j] == 3 + 1) //��
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Jtrim);
            else if (mino[next1[2]][i][j] == 4 + 1) //�I�����W
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Ltrim);
            else if (mino[next1[2]][i][j] == 5 + 1) //��
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Strim);
            else if (mino[next1[2]][i][j] == 6 + 1) //��
                Sprite::draw(texture_, Vector2(654 + (14 * j), 99 + (15 * i)), &Ztrim);
        }
    }

    //3��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (mino[next1[3]][i][j] == 0 + 1) //���F
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &trim);
            else if (mino[next1[3]][i][j] == 1 + 1) //���F
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Otrim);
            else if (mino[next1[3]][i][j] == 2 + 1) //��
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Ttrim);
            else if (mino[next1[3]][i][j] == 3 + 1) //��
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Jtrim);
            else if (mino[next1[3]][i][j] == 4 + 1) //�I�����W
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Ltrim);
            else if (mino[next1[3]][i][j] == 5 + 1) //��
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Strim);
            else if (mino[next1[3]][i][j] == 6 + 1) //��
                Sprite::draw(texture_, Vector2(699 + (14 * j), 99 + (15 * i)), &Ztrim);
        }
    }
}

//�z�[���h�����u���b�N�̕`��
void Mino::holddraw()
{

    //���F
    RECT trim;
    trim.top = 967;
    trim.left = 913;
    trim.bottom = trim.top + 14;
    trim.right = trim.left + 14;

    //�I�����W
    RECT Ltrim;
    Ltrim.top = 967;
    Ltrim.left = 928;
    Ltrim.bottom = Ltrim.top + 14;
    Ltrim.right = Ltrim.left + 14;

    //��
    RECT Strim;
    Strim.top = 967;
    Strim.left = 943;
    Strim.bottom = Strim.top + 14;
    Strim.right = Strim.left + 14;

    //��
    RECT Ztrim;
    Ztrim.top = 967;
    Ztrim.left = 958;
    Ztrim.bottom = Ztrim.top + 14;
    Ztrim.right = Ztrim.left + 14;

    //��
    RECT Jtrim;
    Jtrim.top = 967;
    Jtrim.left = 973;
    Jtrim.bottom = Jtrim.top + 14;
    Jtrim.right = Jtrim.left + 14;

    //���F
    RECT Otrim;
    Otrim.top = 967;
    Otrim.left = 988;
    Otrim.bottom = Otrim.top + 14;
    Otrim.right = Otrim.left + 14;

    //��
    RECT Ttrim;
    Ttrim.top = 967;
    Ttrim.left = 1003;
    Ttrim.bottom = Ttrim.top + 14;
    Ttrim.right = Ttrim.left + 14;

    //1��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (hold[i][j] == 0 + 1) //���F
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &trim);
            else if (hold[i][j] == 1 + 1) //���F
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Otrim);
            else if (hold[i][j] == 2 + 1) //��
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Ttrim);
            else if (hold[i][j] == 3 + 1) //��
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Jtrim);
            else if (hold[i][j] == 4 + 1) //�I�����W
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Ltrim);
            else if (hold[i][j] == 5 + 1) //��
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Strim);
            else if (hold[i][j] == 6 + 1) //��
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &Ztrim);
        }
    }
}

void Mino::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}

void Mino::reset()
{

}
