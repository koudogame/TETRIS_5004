
#include"start.h"

// コンストラクタ
Start::Start()
{

    texture_ = NULL;

}

//デストラクタ
Start::~Start()
{
}

//初期化
bool Start::init()
{
    //テクスチャの読み込み
    if( !(texture_ = Texture::load( L"Tetris11_SingleT.png" ) )) //何も押されていない
    {
        //エラー
        return false;
    }

    //時間を取得
    oldtime = timeGetTime();

    return true;
}

//更新
bool Start::update()
{

		//ゲームパットの入力を取得
		const GamePad::State pad = Pad::getState();
		const GamePad::State pad2 = Pad::getState2();

		const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();
		const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

		// キーボードの入力を取得
		const Keyboard::State state = Key::getState();
		const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

        nowtime = timeGetTime();

        if (nowtime - oldtime >= 1000)
        {
            if (goflag)
            {
                return false;
            }

            oldtime = nowtime;

            if (starttimer >= 1&&!goflag)
            {
                starttimer--;
            }

            if (starttimer == 0)
            {
                goflag = true;
            }
        }

	return true;
}


//描画
void Start::draw()
{
    RECT rect;

    rect.top = 0;
    rect.left = 1280;
    rect.bottom = rect.top + 153;
    rect.right = rect.left + 153;

    Sprite::draw(texture_, Vector2(558,274),&rect);

}

void Start::cntdraw()
{

    RECT trim;

    trim.top = 982;
    trim.left = 32*starttimer;
    trim.bottom = trim.top + 42;
    trim.right = trim.left + 32;

    Sprite::draw(texture_, Vector2(620, 325), &trim);

}

void Start::godraw()
{
    RECT rect;

    rect.top = 982;
    rect.left = 1375;
    rect.bottom = rect.top + 42;
    rect.right = rect.left + 91;

    if (goflag)
    Sprite::draw(texture_, Vector2(592, 375), &rect);

}

//破棄
void Start::destroy()
{

    //テクスチャの解放
    SAFE_RELEASE( texture_ );

}