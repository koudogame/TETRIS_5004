#include"result.h"
#include"adx.h"
// コンストラクタ
Result::Result()
{
    texture_ = NULL;
    S1texture_ = NULL;
	Rtexture_ = NULL;
    Judge1_ = NULL;
	mash_1 = 0;
	mash_2 = 0;
}

// initialize
bool Result::init( int mash1, int mash2,bool oba )
{
	// 初期化
	mash_1 = 0;
	mash_2 = 0;
	mash_sum = 0;
    
	// スコアを入れる
	mash_1 = mash1;
    if (oba)
    {
        mash_2 = mash2+200;

    }
    else
    {
        mash_2 = mash2;

    }

	// スコアの合計値を求める
	mash_sum = mash_1 + mash_2;

	// 過失割合を求める
	if (mash_sum > 0)
	{
		mash_1 = mash_1 * 10 / mash_sum;
		mash_2 = 10 - mash_1;
	}
	else
	{
		// スコアの合計が0なら強制的に5:5に設定
		mash_1 = 5;
		mash_2 = 5;
	}
    if( oba )
    {
        texture_ = Texture::load( L"リザルト2.png" );
    }
    else
    {
        texture_ = Texture::load( L"リザルト2デフォ.png" );
    }
    Rtexture_ = Texture::load(L"矢印.png");
    S1texture_ = Texture::load(L"work8.png");
    Judge1_ = Texture::load( L"判定.png" );

    if( texture_ == NULL )
    {
        // error
        Error::showDialog( "result.pngが読み込めません" );

        return false;

    }

    if (Rtexture_ == NULL)
    {
        // error
        Error::showDialog("矢印.pngが読み込めません");

        return false;

    }

    if (S1texture_ == NULL)
    {
        // error
        Error::showDialog("work8.pngが読み込めません");

        return false;

    }
    
    if( Judge1_ == NULL )
    {
        // error
        Error::showDialog( "judge.pngが読み込めません" );

        return false;

    }

    menu = 0;

    return true;
}

// update
int Result::update()
{

	const GamePad::State pad = Pad::getState();
	const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

	const Keyboard::State state = Key::getState();
	const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

	if (pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Down)
	{
		Adx::play(10);
		menu = 1; //retry
	}
	if (pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Up)
	{
		Adx::play(10);
		menu = 0; //exit
	}
	// backボタンでリザルト画面を閉じる
	if ((pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter) && menu == 0)
	{
		Adx::play(6);
		Sleep(550);
		return 1; //リトライ
	}
	if ((pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter) && menu == 1)
	{
		Adx::play(6);
		Sleep(550);
		return 2; //EXIT
	}
	return 3;
}

// draw
void Result::draw()
{
    // 背景
    Sprite::draw( texture_, Vector2::Zero);

    // 判定の描画

    RECT rect1;
    rect1.left = 0;
    rect1.right = rect1.left + 180;
    rect1.top = 0;
    rect1.bottom = rect1.top + 70;

    RECT rect2;
    rect2.left = 0;
    rect2.right = rect2.left + 180;
    rect2.top = 70;
    rect2.bottom = rect2.top + 70;


    if( mash_1 > mash_2 )
    {
        judge_num = 0;

        Sprite::draw( Judge1_, Vector2( 300, 300 ), &rect1 );

        judge_num++;

        Sprite::draw( Judge1_, Vector2( 800, 300 ), &rect2 );
    }
    else if( mash_1 < mash_2 )
    {
        judge_num = 1;

        Sprite::draw( Judge1_, Vector2( 300, 300 ), &rect2 );

        judge_num--;

        Sprite::draw( Judge1_, Vector2( 800, 300 ), &rect1);
    }
    else
    {
        RECT rect3;
        rect3.left = 0;
        rect3.right = rect3.left + 180;
        rect3.top = 140;
        rect3.bottom = rect3.top + 70;

        Sprite::draw( Judge1_, Vector2( 580, 300 ), &rect3 );
    }
}

void Result::scoredraw1()
{

    RECT rect;

    int tmp = 0;
    int digit = 0;


    tmp = mash_2;

    // 桁数の算出
    while (tmp != 0) {
        tmp /= 10;
        digit++;
    }

    //スコアの入れ直し
    tmp = mash_2;

    //スコアの描画
    if (tmp == 0)
    {
        rect.left = 0;
        rect.right = rect.left + 32;
        rect.top = 0;
        rect.bottom = rect.top + 64;

        Sprite::draw(S1texture_, Vector2(500, 230), &rect);

    }
    else
    {
        for (int i = digit; i > 0; i--)
        {
            rect.left = tmp % 10 * 32;
            rect.right = rect.left + 32;
            rect.top = 0;
            rect.bottom = rect.top + 64;
			tmp /= 10;

			Sprite::draw(S1texture_, Vector2(500 + (i * 32), 230), &rect);

        }
    }


}


void Result::scoredraw2()
{

    RECT rect;

    int tmp = 0;
    int digit = 0;


    tmp = mash_1;

    // 桁数の算出
    while (tmp != 0) {
        tmp /= 10;
        digit++;
    }

    //スコアの入れ直し
    tmp = mash_1;

    //スコアの描画
    if (tmp == 0)
    {
        rect.left = 0;
        rect.right = rect.left + 32;
        rect.top = 0;
        rect.bottom = rect.top + 64;

        Sprite::draw(S1texture_, Vector2(750,230), &rect);
    }
    else
    {
        for (int i = digit; i > 0; i--)
        {
            rect.left = tmp % 10 * 32;
            rect.right = rect.left + 32;
            rect.top = 0;
            rect.bottom = rect.top + 64;
			tmp /= 10;
            Sprite::draw(S1texture_, Vector2(750+(i*32),230), &rect);

        }
    }
}
void Result::arrowdraw()
{
    RECT rect;

    const GamePad::State pad = Pad::getState();
    const Keyboard::State state = Key::getState();

    if (menu == 0)
    {
        rect.top = 0;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    else if (menu == 1)
    {
        rect.top = 200;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }

    Sprite::draw(Rtexture_, Vector2(800.0F, 500.0F), &rect);

}
// destroy
void Result::destroy()
{
    SAFE_RELEASE(texture_);
    SAFE_RELEASE(S1texture_);
	SAFE_RELEASE(Rtexture_);
    SAFE_RELEASE( Judge1_ );
  
}