#pragma once

#include<d3d11.h>
#include<SimpleMath.h>
#include<Keyboard.h>
#include"release.h"
#include"Error.h"

using namespace DirectX;
using namespace SimpleMath;

//クラス宣言
class Player
{
private:
    ID3D11ShaderResourceView* texture_1;                                                         // テクスチャ
    ID3D11ShaderResourceView* texture_2;
    Vector2 position_;                                                                          // 座標
    float speed_;                                                                               // 移動速度

    // アニメーション関連
    int animation_pattern_;                                                                     // アニメーションパターン                                         
    int animation_no_;                                                                          // アニメーション番号
    int animation_counter_;                                                                     // アニメーションカウンタ                            


    // アクション関連
    bool action_flag_;       // アクションのフラグ
    int action_count_;       // アクション実行時の時間管理をする変数

    // 連打数
    static int mash_point1_;      // プレイヤー1
    static int mash_point2_;      // プレイヤー2
    

public:
    Player();                                                                                   // コンストラクタ
    ~Player();                                                                                  // デストラクタ

    //初期化
    bool init( const wchar_t* FileName1, const wchar_t*FileName2);
    int get_position_x() { return position_.x; }
    int get_animation_pattern() { return animation_pattern_; }
    static int get_mashpoint_1() { return mash_point1_; }
    static int get_mashpoint_2() { return mash_point2_; }


    void update(bool oba);                                                // 更新
    void draw(bool oba);                                                  // 描画
    void draw2();
    void destroy();                                               // 破棄
};