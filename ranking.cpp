#include "ranking.h"

Ranking::Ranking()
{
    texture_ = NULL;
}

bool Ranking::init()
{
    //テクスチャの読み込み
    if (!(texture_ = Texture::load(L"Tetris13_Ranking.png")))
    {

        Error::showDialog("Tetris13_Ranking.pngの読み込みに失敗");

        //エラー
        return false;
    }

    return true;
}

bool Ranking::update()
{
    //ゲームパットの入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // キーボードの入力を取得
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    //タイトルに戻る
    if (key_tracker.pressed.Enter || pad_tracker.a == GamePad::ButtonStateTracker::PRESSED)
    {
        Adx::play(10);

        return false;
    }

    return true;
}

void Ranking::draw()
{
    rankcntx = 0;
    rankcnty = 0;
    RECT trim;

    trim.top = 0;
    trim.left = 0;
    trim.bottom = trim.top + 720;
    trim.right = trim.left + 1280;

    Sprite::draw(texture_, Vector2::Zero, &trim);
    FILE* fp = fopen("ranking.txt", "r");

    RECT rank;

    if (fp == NULL)
    {
        Error::showDialog("ranking.txtの読み込みに失敗しました");
        PostQuitMessage(0);
    }
    int ranking;
    int left = 0;

    while (fscanf(fp, "%d", &ranking) != EOF)
    {
        rankcntx++;
        if (rankcntx == 4)
        {
            rankcntx++;
        }
        if (rankcntx == 11)
        {
            rankcntx++;
        }
        if (rankcntx % 13 == 0)
        {
            rankcnty++;
            rankcntx = 1;
        }

        rank.top = 982;
        rank.left = 0 + (32 * ranking);
        rank.bottom = rank.top + 42;
        rank.right = rank.left + 32;
        if (rankcntx < 4)
        {
            Sprite::draw(texture_, Vector2(429 + (rankcntx * 32), 139 + (rankcnty * 52)), &rank);
        }
        else if (rankcntx > 4 && rankcntx < 12)
        {
            Sprite::draw(texture_, Vector2(435 + (rankcntx * 32), 139 + (rankcnty * 52)), &rank);
        }
        else
        {
            Sprite::draw(texture_, Vector2(445 + (rankcntx * 32), 139 + (rankcnty * 52)), &rank);
        }
    }

    fclose(fp);



}

void Ranking::destroy()
{
    SAFE_RELEASE(texture_);
}
