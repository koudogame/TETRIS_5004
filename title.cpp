#include"title.h"

// コンストラクタ
Title::Title()
{  
    texture_ = NULL;
    texture2_ = NULL;
    texture3_ = NULL;
    oba = false;
}

// 決定音待ち時間
const int wait = 550;

//デストラクタ
Title::~Title()
{
}

//初期化
bool Title::init()
{
    menu = 0;
    oba = false;
    cnt = 0;
    //テクスチャの読み込み
    if( !(texture_ = Texture::load( L"標準タイトル.png" )) )
    {

        Error::showDialog("標準タイトル.pngの読み込みに失敗");

        //エラー
        return false;
    }

    //テクスチャの読み込み
    if (!(texture2_ = Texture::load(L"タイトル矢印.png")))
    {

        Error::showDialog("タイトル.pngの読み込みに失敗");

        //エラー
        return false;
    }
    // テクスチャの読み込み
    if( !(texture3_ = Texture::load( L"大場先生タイトル.png" )) )
    {

        Error::showDialog( "大場先生タイトル.pngの読み込みに失敗" );

        //エラー
        return false;
    }

    return true;
}

//更新
int Title::update()
{
    tmp = oba; //前のフレームのフラグ状態を取得

    //ゲームパットの入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // キーボードの入力を取得
    const Keyboard::State state = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    if (!oba)
    {
        if (pad.dpad.up&&pad.dpad.left&&pad2.dpad.right&&pad2.dpad.down)
        {
            cnt++;
        }
        else
        {
            cnt = 0;
        }

        if (cnt > 50)
        {
            oba = true;
        }
    }

    if (state.F1) //大場モード解除
    {
        oba = false;
    }

    if (tmp!=oba) //モード切り替え音
    {
        if( oba )
        {
            Adx::stop();
            Adx::play( 0 );
            Adx::play( 5 );
        }
        else
        {
            Adx::stop();
            Adx::play( 3 );
        }
    }

    // 下が押されたら
    if (key_tracker.pressed.Down || pad_tracker.dpadDown == GamePad::ButtonStateTracker::PRESSED)
    {
        menu++;
		Adx::play(10);
    }

    // 上が押されたら
    else if (key_tracker.pressed.Up || pad_tracker.dpadUp == GamePad::ButtonStateTracker::PRESSED)
    {
        menu--;
		Adx::play(10);
    }

    // メニューのループ
    if (menu > 2)
    {
        menu = 0;
    }

    if (menu < 0)
    {
        menu = 2;
    }

    if (oba&&menu == 0 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))  //ゲームスタート(大場モード)
    {
        Adx::play(6);
        Sleep(wait);
        return 4;
    }
    if (menu == 0 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))  //ゲームスタート(通常)
    {
        Adx::play(6);
        Sleep(wait);
        return 2;
    }
    if (menu == 1 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter))   //クレジット
    {
        Adx::play(6);
        Sleep(wait);
        return 3;
    }
    if (menu == 2 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)) //exit
    {
        Adx::play(6);
        Sleep(wait);
        return 1;
    }

    return 6;

}

//描画
void Title::draw()
{
    if( oba )
    {
        Sprite::draw( texture3_, Vector2::Zero );
    }
    else
    {
        Sprite::draw( texture_, Vector2::Zero );
    }
}

void Title::adraw()
{
    RECT rect;

    if( menu == 0 )
    {
        rect.top = 0;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    else if( menu == 1 )
    {
        rect.top = 200;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    else if( menu == 2 )
    {
        rect.top = 400;
        rect.left = 0;
        rect.right = rect.left + 200;
        rect.bottom = rect.top + 200;
    }
    Sprite::draw( texture2_, Vector2( 370.0F, 360.0F ), &rect );
}

//破棄
void Title::destroy()
{
    //テクスチャの解放
    SAFE_RELEASE( texture_ );
    SAFE_RELEASE( texture2_ );
    SAFE_RELEASE( texture3_ );
}