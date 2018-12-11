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
    //上
    if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
    {
        //ハードドロップ
        while (main[down + 1][pos + 1] == 0)
        {
            down++;
        }
    }
    //左
    if (pad_tracker.dpadLeft == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Left)
    {
        pos--;
    }
    //右
    if (pad_tracker.dpadRight == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Right)
    {
        pos++;
    }
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
 
    //実時間で落とす
    if (nowtime - oldtime >= 500/time)
    {
        cnt = 0;
        down++;
        oldtime = nowtime;
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
                clearlinepos[i] = 0;    //ブロックがあるときは0
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
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //積み上げ
            if (main[down + 1+i][pos + 1+j] != 0)
            {
                main[down+i][pos + 1] = 1;
                down = 0;
            }
        }

    }

    //移動制限
    if (pos < 0)
    {
        pos = 0;
    }
    if (pos > 9)
    {
        pos = 9;
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
            if(test[i][j]==1)
            Sprite::draw(texture_, Vector2(510 + (25 * pos)+(25*j), 246 + (25 * down) - (25 * up) - 75+(25*i)), &rect);

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

    //青
    RECT trim;
    trim.top = 955;
    trim.left = 687;
    trim.bottom = trim.top + 28;
    trim.right = trim.left + 26;

    for (int i = 0; i < 22; i++)
    {
        for (int j = 0; j < 12; j++)
        {
         if(main[i][j]==9) //枠
            Sprite::draw(texture_, Vector2(510 + (25 * j)-25, 246 + (25 * i) - 75), &rect);
         else if (main[i][j] == 1) //青
             Sprite::draw(texture_, Vector2(510 + (25 * j) - 25, 246 + (25 * i) - 75), &trim);
        }
    }
}

void Mino::destroy()
{
    //破棄
    SAFE_RELEASE(texture_);
}
