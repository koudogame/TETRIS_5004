#pragma once

#define field_width 12
#define field_height 23

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
    int update();
    void ghostupdate();

    void srsystem(); //スーパーローテーション
    void change();

    //描画
    void draw();
    void maindraw(); //積みあがる配列の描画
    void nextdraw(); //ネクストブロックの描画
    void holddraw(); //ホールドしているブロックの描画
    void ghostdraw();
    void scoredraw(); //スコアとレベルの描画

	void destroy();  //破棄
    void reset();    //積み上げ配列の範囲内の全情報を初期化

    //当たり判定
    void collisionleft();
    void collisionright();
    void collisiondown();

    //ネクスト
    void nextpattern();

    //ミノ
    int main[4][26][12]={ 0 };  //積みあがる本体(人数分
    int sub[22][12] = { 9 }; //サブ
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
        {0,0,3,0},
        {0,3,3,0},
        {0,0,3,0}
        },
        { //Jミノ
        {0,0,0,0},
        {0,0,4,0},
        {0,0,4,0},
        {0,4,4,0}
        },
        { //Lミノ
        {0,0,0,0},
        {0,5,5,0},
        {0,0,5,0},
        {0,0,5,0}
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

    int test [4][4] = { 0 };
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
    int pos = 4;  //横

    //カウント
    int cnt = 0;
    int right = 0;
    int left = 0;

    //当たり判定
    bool collisionf = false;
    bool collision_down = false;

    //ネクスト
    bool nextblock = true; //次のブロックを出す
    bool shuffle = false;  //ネクストブロックの配列要素をシャッフル
    bool shift = false;    //ネクストブロックの描画時のシフト用
    int next = 0;          //次のブロック
    int a = 0;             //配列の添え字

    //積み上げ
    bool Accumulate = false;
    bool downf = false;

    //ホールド関係
    bool holdf = false;        //ホールド
    bool holdcheck = false;    //すでにホールド中かの判定(ホールド中ならtrue)
    bool holdbutton = false;   //すでにホールドを使用したかの判定
    int holdtmp[4][4] = { 0 }; //ホールドtmp
    int hold[4][4] = { 0 };    //ホールド用

    bool srs = false; //スーパーローテーション

	//ゲームオーバー処理関係
	bool gameover = false; //ゲームオーバーになったときｔｒｕｅ
	int overcnt = 0; //ゲームオーバーになった時の中身の入れ替え変数
    int overcnt2 = 0; //ゲームオーバーになってからメニューが表示されるまでの時間

    // 消去数
    int erase = 0;
    int fall_speed = 1;

    //ゴースト
    int transparent = 50;
    int ghost[4][4] = { 0 };
    int gdown = 0;
};