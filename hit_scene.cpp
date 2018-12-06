#include "hit_scene.h"
#include"adx.h"


// コンストラクタ
HitScene::HitScene()
{
    // テクスチャにNULLを入れておく
    texture1_car = NULL;
    texture2_bike = NULL;
    texture3_back = NULL; hit_flag_ = NULL;
}

// 初期化
bool HitScene::init(bool oba, int p2)
{
    // テクスチャ読み込み
	if (oba)
	{
		texture1_car = Texture::load(L"oba1.png");
	}
	else
	{
		texture1_car = Texture::load(L"car_side.png");
	}
    if (!oba)
    {
        //ひかれる側の種類
        if (p2 == 0)
        {
            texture2_bike = Texture::load(L"チャリ.png");
        }
        else if (p2 == 1)
        {
            texture2_bike = Texture::load(L"バイク緑.png");
        }
        else if (p2 == 2)
        {
            texture2_bike = Texture::load(L"バイク赤.png");
        }
    }
    else
    {
        texture2_bike = Texture::load(L"チャリ.png");
    }

    
    texture3_back = Texture::load( L"field.png" );

    
    // 自転車の座標
    position1_bike.x = static_cast<float>(1280.0F);
    position1_bike.y = static_cast<float>(390.0F);

    // 車の座標
    if (oba)
    {
        position2_car.x = static_cast<float>(0.0F);
        position2_car.y = static_cast<float>(600.0F - 196.0F);

    }
    else //通常モード
    {
        position2_car.x = static_cast<float>(0.0F);
        position2_car.y = static_cast<float>(600.0F - 350.0F);

    }

    hit_flag_ = NULL;

    //NULLチェック
    if( texture1_car == NULL )
    {

        Error::showDialog( "texture_1が読み込めません" );

        //エラー
        return false;
    }

    if( texture2_bike == NULL )
    {

        Error::showDialog( "texture_2が読み込めません" );

        //エラー
        return false;
    }

    if( texture3_back == NULL )
    {

        Error::showDialog( "texture_2が読み込めません" );

        //エラー
        return false;
    }

    return true;
}

bool HitScene::update(bool oba)
{

    cnt++;
    int tmp=0;
    if (oba)
    {
        tmp = 5;
    }
	// 自転車の座標が一定以上のとき衝突フラグがオフなら左に移動
    if( position1_bike.x>=640&&hit_flag_!=true )
    {
        position1_bike.x-=5;
    }
    if (oba)
    {
        position2_car.x += 5;
    }
	// 車の座標が一定以下のとき衝突フラグがオフなら右に移動
    if (position2_car.x + 600 <= position1_bike.x&&hit_flag_ != true)
    {
        if (!oba)
        {
            position2_car.x += 5;
        }
    }

	// 車と自転車が衝突したときの処理
    if( position1_bike.x <= position2_car.x + 550&&!hit_flag_ )
    {
       
		// 大場先生モードなら小鼓の音にする
		if (oba)
		{

			Adx::play(7);
		}
		else
		{
			Adx::play(8);
		}
		// 衝突フラグをオン
        hit_flag_ = true;
    }

	// 衝突フラグがオンで自転車が画面内にまだいるとき自転車を吹っ飛ばす
    if( hit_flag_ == true && position1_bike.x <= 1280 + 210 )
    {
        position1_bike.y -= 5;
        position1_bike.x += 10;
    }
	// 自転車が消えたら終了
    else if( hit_flag_ == true && position1_bike.x >= 1280 + 210+tmp)
    {
        return false;
    }
    return true;
}

// 描画
void HitScene::draw(bool oba)
{
    RECT rect;

    if (oba)
    {
        if (!hit_flag_)
        {
            rect.top = 0L;
            rect.left = 0L;
            rect.right = rect.left + 600L;
            rect.bottom = rect.top + 196L;
        }
        else
        {
            rect.top = 196L;
            rect.left = 0L;
            rect.right = rect.left + 600L;
            rect.bottom = rect.top + 196L;
        }
    }
    else
    {
        rect.top = 0L;
        rect.left = 0L;
        rect.right = rect.left + 600L;
        rect.bottom = rect.top + 360L;
    }

    Vector2 scale(1.0F, 1.0F);
    Vector2 origin(0.0F, 0.0F);

    Sprite::draw(texture3_back, Vector2::Zero);       // 背景を描画
    Sprite::draw(texture2_bike, position1_bike);       // 自転車を描画
    if (oba)
    {
        Sprite::draw(texture1_car, position2_car, &rect); // 車を描画

    }
    else
    {
        Sprite::draw(texture1_car, position2_car, &rect); // 車を描画
    }

}

void HitScene::destroy()
{
    SAFE_RELEASE( texture1_car );
    SAFE_RELEASE( texture2_bike );
    SAFE_RELEASE( texture3_back );
}
