#include "MINO.h"

Mino::Mino()
{
    texture_ = NULL;
}

bool Mino::init(int player_num)
{

    texture_ = Texture::load(L"Tetris11_SingleT.png");

    if (!gameover_.init()) { return false; }

    if (texture_ == NULL)
    {
        Error::showDialog("Tetris11_singleT.pngが読み込めません");

        //エラー
        return false;
    }

    //配列の初期化
    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            main[player_num][i][j] = 0;

        }
    }

    //枠の生成
    for (int i = 0; i < field_height; i++)
    {
        for (int j = 0; j < field_width; j++)
        {
            main[player_num][i][0] = 9;
            main[player_num][i][11] = 9;
            main[player_num][22][j] = 9;
        }
    }

    //初期のミノ決定
    for (int i = 0; i < 7; i++)
    {
        int j = rand() % 7;
        int t = next1[i];
        next1[i] = next1[j];
        next1[j] = t;
    }

    for (int i = 0; i < 7; i++)
    {
        int j = rand() % 7;
        int t = next2[i];
        next2[i] = next2[j];
        next2[j] = t;
    }

    //ホールド初期化
    holdcheck = false;
    holdbutton = false;

    //ホールドの配列を初期化
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            holdtmp[i][j] = 0;
            hold[i][j] = 0;
        }
    }
    pos = 3;
    score = 0;
    fall_speed = SPEED;
    gdown = down;
    down = -1;
    first = true;
    op_bonus = 1.0;

    nowtime = timeGetTime();

    FILE* fp = fopen("option.txt", "r");
    if (fp == NULL)
    {
        Error::showDialog("option.txtの読み込みに失敗");
        PostQuitMessage(0);
    }

    int optiontxt;
    //optionの内容を反映
    int num = 0;

    while (fscanf(fp, "%d", &optiontxt) != NULL)
    {
        option[num] = optiontxt;
        if (num == 7) //なんかとまらなかったからbreak
        {
            break;
        }
        num++;
    }

    //レベル上限
    if (option[0] == 0)
    {
        maxlevelop = 6;
    }
    else
    {
        maxlevelop = 9;
    }

    //ホールド使用設定
    if (option[1] == 0)
    {
        holdop = true;
    }
    else
    {
        op_bonus += 0.5;
        holdop = false;
    }

    if (option[2] == 3)
    {
        nextop = 0;
    }
    else if (option[2] == 2)
    {
        op_bonus += 0.25;
        nextop = 1;
    }
    else if (option[2] == 1)
    {
        op_bonus += 0.5;
        nextop = 2;
    }
    else
    {
        op_bonus += 1.0;
        nextop = 3;
    }

    if (option[3] == 0)
    {
        hidden = false;
    }
    else
    {
        op_bonus += 5.0;
        hidden = true;
    }

    if (option[5] == 0)
    {
        reverseop = false;
    }
    else
    {
        op_bonus += 2.5;
        reverseop = true;
    }

    return true;
}

