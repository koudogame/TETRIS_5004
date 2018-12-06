#include"title.h"
#include"texture.h"
#include"sprite.h"
#include"pad.h"
#include"adx.h"
#include"key.h"
#include"start.h"

// コンストラクタ
Start::Start()
{

    texture1_ = NULL;
    texture2_ = NULL;
    texture3_ = NULL;
    texture4_ = NULL;
    p1 = false;
    p2 = false;

}

//デストラクタ
Start::~Start()
{
}

//初期化
bool Start::init()
{
    //テクスチャの読み込み
    if( !(texture3_ = Texture::load( L"説明準備.png" ) )) //何も押されていない
    {
        //エラー
        return false;
    }

    if (!(texture1_ = Texture::load(L"説明1p.png"))) //1pのみ準備完了
    {
        //エラー
        return false;
    }

    if (!(texture2_ = Texture::load(L"説明2p.png"))) //2pのみ準備完了
    {
        //エラー
        return false;
    }

    if (!(texture4_ = Texture::load(L"説明準備完了.png"))) //全員準備完了
    {
        //エラー
        return false;
    }

    p1 = false;
	p2 = false;
    cnt = 0;

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

		if (!p1 && (pad_tracker.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Enter)) //1pの準備完了
		{
			Adx::play(9);
			p1 = true;

		}

		if (!p2 && (pad_tracker2.a == GamePad::ButtonStateTracker::PRESSED || key_tracker.pressed.Space)) //2pの準備完了
		{
			Adx::play(9);
			p2 = true;
		}
	

	if (p1&&p2) //両プレイヤーが準備完了していたらカウントスタート
	{
		cnt++;
	}

	if (cnt > 50&& p1&&p2) //カウントが50を超えたらゲームスタート
	{
		return false;
	}

	return true;
}


//描画
void Start::draw()
{
    if (p1&&p2)
    {
        Sprite::draw(texture4_, Vector2::Zero);
    }
    else if (p1 && !p2)
    {
        Sprite::draw(texture1_, Vector2::Zero);
    }
    else if (!p1&&p2)
    {
        Sprite::draw(texture2_, Vector2::Zero);
    }
    else
    {
        Sprite::draw(texture3_, Vector2::Zero);
    }

}

//破棄
void Start::destroy()
{

    //テクスチャの解放
    SAFE_RELEASE( texture1_ );
    SAFE_RELEASE( texture2_ );
    SAFE_RELEASE( texture3_ );
    SAFE_RELEASE( texture4_ );

}