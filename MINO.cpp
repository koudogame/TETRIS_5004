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
    fall_speed = 0;
    gdown = down;

    oldtime = timeGetTime();
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
                main[0][22 - overcnt][i] = 10;
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

    //�u���b�N����������
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

    //�����ꂽ��̗��Ƃ�����
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
            erase++;
            erase_line++;
        }
    }

    //�Q�[���N���A
    if (fall_speed == 9 && erase >= 10)
    {
        return 4;
    }

    //���C���������ŗ������x�ύX
    if (erase >= 10)
    {
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
        while (!collision_down)
        {
            down++;
            score++;
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
            ghostupdate();
            pos--;
        }
    }

    //�E�ړ�
    if (state.Right || pad.dpad.right)
    {
        right++;
    }
    if (right % 50 == 7 || pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
    {

        right = 0;
        collisionright();
        collisionsrs();

        if (!collisionf)
        {
            collisionf = false;
            ghostupdate();
            pos++;
        }
    }
    //��]270
    if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        oldtime = nowtime;
        nowtime = timeGetTime();
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

            //T�~�m�͗�O����ŉ�]�����炷
            if (a != 0 && a != 1)
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
        turnover_rate++;
        if (turnover_rate >3 )
        {
            turnover_rate = 0;
        }
        oldtime = nowtime;
        nowtime = timeGetTime();

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = test[j][i];
            }
        }

        //T�~�m�͗�O����ŉ�]�����炷
        if (a != 0 && a != 1)
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
        if (a != 0 && a != 1)
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
                    hold[i][j] = mino[a][i][j];
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

//���삷����
void Mino::draw(int player_num)
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
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &rect);
            else if (test[i][j] == 2)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Otrim);
            else if (test[i][j] == 3)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ttrim);
            else if (test[i][j] == 4)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Jtrim);
            else if (test[i][j] == 5)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ltrim);
            else if (test[i][j] == 6)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Strim);
            else if (test[i][j] == 7)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &Ztrim);
        }
    }
}

//�ς݂�������
void Mino::maindraw(int player_num)
{

    //�g
    RECT rect;
    rect.top = 955;
    rect.left = 687+(25*8);
    rect.bottom = rect.top + 26;
    rect.right = rect.left + 26;

	//�Q�[���I�[�o�[���̒u������
	RECT rect2;
	rect2.top = 955;
	rect2.left = 687 + (25 * 7);
	rect2.bottom = rect2.top + 26;
	rect2.right = rect2.left + 26;

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

    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            if (main[0][i][j] == 9) //�g
            {
                //Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &rect);
            }
            else if (main[0][i][j] == 1) //���F
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &trim);
			else if (main[0][i][j] == 2) //���F
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Otrim);
			else if (main[0][i][j] == 3) //��
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Ttrim);
			else if (main[0][i][j] == 4) //��
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Jtrim);
			else if (main[0][i][j] == 5) //�I�����W
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Ltrim);
			else if (main[0][i][j] == 6) //��
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Strim);
			else if (main[0][i][j] == 7) //��
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &Ztrim);
			else if (main[0][i][j] == 10)
				Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &rect2);
		}
    }
}

//�l�N�X�g�u���b�N�̕\��
void Mino::nextdraw(int player_num)
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
void Mino::holddraw(int player_num)
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
}

//�S�[�X�g�̕`��
void Mino::ghostdraw()
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
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &rect);
            else if (test[i][j] == 2)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Otrim);
            else if (test[i][j] == 3)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Ttrim);
            else if (test[i][j] == 4)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Jtrim);
            else if (test[i][j] == 5)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Ltrim);
            else if (test[i][j] == 6)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Strim);
            else if (test[i][j] == 7)
                Sprite::draw(texture_, Vector2(510 + (25 * pos) + (25 * j) - 25, 246 + (25 * gdown) - (25 * up) - 125 + (25 * i)), &Ztrim);
        }
    }
}

void Mino::destroy()
{
    //�j��
    SAFE_RELEASE(texture_);
}