int Mino::update(int player_num)
{

    //現在の時間を取得
    nowtime = timeGetTime();

    //フラグを初期化
    collision_down = false;

    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    clearline = 0;

    //全消しの確認
    allclear(player_num);


    //ゲームオーバー処理
    if (main[player_num][0][5] != 0)
    {
        nextblock = false;
        shift = false;
        overcnt++;
        overcnt2++;
        gameover = true;
        if (overcnt2 == 1)
        {
            Adx::stop();

            Adx::play(7);
        }
        for (int i = 1; i < 11; i++)
        {
            if (main[player_num][22 - overcnt][i] != 0)
            {
                main[player_num][22 - overcnt][i] = 8;
            }
        }

        if (overcnt >= 22)
        {
            overcnt = 0;
        }

        //ゲームオーバーメニュー
        if (overcnt2 >= 200)
        {
            gameover_.draw();
            gameover_.rankdraw(fall_speed);
            gameover_.scoredraw(score);
            gameover_.update();
        }
    }
    if (!gameover)
    {

        //ポーズメニュー
        if (key_tracker.pressed.F1 || pad_tracker.start == GamePad::ButtonStateTracker::PRESSED)
        {
            Adx::play(10);
            return 2;
        }

        //初期化(テスト用)
        if (pad_tracker.rightShoulder == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space)
        {
            reset(player_num);
            gameover = false;
        }

        //ネクスト
        nextpattern();

        //下
        if (state.Down || pad.dpad.down)
        {
            time = 50;
        }
        else
        {
            time = 1;
        }

        //当たり判定
        collisiondown(player_num);


        //回転先が埋まっていた場合スーパーローテーション関数で補正をかける
        if (srs)
        {
            srsystem(turnover_rate, player_num);
        }

        //実時間で落とす
        if (!collision_down && !Accumulate)
        {

            if (nowtime - oldtime >= fall_time / (time + fall_speed))
            {
                if (state.Down || pad.dpad.down)
                {
                    score++;
                }

                if (time == 50) //降下音（消えるから放置）
                {
                    Adx::play(14);
                }
                down++;
                oldtime = nowtime;
            }


        }

        //ブロックを消す場所の確認
        for (int i = 0; i < 22; i++)
        {
            for (int j = 1; j < 11; j++)
            {
                if (main[player_num][i][j] == 0)
                {
                    clearlinepos[i] = 1;  //空欄を確認 
                    break;  //空欄があったら次の行へ
                }
                else
                {
                    clearlinepos[i] = 0;    //ブロックで埋まっているときは0
                }
            }
        }

        //消す処理と消された後の落とす処理
        for (int i = 0; i < 22; i++)
        {
            if (clearlinepos[i] == 0)
            {

                for (int j = 1; j < 11; j++)
                {
                    //配列の初期化
                    main[player_num][i][j] = 0;
                }
                clearlinepos[i] = 0;

                for (int k = i; k > 0; k--)
                {
                    for (int l = 1; l < 11; l++)
                    {
                        //ミノ落とし
                        sub[k][l] = main[player_num][k][l];
                        main[player_num][k][l] = main[player_num][k - 1][l];
                        main[player_num][k - 1][l] = sub[k][l];
                    }
                }
                Adx::play(2);
                erase++;
                erase_line++;
            }
        }

        //ゲームクリア
        if (fall_speed == maxlevelop && erase >= 10)
        {
            Adx::stop();

            Adx::play(23);
            return 4;
        }

        //ライン消去数で落下速度変更
        if (erase >= 10)
        {
            Adx::play(6);
            erase -= 10;
            fall_speed++;
        }

        //ミノのホールド
        if (key_tracker.pressed.LeftShift || pad_tracker.leftShoulder == GamePad::ButtonStateTracker::PRESSED)
        {
            if (holdop)
            {
                change();
            }
        }

        //上(ハードドロップ)
        if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
        {
            Adx::play(4);

            while (!collision_down)
            {
                down++;
                score += 2;
                //下側
                for (int y = 0; y < block_height; y++) {
                    for (int x = 0; x < block_width; x++) {
                        if (test[y][x] != 0) {
                            if (main[player_num][down + y][pos + x] != 0) {
                                collision_down = true;
                            }
                        }
                    }
                }
            }

            //積み上げ
            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (test[i][j] != 0 && main[player_num][down + i - 1][pos + j] == 0)
                        main[player_num][down + i - 1][pos + j] = test[i][j];
                }
            }

            //フラグ更新
            nextblock = true;
            shift = true;
            holdbutton = false;
            holdf = false;
            next++;
            gdown = down;

            if (first)
            {
                first = false;
            }

            if (next > 6)
            {
                shuffle = true;
                next = 0;
            }
        }

        //左移動
        if (state.Left || pad.dpad.left)
        {
            if (reverseop)
            {
                right++;
            }
            else
            {
                left++;

            }
        }

        if (!reverseop)
        {
            if (left % 50 == 10 || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
            {
                left = 0;
                collisionleft(player_num);
                collisionsrs(player_num);

                if (!collisionf)
                {
                    Adx::play(14);
                    ghostupdate(player_num);
                    pos--;
                }
            }
        }
        else //リバース
        {
            if (left % 50 == 10 || pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
            {
                left = 0;
                collisionleft(player_num);
                collisionsrs(player_num);

                if (!collisionf)
                {
                    Adx::play(14);
                    ghostupdate(player_num);
                    pos--;
                }
            }
        }


        if (key_tracker.released.Left || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::RELEASED)
        {
            if (reverseop)
            {
                left = 0;
            }
            else
            {
                right = 0;
            }
        }
        //右移動
        if (state.Right || pad.dpad.right)
        {
            if (reverseop)
            {
                left++;
            }
            else
            {
                right++;
            }
        }
        if (!reverseop)
        {
            if (right % 50 == 10 || pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
            {

                right = 0;
                collisionright(player_num);
                collisionsrs(player_num);

                if (!collisionf)
                {
                    Adx::play(14);

                    ghostupdate(player_num);
                    pos++;
                }
            }
        }
        else //リバース
        {
            if (right % 50 == 10 || pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
            {

                right = 0;
                collisionright(player_num);
                collisionsrs(player_num);

                if (!collisionf)
                {
                    Adx::play(14);

                    ghostupdate(player_num);
                    pos++;
                }
            }
        }


        if (key_tracker.released.Right || pad_tracker.dpadRight == GamePad::ButtonStateTracker::RELEASED)
        {
            if (reverseop)
            {
                left++;
            }
            else
            {
                right = 0;
            }
        }
        //回転270
        if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
        {
            Adx::play(0);
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

            //IとOミノは例外判定で回転軸ずらす
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
            collisionsrs(player_num);
        }

        //回転90
        if (key_tracker.pressed.RightShift || pad_tracker.b == GamePad::ButtonStateTracker::PRESSED)
        {
            Adx::play(0);

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

            //IとOミノは例外判定で回転軸ずらす
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

        //下が当たっていたら積む
        if (nowtime - oldtime >= fall_time - 300 && collision_down)
        {
            Accumulate = true;
        }
        else
        {
            Accumulate = false;
        }

        //積み上げ
        if (Accumulate)
        {

            Adx::play(1);

            for (int i = 0; i < 4; i++)
            {
                for (int j = 0; j < 4; j++)
                {
                    if (test[i][j] != 0 && main[player_num][down + i - 1][pos + j] == 0)
                        main[player_num][down + i - 1][pos + j] = test[i][j];
                }
            }

            //フラグ更新
            nextblock = true;
            shift = true;
            holdbutton = false;
            holdf = false;
            next++;
            if (first)
            {
                first = false;
            }
            if (next > 7)
            {
                shuffle = true;
                next = 0;
            }
        }

        //スコアの計算
        if (!erase_line == 0)
        {

            //B2Bの計算
            if (olderasenum == 4 && olderasenum == erase_line)
            {
                back_to_back = 1.5;
            }
            else
            {
                back_to_back = 1;
            }
            //レベル得点掛ける消えたライン数
            if (!all_clear)
            {
                score += ((fall_speed + 1) * linescore[erase_line - 1])*back_to_back*op_bonus;
            }
            else
            {
                score += ((fall_speed + 1) * linescore[erase_line - 1])*back_to_back * 10 * op_bonus;
                all_clear = false;
            }

            //スコア上限
            if (score >= 999999)
            {
                score = 999999;
            }

            olderasenum = erase_line;
            erase_line = 0;
        }

    }
    return 1;

}

//ゴースト更新
void Mino::ghostupdate(int player_num)
{
    gdown = down;
    gcollsion = false;

    while (!gcollsion)
    {
        //下側
        for (int y = 0; y < block_height; y++) {
            for (int x = 0; x < block_width; x++) {
                if (test[y][x] != 0) {
                    if (main[player_num][gdown + y][pos + x] != 0) {
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

//当たり判定
//左
void Mino::collisionleft(int player_num)
{
    collisionf = false;
    //左側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[player_num][down + y-1][pos + x - 1] != 0) {
                    collisionf = true;
                }
            }
        }
    }
}
//右
void Mino::collisionright(int player_num)
{
    collisionf = false;
    //右側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[player_num][down + y-1][pos + x + 1] != 0) {
                    collisionf = true;
                }
            }
        }
    }
}
//下
void Mino::collisiondown(int player_num)
{
    collision_down = false;
    //下側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[player_num][down + y][pos + x] != 0 ) {
                    collision_down = true;
                }
            }
        }
    }
}
//srs用
bool Mino::collisionsrs(int player_num)
{
    srs = false;
    //スーパーローテーション用当たり判定
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (test[y][x] != 0) {
                if (main[player_num][down + y - 1][pos + x] != 0) {
                    srs = true;
                    return true;
                }
            }
        }
    }
    return false;
}

