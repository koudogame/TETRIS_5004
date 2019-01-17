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

    //�z��̏�����
    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            main[0][i][j] = 0;

        }
    }

    //�g�̐���
    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            main[0][i][0] = 9;
            main[0][i][11] = 9;
            main[0][22][j] = 9;
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

    //�z�[���h������
    holdcheck = false;
    holdbutton = false;

    //�z�[���h�̔z���������
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            holdtmp[i][j] = 0;
            hold[i][j] = 0;
        }
    }

    nextpattern();
    down = -1;
    pos = 3;
    score = 0;
    fall_speed = SPEED;
    gdown = down;


    nowtime = timeGetTime();
    return true;
}

int Mino::update()
{

    //���݂̎��Ԃ��擾
    nowtime = timeGetTime();

    //�t���O��������
    collision_down = false;

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //�Q�[���I�[�o�[����
    if (main[0][0][5] != 0 && !gameover)
    {
        nextblock = false;
        shift = false;
        overcnt++;
        overcnt2++;

        for (int i = 1; i < 11; i++)
        {
            if (main[0][22 - overcnt][i] != 0)
            {
                main[0][22 - overcnt][i] = 8;
            }
        }

        if (overcnt >= 22)
        {
            overcnt = 0;
        }

        //�Q�[���I�[�o�[���j���[
        if (overcnt2 >= 40)
        {
            return 3;
        }
    }

    //�|�[�Y���j���[
    if (key_tracker.pressed.F1 || pad_tracker.start == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(10);
        return 2;
    }

    //������(�e�X�g�p)
    if (pad_tracker.rightShoulder == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space)
    {
        reset();
        gameover = false;
    }

    //�l�N�X�g
    nextpattern();

    //��
    if (state.Down || pad.dpad.down)
    {
        time = 50;
    }
    else
    {
        time = 1;
    }

    //�����蔻��
    collisiondown();


    //��]�悪���܂��Ă����ꍇ�X�[�p�[���[�e�[�V�����֐��ŕ␳��������
    if (srs)
    {
        srsystem(turnover_rate);
    }

    //�����Ԃŗ��Ƃ�
    if (!collision_down && !Accumulate)
    {
        if (time == 50) //�~�����i�����邩����u�j
        {
            //Adx::play(14);
        }
        if (nowtime - oldtime >= fall_time / (time + fall_speed))
        {
            if (state.Down || pad.dpad.down)
            {
                score++;
            }

            down++;
            oldtime = nowtime;
        }


    }

    //�u���b�N�������ꏊ�̊m�F
    for (int i = 0; i < 22; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (main[0][i][j] == 0)
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

    //���������Ə����ꂽ��̗��Ƃ�����
    for (int i = 0; i < 22; i++)
    {
        if (clearlinepos[i] == 0)
        {

            for (int j = 1; j < 11; j++)
            {
                //�z��̏�����
                main[0][i][j] = 0;
            }
            clearlinepos[i] = 0;

            for (int k = i; k > 0; k--)
            {
                for (int l = 1; l < 11; l++)
                {
                    //�~�m���Ƃ�
                    sub[k][l] = main[0][k][l];
                    main[0][k][l] = main[0][k - 1][l];
                    main[0][k - 1][l] = sub[k][l];
                }
            }
            Adx::play(23);
            erase++;
            erase_line++;
        }
    }

    //�Q�[���N���A
    if (fall_speed == 9 && erase >= 10)
    {
        Adx::stop();

        Adx::play(2);
        return 4;
    }

    //���C���������ŗ������x�ύX
    if (erase >= 10)
    {
        Adx::play(21);
        erase -= 10;
        fall_speed++;
    }

    //�~�m�̃z�[���h
    if (key_tracker.pressed.LeftShift || pad_tracker.leftShoulder == GamePad::ButtonStateTracker::PRESSED)
    {
        change();
    }

    //��(�n�[�h�h���b�v)
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {
        Adx::play(19);

        while (!collision_down)
        {
            down++;
            score += 2;
            //����
            for (int y = 0; y < block_height; y++) {
                for (int x = 0; x < block_width; x++) {
                    if (test[y][x] != 0) {
                        if (main[0][down + y][pos + x] != 0) {
                            collision_down = true;
                        }
                    }
                }
            }
        }

        //�ςݏグ
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (test[i][j] != 0 && main[0][down + i - 1][pos + j] == 0)
                    main[0][down + i - 1][pos + j] = test[i][j];
            }
        }

        //�t���O�X�V
        nextblock = true;
        shift = true;
        holdbutton = false;
        holdf = false;
        next++;
        gdown = down;

        if (next > 6)
        {
            shuffle = true;
            next = 0;
        }
    }

    //���ړ�
    if (state.Left || pad.dpad.left)
    {
        left++;
    }
    if (left % 50 == 7 || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
    {
        left = 0;
        collisionleft();
        collisionsrs();

        if (!collisionf)
        {
            Adx::play(14);
            ghostupdate();
            pos--;
        }
    }

    if (key_tracker.released.Left || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::RELEASED)
    {
        left = 0;
    }
    //�E�ړ�
    if (state.Right || pad.dpad.right)
    {
        right++;
    }
    if (right % 50 == 10 || pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
    {

        right = 0;
        collisionright();
        collisionsrs();

        if (!collisionf)
        {
            Adx::play(14);

            ghostupdate();
            pos++;
        }
    }

    if (key_tracker.released.Right || pad_tracker.dpadRight == GamePad::ButtonStateTracker::RELEASED)
    {
        right = 0;
    }
    //��]270
    if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(15);
        if (Accumulate)
        {
            oldtime = nowtime;
            nowtime = timeGetTime();
        }

        turnover_rate--;

        if (turnover_rate < 0)
        {
            turnover_rate = 3;
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }

        //I��O�~�m�͗�O����ŉ�]�����炷
        if (a != 0 && a != 5)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[4 - i][j] = tmp[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[3 - i][j] = tmp[i][j];
                }
            }
        }
        collisionsrs();
    }

    //��]90
    if (key_tracker.pressed.RightShift || pad_tracker.b == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(15);

        turnover_rate++;
        if (turnover_rate > 3)
        {
            turnover_rate = 0;
        }

        if (Accumulate)
        {
            oldtime = nowtime;
            nowtime = timeGetTime();
        }


        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }

        //I��O�~�m�͗�O����ŉ�]�����炷
        if (a != 0 && a != 5)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[i][4 - j] = tmp[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[i][3 - j] = tmp[i][j];
                }
            }
        }
    }

    //�����������Ă�����ς�
    if (nowtime - oldtime >= fall_time && collision_down)
    {
        Accumulate = true;
    }
    else
    {
        Accumulate = false;
    }

    //�ςݏグ
    if (Accumulate)
    {

        Adx::play(16);

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (test[i][j] != 0 && main[0][down + i - 1][pos + j] == 0)
                    main[0][down + i - 1][pos + j] = test[i][j];
            }
        }

        //�t���O�X�V
        nextblock = true;
        shift = true;
        holdbutton = false;
        holdf = false;
        next++;

        if (next > 6)
        {
            shuffle = true;
            next = 0;
        }
    }

    //�X�R�A�̌v�Z
    if (!erase_line == 0)
    {

        //B2B�̌v�Z
        if (olderasenum == 4 && olderasenum == erase_line)
        {
            back_to_back = 1.5;
        }
        else
        {
            back_to_back = 1;
        }
        //���x�����_�|������������C����
        score += ((fall_speed + 1) * linescore[erase_line - 1])*back_to_back;

        //�X�R�A���
        if (score >= 999999)
        {
            score = 999999;
        }
        olderasenum = erase_line;
        erase_line = 0;
    }

    return 1;
}

