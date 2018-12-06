#include"sprite.h"
#include"direct3d.h"
#include"common.h"
#include"player.h"

// 実体の宣言
SpriteBatch*  Sprite::sprite_;

//初期化
bool Sprite::init()
{
    //SpriteBatchクラスのメモリ確保
    sprite_ = new SpriteBatch( Direct3D::getContext() );

    //メモリ確保チェック
    if( !sprite_ )
    {
        return false;
    }

    return true;

}

    //破棄
void Sprite::destroy()
{
    //メモリ解放
    delete  sprite_;
}


    //描画終了
void Sprite::end()
{
    sprite_->End();
}

//描画開始
void Sprite::begin()
{
    sprite_->Begin( SpriteSortMode_Deferred, Common::getState()->NonPremultiplied() );
}

void Sprite::draw(
    ID3D11ShaderResourceView* Texture,
    const Vector2& Position,
    const RECT* Rect,
    const float Rotation,
    const Vector2& Scale,
    const Vector2& Origin,
    const SpriteEffects Effect,
    const float Depth )
{
    sprite_->Draw(
        Texture,       // テクスチャ
        Position,      // 座標
        Rect,          // 描画範囲
        Colors::White, // カラー
        Rotation,      // 回転値
        Origin,        //アンカーポイント
        Scale,         //拡縮
        Effect,        //エフェクト
        Depth );       //深度値
}