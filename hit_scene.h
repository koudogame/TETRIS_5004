#pragma once


#include "player.h"
#include "field.h"
#include "UI.h"

class HitScene
{
private:
    ID3D11ShaderResourceView* texture1_car;     // 自転車
    ID3D11ShaderResourceView* texture2_bike;    // 車
    ID3D11ShaderResourceView* texture3_back;    // 背景

    Vector2 position1_bike;                         //自転車 
    Vector2 position2_car;                         // 車

    bool hit_flag_;                                // 当たりフラグ

public:
    HitScene();     // コンストラクタ
    bool init(bool oba, int p2);    // 初期化
    bool update(bool oba);  // 更新
    void draw(bool oba);    // 描画
    void destroy(); // 破棄

    int cnt = 0;
};