//�S�[�X�g�X�V
void Mino::ghostupdate()
{

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    gdown = down;
    gcollsion = false;

    while (!gcollsion)
    {
        //����
        for (int y = 0; y < block_height; y++) {
            for (int x = 0; x < block_width; x++) {
                if (test[y][x] != 0) {
                    if (main[0][gdown + y][pos + x] != 0) {
                        gcollsion = true;
                    }
                }
            }
        }
        if (!gcollsion)
        {
            gdown++;
        }
    }
}

//�����蔻��
//��
void Mino::collisionleft()
{
    collisionf = false;
    //����
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[0][down + y-1][pos + x - 1] != 0) {
                    collisionf = true;
                }
            }
        }
    }
}
//�E
void Mino::collisionright()
{
    collisionf = false;
    //�E��
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[0][down + y-1][pos + x + 1] != 0) {
                    collisionf = true;
                }
            }
        }
    }
}
//��
void Mino::collisiondown()
{
    collision_down = false;
    //����
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[0][down + y][pos + x] != 0 ) {
                    collision_down = true;
                }
            }
        }
    }
}

bool Mino::collisionsrs()
{
    srs = false;
    //�X�[�p�[���[�e�[�V�����p�����蔻��
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[0][down + y - 1][pos + x] != 0) {
                    srs = true;
                    return true;
                }
            }
        }
    }
    return false;
}

