#pragma once

#define field_width 12 //フィールド横幅
#define field_height 23 //フィールド縦幅

#define block_width 4 //ブロック横幅
#define block_height 4 //ブロック縦幅

#define fall_time 1500 //落下秒数

#define SPEED 1 //初期レベル（速度)

#include"texture.h"
#include"player.h"
#include"sprite.h"
#include"key.h"
#include"pad.h"
#include"tetris_acf.h"
#include"CueSheet_0.h"
#include"adx.h"
#include<ctime>
#include"gameover.h"

class Mino
{
private:
    ID3D11ShaderResourceView* texture_; //テクスチャ
    Gameover gameover_;
public:
    Mino();

    bool init(int player_num);
    int update(int player_num);
    void ghostupdate(int player_num);

    void srsystem(int rotation_type, int player_num); //スーパーローテーション
    void change();

    //描画
    void draw(int player_num);
    void maindraw(int player_num); //積みあがる配列の描画
    void nextdraw(int player_num); //ネクストブロックの描画
    void holddraw(int player_num); //ホールドしているブロックの描画
    void leveldraw(int player_num); //レベルの表示
    void ghostdraw(int player_num);
    void scoredraw(int player_num); //スコアとレベルの描画
    void cleardraw();
    void menudraw();

	void destroy();  //破棄
    void reset(int player_num);    //積み上げ配列の範囲内の全情報を初期化

    //当たり判定
    void collisionleft(int player_num);
    void collisionright(int player_num);
    void collisiondown(int player_num);
    bool collisionsrs(int player_num);

    //ネクスト
    void nextpattern();

    //全消し
    void allclear(int player_num);

    //スーパーローテーション
    int turnover_rate = 0; //ミノの回転率
    int type = 40; //0 = a→d 2 = 
    bool srstest = false;

    //ミノ
    int main[4][23][12]={ 0 };  //積みあがる本体(人数分
    int sub[22][12] = { 9 }; //サブ
    const int next0[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン 見本
    int next1[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン
    int next2[7]{ 0,1,2,3,4,5,6 }; //ネクストパターン補充用
    float transparency = 1.0F; //透明度
    const int mino[7][4][4] = {
        { //Iミノ
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0},
        {0,0,1,0}
        },
        { //Lミノ
        {0,0,0,0},
        {0,2,2,0},
        {0,0,2,0},
        {0,0,2,0}
        },
        { //Sミノ
        {0,0,0,0},
        {0,3,0,0},
        {0,3,3,0},
        {0,0,3,0}
        },
        { //Zミノ
        {0,0,0,0},
        {0,0,4,0},
        {0,4,4,0},
        {0,4,0,0}
        },
        { //Jミノ
        {0,0,0,0},
        {0,0,5,0},
        {0,0,5,0},
        {0,5,5,0}
        },
        { //Oミノ
        {0,0,0,0},
        {0,6,6,0},
        {0,6,6,0},
        {0,0,0,0}
        },
        { //Tミノ
        {0,0,0,0},
        {0,0,7,0},
        {0,7,7,0},
        {0,0,7,0}
        }
    };

    int test [4][4] = { 0 }; //流す用の配列
    int clearlinepos[22] = { 0 }; //横一列そろっている場所の確認用
   
    //回転時のtmp
    int tmp[4][4] = { 0 };

    //時間関係
    int nowtime = 0; //現在の時間
    int oldtime = 0; //前回の時間
    int time = 1;    //落下にかかる時間

    //方向キー
    int up = 0;   //上
    int down = -5; //下
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
    int hold_a;
    int holdtmp_a;

    bool srs = false; //スーパーローテーション

	//ゲームオーバー処理関係
	bool gameover = false; //ゲームオーバーになったときｔｒｕｅ
	int overcnt = 0; //ゲームオーバーになった時の中身の入れ替え変数
    int overcnt2 = 0; //ゲームオーバーになってからメニューが表示されるまでの時間
    int testcnt = 0;
    // 消去数
    int erase = 0;
    int fall_speed = SPEED;

    //スコア
    unsigned int score = 0;
    int erase_line = 0; //消されたライン数
    int olderasenum = 0; //前回消した行数を取っておく(B2B用)
    float back_to_back = 1; //back_to_backをした時のスコア倍率
    const int linescore[4] = { 40,100,300,1200 }; //同時消しの点数表

    //ゴースト
    int transparent = 50; //透明度
    int ghost[4][4] = { 0 }; 
    int gdown; //ゴーストのy軸
    bool gcollsion = false; //ゴーストの当たり判定

    //multi用
    int playerx = 0;
    int mainx = 0;
    int nextx = 0;
    int holdx = 0;
    
    //全消し
    int leaveline[22];
    int clearline = 0;
    bool first = false; //最初は全消し扱いにしない
    bool all_clear = false; //全消し

    //オプション
    int option[8]; //オプションの項目保存
    int maxlevelop; //レベル上限
    bool holdop;    //ホールド使用設定
    int nextop;     //ネクストを何個表示するか
    bool hidden;    //隠しを入れるか
    bool vsop;      //vsモードにするか
    bool reverseop; //操作を反転させるか
    bool scorereset;//ランキングスコアリセット

    float op_bonus = 1.0;

};