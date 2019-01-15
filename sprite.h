#pragma once
#include<SpriteBatch.h>
#include<SimpleMath.h>

using namespace DirectX;
using namespace SimpleMath;


//Class

class Sprite
{
private:
    static SpriteBatch*  sprite_;

public:
    static bool init();                                          //初期化
    static void begin();                                         //描画開始
    static void end();                                           //描画終了
    static void destroy();                                       //破棄

    // 描画
    static void draw(
        ID3D11ShaderResourceView* Texture,                       // テクスチャ
        const Vector2& Position         = Vector2( 0.0F, 0.0F ), // 座標
        const RECT* Rect                = NULL,                  // 描画範囲
        const XMVECTOR Color           = Colors::White,
        const float Rotation            = 0.0F,                  // 回転
        const Vector2& Scale            = Vector2( 1.0F, 1.0F ), // 拡縮
        const Vector2& Origin           = Vector2( 0.0F, 0.0F ), // アンカーポイント
        const SpriteEffects Effect      = SpriteEffects_None,    // エフェクト
        const float Depth = 0.0F );                              // 深度

    //SpriteBatchポインタを返す
    static SpriteBatch* getSprite() { return sprite_; }
};