//�l�N�X�g�Ăяo��
void Mino::nextpattern()
{
    //�l�N�X�g�u���b�N�̃p�^�[�����V���b�t��
    if (shuffle)
    {
        //���{����R�s�[
        for (int i = 0; i < 7; i++)
        {
            next2[i] = next0[i];
        }

        //�V���b�t��
        for (int i = 0; i < 7; i++)
        {
            int j = rand() % 7;
            int t = next2[i];
            next2[i] = next2[j];
            next2[j] = t;
        }
        shuffle = false;
    }

    //�l�N�X�g�u���b�N�̉��o��
    if (shift)
    {
        for (int i = 0; i < 7; i++)
        {
            next1[i] = next1[i + 1];

        }
        next1[6] = next2[0];
        for (int i = 0; i < 7; i++)
        {
            next2[i] = next2[i + 1];

        }
        shift = false;
    }


    if (nextblock)
    {
        a = next1[0];

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                test[i][j] = mino[a][i][j];
                ghost[i][j] = mino[a][i][j];
            }
        }


        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }
        //T�~�m�͗�O����ŉ�]�����炷
        if (a != 0 && a != 5)
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[i][4 - j] = tmp[i][j];
                }
            }
        }
        else
        {
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    test[i][3 - j] = tmp[i][j];
                }
            }
        }

        pos = 3;
        down = 0;
        nextblock = false;
        gcollsion = false;
        gdown = down;

    }

}

//�X�[�p�[���[�e�[�V����(������)
void Mino::srsystem(int rotation_type)
{
    int step = rotation_type;
    int postmp = pos; //pos��ۑ�
    int downtmp = down; //down��ۑ�
    //*****************
    //A 0�x
    //B 90�x
    //C 180�x
    //D 270�x
    //*****************
    /*if (step < 0 || step>39)
    {
        step = rotation_type;
    }*/

    switch (step)
    {
        //A��D
    case 0:
        if (collisionsrs())
        {
            collisionright();
            if (collisionf)
            {
                pos--;
            }
            collisionleft();
            if (collisionf)
            {
                pos++;
            }
            step = 1;

        }
        else
        {
            step = 40;

        }

        break;
    case 1:
        if (collisionsrs())
        {
            while (srs)
            {
                collisionsrs();
                collisionright();
                if (!collisionf)
                {
                    pos++;

                }
                else
                {
                    break;
                }

            }
            while (srs)
            {
                collisionsrs();
                pos--;

            }

            step = 2;
        }

        break;
    case 2:
        if (collisionsrs())
        {
            down = downtmp;
            pos = postmp;
            
            while (srs)
            {
                collisionsrs();
                collisionright();
                    if (!collisionf)
                    {
                        pos++;

                    }
                    else
                    {
                        break;
                    }

            }
                while (srs)
                {
                    collisionsrs();
                    pos--;

                }

            step = 3;
        }

        break;
    case 3:


        if (collisionsrs())
        {

            while (srs)
            {
                collisionsrs();
                collisionright();
                if (!collisionf)
                {
                    pos++;

                }
                else
                {
                    break;
                }

            }
            while (srs)
            {
                collisionsrs();
                pos--;

            }
            step = 4;
        }

        break;
    case 4:
        if (collisionsrs())
        {
            pos++;
            step = 40;
        }
        break;
        //A��B
    case 5:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            step = 6;
        }

        break;
    case 6:

        if (collisionsrs())
        {
            pos--;

            step = 7;
        }

        break;
    case 7:


        if (collisionsrs())
        {
            down--;

            step = 8;
        }

        break;
    case 8:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down++;
            step = 9;
        }

        break;
    case 9:
        if (collisionsrs())
        {
            pos--;
            step = 40;

        }
        break;
        //B��A(����͂ł��Ă�)
    case 10:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 10;
        }

        break;
    case 11:
        if (collisionsrs())
        {
            pos++;

            step = 12;
        }

        break;
    case 12:
        if (collisionsrs())
        {
            down++;

            step = 13;
        }

        break;
    case 13:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down--;
            step = 14;
        }
  
        break;
    case 14:
        if (collisionsrs())
        {
            pos++;
            step = 40;

        }
        break;
        //B��C
    case 15:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 16;
        }
  
        break;
    case 16:
        if (collisionsrs())
        {
            pos++;

            step = 17;
        }

        break;
    case 17:
        if (collisionsrs())
        {
            down++;

            step = 18;
        }
  

        break;
    case 18:
        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down--;
        }


        break;
    case 19:
        if (collisionsrs())
        {
            pos++;

            step = 40;

        }

        break;
        //C��B
    case 20:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 21;
        }

        break;
    case 21:
        if (collisionsrs())
        {
            pos--;

            step = 21;
        }

        break;
    case 22:
        if (collisionsrs())
        {
            down--;

            step = 23;
        }

    case 23:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down++;
            step = 24;
        }

        break;
    case 24:
        if (collisionsrs())
        {
            pos--;
            step = 40;

        }
        break;
        //C��D
    case 25:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 26;
        }

        break;
    case 26:

        if (collisionsrs())
        {
            pos++;

            step = 27;
        }
 
        break;
    case 27:
        if (collisionsrs())
        {
            down--;

            step = 28;
        }

        break;
    case 28:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down++;
            step = 29;
        }

        break;
    case 29:
        if (collisionsrs())
        {
            pos++;
            step = 40;
        }


        break;
        //D��C
    case 30:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 31;
        }

        break;
    case 31:
        if (collisionsrs())
        {
            pos--;

            step = 32;
        }

        break;
    case 32:
        if (collisionsrs())
        {
            down++;

            step = 33;
        }

        break;
    case 33:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down--;
            step = 34;
        }

        break;
    case 34:
        if (collisionsrs())
        {
            pos--;
            step = 40;

        }

        break;
        //D��A
    case 35:
        pos = postmp; //���̒l�̖߂�
        down = downtmp;
        if (collisionsrs())
        {

            step = 36;
        }

        break;
    case 36:
        if (collisionsrs())
        {
            pos--;

            step = 37;
        }

        break;
    case 37:
        if (collisionsrs())
        {
            down++;

            step = 38;
        }
  
        break;
    case 38:

        if (collisionsrs())
        {
            pos = postmp; //���̒l�̖߂�
            down = downtmp;
            down--;
            step = 39;
        }

        break;
    case 39:
        if (collisionsrs())
        {
            pos--;
            step = 40;

        }
        break;
    default:
        step = rotation_type;

        break;

    }
}

