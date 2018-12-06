#include"player.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"key.h"

#include"adx.h"

Player player;
// 実体の宣言
int Player::mash_point1_;
int Player::mash_point2_;

enum
{
    kDown,
    kUp,
    kRight,
    kLeft,
};

// アクション番号
enum Action
{
    animation1,
    animation2,
    animation3,
};

enum Motion
{
    normal,
    turn,
};

// コンストラクタ
Player::Player()
{
    //メンバ変数初期化
    position_.x = static_cast<float>(0.0F);
    position_.y = static_cast<float>(600.0F - 196.0F);

    // アニメーション関係
    animation_no_ = animation1;
    animation_pattern_ = normal;                                                                                                                                                                                   // アニメーション番号
    animation_counter_ = 0;

    // アクション関連
    action_flag_ = false;
    action_count_ = 0;


    // メンバ変数初期化
    texture_1 = NULL;
    texture_2 = NULL;
}


//デストラクタ
Player::~Player()
{
}

//初期化
bool Player::init( const wchar_t* FileName1, const wchar_t* FileName2)
{
    //テクスチャの読み込み

    texture_1 = Texture::load( FileName1 );
    texture_2 = Texture::load( FileName2 );

	// 変数初期化
    //static int mash_point1_;    // プレイヤー1
    //static int mash_point2_ ;    // プレイヤー2

    mash_point1_ = 0;
    mash_point2_ = 0;

    //NULLチェック
    if( texture_1 == NULL )
    {

        Error::showDialog( "texture_1が読み込めません" );

        //エラー
        return false;
    }

    //NULLチェック
    if( texture_2 == NULL )
    {

        Error::showDialog( "texture_2が読み込めません" );

        //エラー
        return false;
    }

    //再生
    Adx::play( 0 );

    return true;

}

//更新処理
void Player::update(bool oba)
{
    if (oba) //大場モード時のみ使用
    {
        // アニメーション処理
        animation_no_++;

        // アニメーション番号をリセットする
        if (animation_no_ > animation3)
        {
            animation_no_ = animation1;
        }

        // ランダムで大場先生の向きを変更
        if (int pattern_manager = animation_counter_ % 200)
        {
            if (pattern_manager <= 130
                )
            {
                animation_pattern_ = normal;
            }
            else
            {
                animation_pattern_ = turn;
            }
        }
    }
   

    // 1Pコントローラの入力を取得
    const GamePad::State pad = Pad::getState();
    const GamePad::ButtonStateTracker pad_tracker = Pad::getTracker();

    // 2Pコントローラの入力を取得
    const GamePad::State pad2 = Pad::getState2();
    const GamePad::ButtonStateTracker pad_tracker2 = Pad::getTracker2();

    // キーボードの入力を取得
    const Keyboard::State key = Key::getState();
    const Keyboard::KeyboardStateTracker key_tracker = Key::getTracker();

    // 連打数を加算する
    if( pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter )
    {
        mash_point1_++;
		if (oba)
		{
			Adx::play(5);
		}
    }

    if( pad_tracker2.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space )
    {
        mash_point2_++;
    }

    // アニメーションカウンタを加算
    animation_counter_++;

}

//描画
void Player::draw(bool oba)  //車
{
    RECT rect;

    if (oba) //大場モードのテクスチャの設定
    {
        // 描画範囲の設定
        rect.top = animation_pattern_ * 196L;
        rect.left = animation_no_ * 600L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 196L;

        // 描画
        Sprite::draw(texture_1, position_, &rect);
    }
    else //通常モードの車テクスチャの設定
    {
        // 描画範囲の設定
        rect.top =0L;
        rect.left = 0L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 360L;

        // 描画
        Sprite::draw(texture_1, Vector2(-50.0F, 250.0F), &rect);
    }

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
    SAFE_RELEASE( texture_2 );
}