//ネクスト呼び出し
void Mino::nextpattern()
{


    //ネクストブロックの押出し
    if (shift)
    {
        if (!shuffle)
        {
            for (int i = 0; i < 6; i++)
            {
                next1[i] = next1[i + 1];

            }
            next1[6] = next2[0];
            for (int i = 0; i < 6; i++)
            {
                next2[i] = next2[i + 1];

            }
        }

        shift = false;
    }
    //ネクストブロックのパターンをシャッフル
    if (shuffle)
    {
        //見本からコピー
        for (int i = 0; i < 7; i++)
        {
            next2[i] = next0[i];
        }

        //シャッフル
        for (int i = 0; i < 7; i++)
        {
            int j = rand() % 7;
            int t = next2[i];
            next2[i] = next2[j];
            next2[j] = t;
        }
        shuffle = false;
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
        //Tミノは例外判定で回転軸ずらす
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

void Mino::allclear(int player_num)
{
    //全消しの確認
    for (int i = 0; i < 22; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (main[player_num][i][j] != 0)
            {
                leaveline[i] = 1;  //ブロックを確認 
                break;  //ブロックがあったら次の行へ
            }
            else
            {
                leaveline[i] = 0;
            }
        }
    }

    for (int i = 0; i < 22; i++)
    {
        if (leaveline[i] == 0)
        {
            clearline++;
        }
    }

    if (clearline == 22 && !first)
    {
        all_clear = true;
    }

}

//スーパーローテーション(未完成)
void Mino::srsystem(int rotation_type, int player_num)
{
    int step = rotation_type;
    int postmp = pos; //posを保存
    int downtmp = down; //downを保存
    //*****************
    //A 0度
    //B 90度
    //C 180度
    //D 270度
    //*****************
    /*if (step < 0 || step>39)
    {
        step = rotation_type;
    }*/

    switch (step)
    {
        //A→D
    case 0:
        if (collisionsrs(player_num))
        {
            collisionright(player_num);
            if (collisionf)
            {
                pos--;
            }
            collisionleft(player_num);
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
        if (collisionsrs(player_num))
        {

            collisionsrs(player_num);
            collisionleft(player_num);
            if (!collisionf)
            {
                pos++;

            }
            else
            {
                break;
            }

            if (!collisionf)
            {
                collisionsrs(player_num);
                pos--;
            }

            step = 2;
        }

        break;
    case 2:
        if (collisionsrs(player_num))
        {
            down = downtmp;
            pos = postmp;

            pos--;


            step = 3;
        }
        else
        {
            break;
        }
        break;
    case 3:


        if (collisionsrs(player_num))
        {

            pos++;


            step = 4;
        }

        else
        {
            break;
        }

        break;
    case 4:
        if (collisionsrs(player_num))
        {
            pos++;
            step = 40;
        }
        break;
        //A→B
    case 5:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            step = 6;
        }

        break;
    case 6:

        if (collisionsrs(player_num))
        {
            pos--;

            step = 7;
        }

        break;
    case 7:


        if (collisionsrs(player_num))
        {
            down--;

            step = 8;
        }

        break;
    case 8:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down++;
            step = 9;
        }

        break;
    case 9:
        if (collisionsrs(player_num))
        {
            pos--;
            step = 40;

        }
        break;
        //B→A(これはできてる)
    case 10:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 10;
        }

        break;
    case 11:
        if (collisionsrs(player_num))
        {
            pos++;

            step = 12;
        }

        break;
    case 12:
        if (collisionsrs(player_num))
        {
            down++;

            step = 13;
        }

        break;
    case 13:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down--;
            step = 14;
        }

        break;
    case 14:
        if (collisionsrs(player_num))
        {
            pos++;
            step = 40;

        }
        break;
        //B→C
    case 15:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 16;
        }

        break;
    case 16:
        if (collisionsrs(player_num))
        {
            pos++;

            step = 17;
        }

        break;
    case 17:
        if (collisionsrs(player_num))
        {
            down++;

            step = 18;
        }


        break;
    case 18:
        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down--;
        }


        break;
    case 19:
        if (collisionsrs(player_num))
        {
            pos++;

            step = 40;

        }

        break;
        //C→B
    case 20:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 21;
        }

        break;
    case 21:
        if (collisionsrs(player_num))
        {
            pos--;

            step = 21;
        }

        break;
    case 22:
        if (collisionsrs(player_num))
        {
            down--;

            step = 23;
        }

    case 23:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down++;
            step = 24;
        }

        break;
    case 24:
        if (collisionsrs(player_num))
        {
            pos--;
            step = 40;

        }
        break;
        //C→D
    case 25:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 26;
        }

        break;
    case 26:

        if (collisionsrs(player_num))
        {
            pos++;

            step = 27;
        }

        break;
    case 27:
        if (collisionsrs(player_num))
        {
            down--;

            step = 28;
        }

        break;
    case 28:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down++;
            step = 29;
        }

        break;
    case 29:
        if (collisionsrs(player_num))
        {
            pos++;
            step = 40;
        }


        break;
        //D→C
    case 30:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 31;
        }

        break;
    case 31:
        if (collisionsrs(player_num))
        {
            pos--;

            step = 32;
        }

        break;
    case 32:
        if (collisionsrs(player_num))
        {
            down++;

            step = 33;
        }

        break;
    case 33:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down--;
            step = 34;
        }

        break;
    case 34:
        if (collisionsrs(player_num))
        {
            pos--;
            step = 40;

        }

        break;
        //D→A
    case 35:
        pos = postmp; //元の値の戻す
        down = downtmp;
        if (collisionsrs(player_num))
        {

            step = 36;
        }

        break;
    case 36:
        if (collisionsrs(player_num))
        {
            pos--;

            step = 37;
        }

        break;
    case 37:
        if (collisionsrs(player_num))
        {
            down++;

            step = 38;
        }

        break;
    case 38:

        if (collisionsrs(player_num))
        {
            pos = postmp; //元の値の戻す
            down = downtmp;
            down--;
            step = 39;
        }

        break;
    case 39:
        if (collisionsrs(player_num))
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