//�z�[���h
void Mino::change()
{

    if (!holdbutton)
    {
        if (holdcheck)
        {
            Adx::play(18);

            //�z�[���h(2��ڈȍ~)
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    holdtmp[i][j] = mino[a][i][j];
                    test[i][j] = hold[i][j];
                    hold[i][j] = holdtmp[i][j];
                }
            }

            holdtmp_a = hold_a;
            hold_a = a;
            a = holdtmp_a;
            holdbutton = true;
            pos = 3;
            down = 0;
        }
        else if (!holdcheck)
        {
            Adx::play(18);

            //�z�[���h(����)
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    hold[i][j] = mino[a][i][j];
                }
            }
            hold_a = a;
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

//���삷����
void Mino::draw(int player_num)
{
    RECT trim;

    //�`��
    if (!gameover)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                trim.top = 955;
                trim.left = 688 + (25 * (test[i][j] - 1));
                trim.bottom = trim.top + 25;
                trim.right = trim.left + 25;

                if (test[i][j] != 0)
                    Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &trim);

            }
        }
    }
}

//�ς݂�������
void Mino::maindraw(int player_num)
{
    RECT trim;

    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {

            trim.top = 955;
            trim.left = 688 + (25 * (main[player_num][i][j] - 1));
            trim.bottom = trim.top + 25;
            trim.right = trim.left + 25;
            if (main[0][i][j] != 0 && main[0][i][j] != 9)
            {
                Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &trim);
            }
        }
    }
}

//�l�N�X�g�u���b�N�̕\��
void Mino::nextdraw(int player_num)
{
    RECT trim;

    //�`��
    for (int l = 1; l < 4; l++)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                trim.top = 967;
                trim.left = 913 + (15 * (mino[next1[l]][i][j] - 1));
                trim.bottom = trim.top + 14;
                trim.right = trim.left + 14;
                if (mino[next1[l]][i][j] != 0)
                {
                    Sprite::draw(texture_, Vector2(565 + (14 * j) + (l * 45), 99 + (15 * i)), &trim);
                }
            }
        }
    }
}

//�z�[���h�����u���b�N�̕`��
void Mino::holddraw(int player_num)
{
    RECT trim;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            trim.top = 967;
            trim.left = 913 + (15 * (hold[i][j] - 1));
            trim.bottom = trim.top + 14;
            trim.right = trim.left + 14;

            if (hold[i][j] != 0)
                Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &trim);
        }
    }
}

