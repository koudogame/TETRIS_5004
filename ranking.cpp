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

    FILE* fp = fopen("ranking.txt", "r");

    RECT trim;
    RECT rank;
    trim.top = 0;
    trim.left = 0;
    trim.bottom = trim.top + 720;
    trim.right = trim.left + 1280;

    Sprite::draw(texture_, Vector2::Zero, &trim);
    if (fp == NULL)
    {
        Error::showDialog("ranking.txtの読み込みに失敗しました");
        PostQuitMessage(0);
    }
    int ranking;
    int left = 0;

    while (fscanf(fp, "%d", &ranking) != EOF)
    {
        left = ranking;
        rank.top = 961;
        rank.left = 0 + (16 * ranking);
        rank.bottom = rank.top + 21;
        rank.right = rank.left + 16;

        Sprite::draw(texture_, Vector2(463, 139), &rank);
    }

    fclose(fp);


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


}

void Ranking::destroy()
{
    SAFE_RELEASE(texture_);
}