//ホールド
void Mino::change()
{

    if (!holdbutton)
    {
        if (holdcheck)
        {
            Adx::play(3);

            //ホールド(2回目以降)
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
            Adx::play(3);

            //ホールド(初回)
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
            //次のブロックを出す
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

//初期化(デバック用)
void Mino::reset(int player_num)
{
    //初期化
    for (int i = 0; i < field_height - 1; i++)
    {
        for (int j = 1; j < field_width - 1; j++)
        {
            main[player_num][i][j] = 0;
        }
    }
    test[4][4] = { 0 };
    clearlinepos[21] = { 0 }; //横一列そろっている場所の確認用

  //回転時のtmp
    tmp[4][4] = { 0 };

    //時間関係
    nowtime = 0; //現在の時間
    oldtime = 0; //前回の時間
    time = 1;    //落下にかかる時間

  //方向キー
    up = 0;   //上
    down = 0; //下
    pos = 3;  //横

  //カウント
    cnt = 0;
    right = 0;
    left = 0;

    //当たり判定
    collisionf = false;
    collision_down = false;

    //ネクスト
    nextblock = true; //次のブロックを出す
    shuffle = false;  //ネクストブロックの配列要素をシャッフル
    shift = false;    //ネクストブロックの描画時のシフト用
    next = 0;          //次のブロック
    a = 0;             //配列の添え字

  //積み上げ
    Accumulate = false;
    downf = false;

    //ホールド関係
    holdf = false;        //ホールド
    holdcheck = false;    //すでにホールド中かの判定(ホールド中ならtrue)
    holdbutton = false;   //すでにホールドを使用したかの判定
    holdtmp[4][4] = { 0 }; //ホールドtmp
    hold[4][4] = { 0 };    //ホールド用

    srs = false; //スーパーローテーション

  //ゲームオーバー処理関係
    gameover = false; //ゲームオーバーになったときｔｒｕｅ
    overcnt = 0; //ゲームオーバーになった時の中身の入れ替え変数
    overcnt2 = 0; //ゲームオーバーになってからメニューが表示されるまでの時間

  // 消去数
    erase = 0;
    fall_speed = 1;

    //ゴースト
    transparent = 50;
    ghost[4][4] = { 0 };
    gdown = 0;

    score = 0;
    fall_speed = 0;


    //見本からコピー
    for (int i = 0; i < 7; i++)
    {
        next2[i] = next0[i];
    }

    //シャッフル
    for (int i = 0; i < 7; i++)
    {
        int j = rand() % 7;
        int t = next2[i];
        next2[i] = next2[j];
        next2[j] = t;
    }
}

//操作するやつ
void Mino::draw(int player_num)
{
    RECT trim;

    if (player_num != 0)
    {
        playerx = 200;
    }
    else
    {
        playerx = 485;
    }

    //描画
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
                    Sprite::draw(texture_, Vector2(playerx + (25 * pos) + (25 * j), 221 + (25 * down) - (25 * up) - 100 + (25 * i)), &trim);

            }
        }
    }
}

