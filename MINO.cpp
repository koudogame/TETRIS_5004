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
        Error::showDialog("Tetris11_singleT.pngが読み込めません");

        //エラー
        return false;
    }

    //枠の生成
    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
            main[i][0] = 9;
            main[i][11] = 9; 
            main[21][j] = 9;

        }
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

    //現在の時間を取得
    nowtime = timeGetTime();
    collision_down = false;
    collision_left = false;
    collision_right = false;


    if (!collision_down)
    {
        //下
        if (state.Down)
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

    //当たり判定
    //左側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (mino[block][y][x] != 0) {
                if (main[down + y][pos +( x-1)] != 0) {
                    collision_left = true;
                }

            }
        }
    }
    //右側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (mino[block][y][x] != 0) {
                if (main[down + y][pos + (x + 1)] != 0) {
                    collision_right = true;
                }

            }
        }
    }
    //下側
    for (int y = 0; y < block_height; y++) {
        for (int x = 0; x < block_width; x++) {
            if (mino[block][y][x] != 0) {
                if (main[down + y][pos + x] != 0) {
                    collision_down = true;
                }
            }
        }
    }
 


    if (!collision_down)
    {
        //実時間で落とす
        if (nowtime - oldtime >= 500 / time)
        {
            cnt = 0;
            down++;
            oldtime = nowtime;
        }

    }

    //ブロックを消す処理
    for (int i = 0; i < 21; i++)
    {
        for (int j = 1; j < 11; j++)
        {
            if (main[i][j] == 0)
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

    //消された後の落とす処理
    for (int i = 0; i < 21; i++)
    {
        if (clearlinepos[i] == 0)
        {
            for (int j = 1; j < 11; j++)
            {
                //配列の初期化
                main[i][j] = 0; 
            }
            clearlinepos[i] = 0;

            for (int k = i; k > 0; k--)
            {
                for (int l = 1; l < 11; l++)
                {
                    //ミノ落とし
                    sub[k][l] = main[k][l];
                    main[k][l] = main[k - 1][l];
                    main[k - 1][l] = sub[k][l];
                }
            }
        }
    }
    //下が当たっていたら積む
    if (collision_down)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                if (mino[block][i][j] != 0&&main[down+i-1][pos+j]==0)
                    main[down + i - 1][pos + j] = mino[block][i][j];
            }

        }
        down = 0;
        pos = 3;
    }

    //上
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {
        //ハードドロップ(今できない)
        while (main[down + 1][pos] == 0)
        {
            down++;
        }
    }
    if (!collision_left)
    {
        //左
        if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
        {
            pos--;
        }

    }
    if (!collision_right)
    {
        //右
        if (pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
        {
            pos++;
        }
    }

    //回転90
    if (key_tracker.pressed.Enter||pad_tracker.a==GamePad::ButtonStateTracker::PRESSED)
    {
        rotation_a = true;
    }
    else
    {
        rotation_a = false;
    }

    if (key_tracker.pressed.RightShift||pad_tracker.b==GamePad::ButtonStateTracker::PRESSED)
    {
        rotation_b = true;
    }
    else
    {
        rotation_b = false;
    }

    if (rotation_a&&!rotation_b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = mino[block][j][i];
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mino[block][i][4 - j] = tmp[i][j];
            }
        }
    }

    //回転270
    if (!rotation_a && rotation_b)
    {
        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tmp[i][j] = mino[block][j][i];
            }
        }

        for (int i = 0; i < 4; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                mino[block][i][4 - j] = tmp[i][j];
            }
        }
    }

    return true;
}

void Mino::draw()
{

    RECT rect;
    rect.top = 955;
    rect.left = 687;
    rect.bottom = rect.top + 28;
    rect.right = rect.left + 26;

    //描画
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if(mino[block][i][j]!=0)
            Sprite::draw(texture_, Vector2(510 + (25 * pos)+(25*j)-25, 246 + (25 * down) - (25 * up) - 75+(25*i)), &rect);

        }
    }
    //Sprite::draw(texture_, Vector2(510 + (25 * pos), 246 + (25 * down) - (25 * up) - 75), &rect);

    //x510
    //y246
}

void Mino::maindraw()
{
    //積みあがるやつ

    //枠
    RECT rect;
    rect.top = 955;
    rect.left = 687+(25*8);
    rect.bottom = rect.top + 28;
    rect.right = rect.left + 26;

    //水色
    RECT trim;
    trim.top = 955;
    trim.left = 687;
    trim.bottom = trim.top + 28;
    trim.right = trim.left + 26;

    //オレンジ
    RECT Ltrim;
    Ltrim.top = 955;
    Ltrim.left = 687+(25 * 1);
    Ltrim.bottom = Ltrim.top + 28;
    Ltrim.right = Ltrim.left + 26;

    //緑
    RECT Strim;
    Strim.top = 955;
    Strim.left = 687 + (25 * 2);
    Strim.bottom = Strim.top + 28;
    Strim.right = Strim.left + 26;

    //赤
    RECT Ztrim;
    Ztrim.top = 955;
    Ztrim.left = 687 + (25 * 3);
    Ztrim.bottom = Ztrim.top + 28;
    Ztrim.right = Ztrim.left + 26;

    //青
    RECT Jtrim;
    Jtrim.top = 955;
    Jtrim.left = 687 + (25 * 4);
    Jtrim.bottom = Jtrim.top + 28;
    Jtrim.right = Jtrim.left + 26;

    //黄色
    RECT Otrim;
    Otrim.top = 955;
    Otrim.left = 687 + (25 * 5);
    Otrim.bottom = Otrim.top + 28;
    Otrim.right = Otrim.left + 26;

    //紫
    RECT Ttrim;
    Ttrim.top = 955;
    Ttrim.left = 687 + (25 * 6);
    Ttrim.bottom = Ttrim.top + 28;
    Ttrim.right = Ttrim.left + 26;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
         if(main[i][j]==9) //枠
            Sprite::draw(texture_, Vector2(510 + (25 * j)-25, 246 + (25 * i) - 75), &rect);
         else if (main[i][j] == 1) //水色
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &trim);
         else if (main[i][j] == 2 ) //黄色
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Otrim);
         else if (main[i][j] == 3) //紫
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ttrim);
         else if (main[i][j] == 4) //青
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Jtrim);
         else if (main[i][j] == 5) //オレンジ
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ltrim);
         else if (main[i][j] == 6) //緑
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Strim);
         else if (main[i][j] == 7) //赤
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &Ztrim);

        }
    }
}

void Mino::destroy()
{
    //破棄
    SAFE_RELEASE(texture_);
}