//���x���̕`��
void Mino::leveldraw()
{
    RECT trim;

    trim.top = 961;
    trim.left = 16 * fall_speed;
    trim.bottom = trim.top + 21;
    trim.right = trim.left + 16;

    Sprite::draw(texture_, Vector2(730, 42), &trim);

}

//�X�R�A�̕`��
void Mino::scoredraw()
{
	RECT rect;
	rect.top = 961;
	rect.left = 0;
	rect.bottom = rect.top + 21;
	rect.right = rect.left + 16;

    unsigned digit=0; //����

    int tmp = score; //�X�R�A��tmp�ɃR�s�[

    //�����̎Z�o
    while (tmp != 0)
    {
        tmp /= 10;
        digit++;
    }

    tmp = score; //�X�R�A���R�s�[���Ȃ���

    for (int i = 6; i >0; i--)
    {
        rect.left = labs(tmp) % 10 * 16;
        rect.right = rect.left + 16;

        Sprite::draw(texture_, Vector2(542+i*16+i, 42), &rect);
        tmp /= 10;
    }

}

//�N���A�E�B���h�E�̕`��
void Mino::cleardraw()
{

    RECT rect;

    rect.top = 0;
    rect.left = 1280+153;
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558, 274), &rect);
}

//������(�f�o�b�N�p)
void Mino::reset()
{
    //������
    for (int i = 0; i < field_height - 1; i++)
    {
        for (int j = 1; j < field_width - 1; j++)
        {
            main[0][i][j] = 0;
        }
    }
      test[4][4] = { 0 };
      clearlinepos[21] = { 0 }; //����񂻂���Ă���ꏊ�̊m�F�p

    //��]����tmp
      tmp[4][4] = { 0 };

    //���Ԋ֌W
      nowtime = 0; //���݂̎���
      oldtime = 0; //�O��̎���
      time = 1;    //�����ɂ����鎞��

    //�����L�[
      up = 0;   //��
      down = 0; //��
      pos = 3;  //��

    //�J�E���g
      cnt = 0;
      right = 0;
      left = 0;

    //�����蔻��
      collisionf = false;
      collision_down = false;

    //�l�N�X�g
      nextblock = true; //���̃u���b�N���o��
      shuffle = false;  //�l�N�X�g�u���b�N�̔z��v�f���V���b�t��
      shift = false;    //�l�N�X�g�u���b�N�̕`�掞�̃V�t�g�p
      next = 0;          //���̃u���b�N
      a = 0;             //�z��̓Y����

    //�ςݏグ
      Accumulate = false;
      downf = false;

    //�z�[���h�֌W
      holdf = false;        //�z�[���h
      holdcheck = false;    //���łɃz�[���h�����̔���(�z�[���h���Ȃ�true)
      holdbutton = false;   //���łɃz�[���h���g�p�������̔���
      holdtmp[4][4] = { 0 }; //�z�[���htmp
      hold[4][4] = { 0 };    //�z�[���h�p

      srs = false; //�X�[�p�[���[�e�[�V����

    //�Q�[���I�[�o�[�����֌W
      gameover = false; //�Q�[���I�[�o�[�ɂȂ����Ƃ���������
      overcnt = 0; //�Q�[���I�[�o�[�ɂȂ������̒��g�̓���ւ��ϐ�
      overcnt2 = 0; //�Q�[���I�[�o�[�ɂȂ��Ă��烁�j���[���\�������܂ł̎���

    // ������
      erase = 0;
      fall_speed = 1;

    //�S�[�X�g
      transparent = 50;
      ghost[4][4] = { 0 };
      gdown = 0;

      score = 0;
      fall_speed = 0;


      //���{����R�s�[
      for (int i = 0; i < 7; i++)
      {
          next2[i] = next0[i];
      }

      //�V���b�t��
      for (int i = 0; i < 7; i++)
      {
          int j = rand() % 7;
          int t = next2[i];
          next2[i] = next2[j];
          next2[j] = t;
      }
}

//�S�[�X�g�̕`��
void Mino::ghostdraw()
{
    Color color = Color(1.0F, 1.0F, 1.0F, 0.6F);
    RECT trim;

    //�`��
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            trim.top = 955;
            trim.left = 688 + (25 * (test[i][j] - 1));
            trim.bottom = trim.top + 25;
            trim.right = trim.left + 25;

            if (test[i][j] != 0)
            {
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &trim, color);

            }
        }
    }
}

void Mino::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}