//積みあがるやつ
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
            if (main[player_num][i][j] != 0 && main[player_num][i][j] != 9)
            {
                if(!hidden)
                Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 221 + (25 * i) - 75), &trim);
            }
        }
    }
}

//ネクストブロックの表示
void Mino::nextdraw(int player_num)
{
    RECT trim;

    //描画
    for (int l = 1; l < nextop+1; l++)
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
                    //四角は一段下げる
                    if (mino[next1[l]][i][j] == 6)
                    {
                        Sprite::draw(texture_, Vector2(565 + (14 * j) + (l * 45), 114 + (15 * i)), &trim);

                    }
                    else
                    {
                        Sprite::draw(texture_, Vector2(565 + (14 * j) + (l * 45), 99 + (15 * i)), &trim);

                    }
                }
            }
        }
    }
}

//ホールドしたブロックの描画
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
            {
                //四角は一段下げる
                if (hold[i][j]== 6)
                {
                    Sprite::draw(texture_, Vector2(530 + (14 * j), 114 + (15 * i)), &trim);

                }
                else
                {
                    Sprite::draw(texture_, Vector2(530 + (14 * j), 99 + (15 * i)), &trim);
                }
            }
               
        }
    }
}

//レベルの描画
void Mino::leveldraw(int player_num)
{
    RECT trim;

    trim.top = 961;
    trim.left = 16 * fall_speed;
    trim.bottom = trim.top + 21;
    trim.right = trim.left + 16;

    Sprite::draw(texture_, Vector2(730, 42), &trim);

}

