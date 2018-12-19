#pragma once


#define field_width 12
#define field_height 22


#define block_width 4
#define block_height 4


#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include<ctime>

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //テクスチャ
public:
    Mino();

    bool init();
    bool update();
    void draw();
    void maindraw();
    void nextdraw();
    void holddraw();
    void destroy();
    void reset();

    //ミノ
    int main[22][12]{ 0 };  //積みあがる本体
    int sub[22][12] = { 0 }; //サブ
    const int next0[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン 見本
    int next1[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン
    int next2[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン補充用
    const int mino[7][4][4] = {
        { //Iミノ
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
        },
        { //Oミノ
        {0,0,0,0},
        {0,2,2,0},
        {0,2,2,0},
        {0,0,0,0}
        },
        { //Tミノ
        {0,0,0,0},
        {0,3,0,0},
        {0,3,3,0},
        {0,3,0,0}
        },
        { //Jミノ
        {0,0,0,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,4,4,0}
        },
        { //Lミノ
        {0,0,0,0},
        {0,5,0,0},
        {0,5,0,0},
        {0,5,5,0}
        },
        { //Sミノ
        {0,0,0,0},
        {0,6,0,0},
        {0,6,6,0},
        {0,0,6,0}
        },
        { //Zミノ
        {0,0,0,0},
        {0,0,7,0},
        {0,7,7,0},
        {0,7,0,0}
        }
    };

    int test[4][4] = {
        {0,0,0,0},
        {0,1,0,0},
        {0,1,1,0},
        {0,0,1,0}
    }; //流す用テスト
    int clearlinepos[21] = { 0 }; //横一列そろっている場所の確認用
   
    //回転時のtmp
    int tmp[4][4] = { 0 };

    //時間関係
    int nowtime = 0; //現在の時間
    int oldtime = 0; //前回の時間
    int time = 1;    //落下にかかる時間

    //方向キー
    int up = 0;   //上
    int down = 0; //下
    int pos = 3;  //横

    //カウント
    int cnt = 0;

    //当たり判定
    bool collision_left = false;
    bool collision_right = false;
    bool collision_down = false;

    //回転
    bool rotation_a = false; //90
    bool rotation_b = false; //270

    //ネクスト
    bool nextblock = true; //次のブロックを出す
    bool shuffle = false;  //ネクストブロックの配列要素をシャッフル
    bool shift = false;    //ネクストブロックの描画時のシフト用
    int next = 0;          //次のブロック
    int a = 0;             //配列の添え字
    
    //ハードドロップ
    bool harddrop = false;

    //積み上げ
    bool Accumulate = false;

    //ミノが下がる時間
    int down_now_time = 0;
    int down_old_time = 0;

    bool downf = false;

    //ホールド関係
    bool holdf = false;        //ホールド
    bool holdcheck = false;    //すでにホールド中かの判定(ホールド中ならtrue)
    bool holdbutton = false;   //すでにホールドを使用したかの判定
    int holdtmp[4][4] = { 0 }; //ホールドtmp
    int hold[4][4] = { 0 };    //ホールド用

};