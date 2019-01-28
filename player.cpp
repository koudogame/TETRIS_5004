#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"key.h"
#include"adx.h"

Player player;

// コンストラクタ
Player::Player()
{
    // メンバ変数初期化
    texture_1 = NULL;
}


//デストラクタ
Player::~Player()
{
}

//初期化
bool Player::init( )
{
    //テクスチャの読み込み

    texture_1 = Texture::load(L"Tetris11_SingleT.png");

    //NULLチェック
    if( texture_1 == NULL )
    {

        Error::showDialog( "Tetris11_SingleT.pngが読み込めません" );

        //エラー
        return false;
    }

    return true;

}

//更新処理
void Player::update()
{

    // 1Pコントローラの入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // 2Pコントローラの入力を取得
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

    // キーボードの入力を取得
    const Keyboard::State key = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

}

//描画
void Player::draw()  //車
{
    RECT rect;

  
        // 描画範囲の設定
        rect.top = animation_pattern_ * 196L;
        rect.left = animation_no_ * 600L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 196L;

        // 描画
        Sprite::draw(texture_1, position_, &rect);

}

void Player::draw2()  //チャリ
{
    // 描画範囲の設定
    RECT rect;
    rect.top =0L;
    rect.left = 0L;
    rect.right = rect.left + 210L;
    rect.bottom = rect.top + 301L;

    Vector2 scale( 0.5F, 0.5F );
    Vector2 origin( 0.0F, 0.0F );

    // 描画
    Sprite::draw( texture_2, Vector2( 900.0F, 390.0F ), &rect );
}


//破棄
void Player::destroy()
{
    SAFE_RELEASE( texture_1 );
}