//スコアの描画
void Mino::scoredraw(int player_num)
{
	RECT rect;
	rect.top = 961;
	rect.left = 0;
	rect.bottom = rect.top + 21;
	rect.right = rect.left + 16;

    unsigned digit=0; //桁数

    int tmp = score; //スコアをtmpにコピー

    //桁数の算出
    while (tmp != 0)
    {
        tmp /= 10;
        digit++;
    }

    tmp = score; //スコアをコピーしなおす

    for (int i = 6; i >0; i--)
    {
        rect.left = labs(tmp) % 10 * 16;
        rect.right = rect.left + 16;

        Sprite::draw(texture_, Vector2(542+i*16+i, 42), &rect);
        tmp /= 10;
    }

}

//クリアウィンドウの描画
void Mino::cleardraw()
{

    RECT rect;

    rect.top = 0;
    rect.left = 1280+153;
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558, 274), &rect);
}

//ゲームオーバー
void Mino::menudraw()
{
    gameover_.draw();
    gameover_.rankdraw(fall_speed);
    gameover_.scoredraw(score);
    
}

//ゴーストの描画
void Mino::ghostdraw(int player_num)
{
    Color color = Color(1.0F, 1.0F, 1.0F, 0.4F);
    RECT trim;

    //描画
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
    
    gameover_.destroy();

    //破棄
    SAFE_RELEASE(texture_);
}